#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "./store.h"
#include "./state.h"
#include "./event.h"

int main(int argc, char const *argv[]) {

    InitStore();

    glutInit(&argc, argv);
    glutInitWindowSize(store.windowSize.x, store.windowSize.y);
    glutCreateWindow("Children's Games");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutTimerFunc(500, Timer, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutInitDisplayMode(GLUT_RGBA);

    glutMainLoop();

    return 0;
}
