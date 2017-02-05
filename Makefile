#
# Makefile
# Auther: Shunta Karasawa
#

SRC_DIR=./src
OBJ_DIR=./obj
MEDIA_DIR=./media

UNAME_S := $(shell uname -s)

CFILES=$(wildcard $(SRC_DIR)/*.c)
HEADERS=$(wildcard $(SRC_DIR)/*.h)
SRCS=$(CFILES)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

CC = gcc
CCFLAGS = -Wall -Wno-deprecated -Wno-unused-function -I/usr/include/opengl
CCFLAGS_MAC = -Wall -Wno-deprecated
LD = gcc
LDFLAGS =
LIBS = -lm -lglpng -lglut32 -lglu32 -lglpngl32
LIBS_MAC = -framework GLUT -framework OpenGL -framework glpng

# For Windows_NT
ifeq ($(OS),Windows_NT)
TARGET = app.exe
ICON=$(MEDIA_DIR)/icon.ico
ICON_OBJ=$(OBJ_DIR)/icon.o

$(TARGET) : $(OBJS) $(ICON_OBJ)
	$(LD) $(OBJS) $(ICON_OBJ) $(LDFLAGS) -o $(TARGET) $(LIBS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CCFLAGS) -o $@ -c $<

$(ICON_OBJ) : $(ICON)
	windres -i icon.rc -o $(ICON_OBJ)
endif


# For macOS
ifeq ($(UNAME_S),Darwin)
TARGET = app

$(TARGET) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET) $(LIBS_MAC)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CCFLAGS_MAC) -o $@ -c $<
endif

$(OBJS) : $(HEADERS) Makefile

all : clean $(TARGET)

clean :
	rm -rf $(TARGET) $(OBJS) $(ICON_OBJ) core *-
