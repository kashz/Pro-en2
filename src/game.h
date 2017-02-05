#ifndef __GAME_H__
#define __GAME_H__

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <glpng/glpng.h>
#else
#include <GL/glut.h>
#include <glpng/glpng.h>
#endif

#define PADDING_WIDTH  (50)
#define PADDING_HEIGHT (20)

#define GAME_TITLE   (0)
#define GAME_PLAYING (1)
#define GAME_RESULT  (2)

#define OWN_TURN  (0)
#define NPC_TURN  (1)

struct _image {
    GLuint img;
    pngInfo info;
};
typedef struct _image Image;
struct _game_info {
    int state;
    int turn;
    int score;
    int npc_score;
};
typedef struct _game_info GameInfo;

extern Image blocks[4];
extern Image junction;
extern Image bars[2][2];
extern Image score_board;
extern Image numbers[10];

// マップに何があるかの情報
extern int map[11][11];

extern GameInfo game_info;

void init_game_info();
void load_images();
void draw_game();
void draw_map();
void draw_result();

void LoadSprite(Image* image, char* name);
void PutSprite(Image* image, int x, int y);
void check_surrounded();
int check_clear();
void click(int x, int y);
void print_map();
void repair_map();
void draw_score(int x, int y, int score);
void npc_select();


#endif /* __GAME_H__ */
