#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <math.h>
#include <stdio.h>

GLUquadric *quad1;
GLUquadric *quad2;

GLfloat x_pos = -1.55;
GLfloat angle = 0;
GLfloat road_speed = 0;


void body() {
    glPushMatrix();
        glColor3f(0, 0, 255);
        glTranslatef(0, 0, 0);
        glutSolidCube(0.6);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.4, -0.15, 0);
        glScalef(0.56, 0.5, 1);
        glutSolidCube(0.6);
    glPopMatrix();
}

void wheels() {
    quad1 = gluNewQuadric();
    quad2 = gluNewQuadric();
    glPushMatrix();
        glColor3f(128, 128, 128);
        glTranslatef(0.35, -0.3, 0);
        glRotatef(angle, 0, 1, 0);
        gluSphere(quad1, 0.15, 400, 400);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(128, 128, 128);
        glTranslatef(-0.1, -0.3, 0);
        gluSphere(quad2, 0.15, 400, 400);
    glPopMatrix();
}

void windows() {
    glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(0.15, 0.15, 0);
        glutSolidCube(0.2);
    glPopMatrix();
    glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(-0.15, 0.15, 0);
        glutSolidCube(0.2);
    glPopMatrix();
}

void road_markings() {
    // replace with for loop
    float place = -3;
    while (place < 20.0) {
        glPushMatrix();
            glColor3f(255, 255, 255);
            glTranslatef(place, -0.4, 0);
            glScalef(0.4, 0.2, 0.01);
            glutSolidCube(0.4);
        glPopMatrix();
        place += 0.3;
    }
}

void display() {
    glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glPushMatrix();
        glTranslatef(x_pos, 0, 0);
        body();
        windows();
        wheels();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(road_speed, 0, 0);
        road_markings();
    glPopMatrix();

    glFlush();
}

void idle_move() {
    x_pos+=0.01;
    angle += 10;
    road_speed -= 0.02;
    if (angle > 360) {angle = 0;}
    glutPostRedisplay();
}

void main(int argc, char **argv) {
    glutInit(&argc, argv);
	// glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
    glutCreateWindow("Car");

    // glutMouseFunc(mouseFunc);

    // glutKeyboardFunc(keyboardFunc);
	
    glutDisplayFunc(display);
    glutIdleFunc(idle_move);
	// glutReshapeFunc(MyReshape);
	// glutIdleFunc(MyIdle);

    glutMainLoop();
}