#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <math.h>

float theta = M_PI/4;
int toggle = 1;
int rotate = 0.0001;

void display(void) {
	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 1);
	
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

void MyIdle() {
	theta += rotate;
	if (theta > 2*M_PI) theta -= 2*M_PI;
	glutPostRedisplay();
	
	return;
}

void MyKeyFunc(unsigned char key, int x, int y) {
	if (toggle == 1) {
		toggle = 0;
		rotate = 0; // stop rotating
	}
	else {
		toggle = 1;
		rotate = 0.0001;
	}
	
	return;
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutCreateWindow("Rotating Square");
	glutDisplayFunc(display);
	glutIdleFunc(MyIdle);
	glutKeyboardFunc(MyKeyFunc);
	glutMainLoop();
}