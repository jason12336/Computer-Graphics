#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <stdio.h>
#include <math.h>

GLfloat r,g,b = 0.0;
int first = 1;
float theta = M_PI/4;

void display(void) {
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(r, g, b);

    GLfloat x = cos(theta), y = sin(theta);

    glBegin(GL_POLYGON);
        glVertex2f(-x, -y);
        glVertex2f(-y, x);
        glVertex2f(x, y);
        glVertex2f(y, -x);
    glEnd();

    glFlush();
    return;
}

void resizeCallback(int x, int y) {
    if (!first) {
        r = 1;
    }
    else {
        r = 0;
    }
    first = !first;
    return;
}

void idleFunc(void) {
    theta+=0.001;
    // if (theta > 2*M_PI) theta -= 2*M_PI;
    glutPostRedisplay();
    return;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutCreateWindow("callback");
    glutReshapeFunc(resizeCallback);
    glutIdleFunc(idleFunc);
    glutDisplayFunc(display);

    glutMainLoop();
}