#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <math.h>

GLUquadricObj *obj;
GLfloat theta[3] = {M_PI/4, M_PI/4, M_PI/4};
GLfloat UPPER_ARM_HEIGHT = 1, 
UPPER_ARM_WIDTH=1,
LOWER_ARM_HEIGHT = 1,
LOWER_ARM_WIDTH = 1,
BASE_HEIGHT = 0.5,
BASE_RADIUS = 0.5;

GLfloat rotate = 0.001;

void base() {
	glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		obj = gluNewQuadric();
		gluCylinder (obj, BASE_RADIUS, BASE_RADIUS, BASE_HEIGHT, 5, 5);
	glPopMatrix();
}

void lower_arm() {
	glPushMatrix();
		glTranslatef(0, 0.5*LOWER_ARM_HEIGHT, 0.0);
		glScalef(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH);
		glutWireCube(1);
	glPopMatrix();
}

void upper_arm() {
	glPushMatrix();
		glTranslatef(0, 0.5*UPPER_ARM_HEIGHT, 0);
		glScalef(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH);
		glutWireCube(1);
	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0,2.0,2.0,0.0,0.0,0.0,0.0,1.0,0.0);
	glColor3f(1, 0, 0);
	glRotatef(theta[0], 0, 1, 0);
	base();
	glTranslatef(0, BASE_HEIGHT, 0);
	glRotatef(theta[1], 0, 0, 1);
	lower_arm();
	glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
	glRotatef(theta[2], 0, 0, 1);
	upper_arm();
	glFlush();
}

void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
	glFrustum(-1.0,1.0,-1.0,1.0,0.5,6.0);


	glViewport(0,0,w,h);
	return;
}

void myIdle() {
	theta[1] += rotate;
	if (theta[1] > 2*M_PI) theta[1] -= 2*M_PI;
	glutPostRedisplay();
	
	return;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("cylinder");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutIdleFunc(myIdle);
	glutMainLoop();
}