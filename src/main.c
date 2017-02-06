#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "./event.h"
#include "./game.h"

int main(int argc, char **argv) {

    srandom(time(NULL));

    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Children's Games");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutTimerFunc(100, Timer, 0);
    glutMouseFunc(Mouse);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glutInitDisplayMode(GLUT_RGBA);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    init_game_info();
    load_images();

    glutMainLoop();

    return 0;
}
