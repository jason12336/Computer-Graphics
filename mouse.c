#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <stdio.h>

GLfloat offset_x = 0;
GLfloat offset_y = 0;

GLfloat size_x = 0.5;
GLfloat size_y = 0.5;

GLfloat angle = 0;

enum menu{
	SMALL,
	MEDIUM,
	LARGE,
	ROTATE_LEFT,
	ROTATE_RIGHT
};

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
		glTranslatef(offset_x, offset_y, 0);
		glRotatef(angle, 0, 0, 1);
		glBegin(GL_POLYGON);
			glVertex2f(-size_x,-size_y);
			glVertex2f(-size_x,size_y);
			glVertex2f(size_x,size_y);
			glVertex2f(size_x,-size_y);
		glEnd();
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
}

void mouseFunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		GLfloat screen_x = x - 250;
		GLfloat screen_y = y - 250;
		screen_y = screen_y * -1;

		screen_x = screen_x / 250;
		screen_y = screen_y / 250;

		offset_y = screen_y;
		offset_x = screen_x;

		printf("screen_x:%.2f screen_y:%.2f\n", screen_x, screen_y);
		printf("x:%.2f y:%.2f\n", offset_x, offset_y);
		glutPostRedisplay();
	}
}

void myMenu(int id) {
	switch(id) {
		case SMALL:
			size_x = 0.25;
			size_y = 0.25;
			break;
		case MEDIUM:
			size_x = 0.5;
			size_y = 0.5;
			break;
		case LARGE:
			size_x = 0.75;
			size_y = 0.75;
			break;
		case ROTATE_LEFT:
			angle -= 45;
			break;
		case ROTATE_RIGHT:
			angle += 45;
			if (angle < -360 || angle > 360) {angle = 0;}
			break;
	}
	glutPostRedisplay();
}

void idleFunc() {
	offset_y += 0.001;
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
	glutCreateWindow("simple");
	glutDisplayFunc(display);
	// glutIdleFunc(idleFunc);

	glutCreateMenu(myMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAddMenuEntry("Small Cube", SMALL);
	glutAddMenuEntry("Medium Cube", MEDIUM);
	glutAddMenuEntry("Large Cube", LARGE);
	glutAddMenuEntry("Rotate Cube Left", ROTATE_LEFT);
	glutAddMenuEntry("Rotate Cube Right", ROTATE_RIGHT);

	glutMouseFunc(mouseFunc);
	glutMainLoop();
}