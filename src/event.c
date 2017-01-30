#include "./event.h"

void Display () {

}
void Reshape (int x, int y) {

}
void Timer (int value) {

}
void Keyboard(unsigned char key, int x, int y) {
    if (key == 'q' || key == 27) {
        printf("exit...\n");
        exit(0);
    }
}
