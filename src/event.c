#include "./event.h"
#include "./game.h"

#include <stdio.h>
#include <stdlib.h>

void Display () {
    glClear(GL_COLOR_BUFFER_BIT);

    draw_game();

    glFlush();
}
void Reshape (int x, int y) {
    glViewport(0, 0, x, y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, x, 0, y);
    glScaled(1, -1, 1);
    glTranslated(0, -y, 0);
    // ウィンドウサイズを固定にする
    glutReshapeWindow(600, 700);
}
void Timer (int value) {
    glutPostRedisplay();
    glutTimerFunc(100, Timer, 0);
}
void NpcTimer (int value) {
    npc_select();
}
void Keyboard(unsigned char key, int x, int y) {
    if (key == 'q' || key == 27) {
        printf("exit...\n");
        exit(0);
    } else if (key == 32 && game_info.state == GAME_TITLE) {
        game_info.state = GAME_PLAYING;
    } else if (key == 32 && game_info.state == GAME_RESULT) {
        init_game_info();
    }
}
void Mouse(int b, int s, int x, int y) {
    if (b == GLUT_LEFT_BUTTON && s == GLUT_UP) {
        if (game_info.turn == OWN_TURN && game_info.state == GAME_PLAYING) {
            click(x, y);
        }
    }
}
