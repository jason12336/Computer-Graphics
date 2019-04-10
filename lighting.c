#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <math.h>
#include <stdio.h>


/*
This program illustrates some 3D operations.
It draws a wire cube with sides of length 0.5 in World Coordinates.
You can uses the glOrtho or glFrustum functions
to choose either orthographic or perspective projection.
You can use the gluLookAt function to choose the viewpoint, 
view direction and the up vector.
*/

GLfloat rotate_x = 0;
GLfloat rotate_y = 0;

int saved_x;
int saved_y;

int STATE = GLUT_UP;

void display(void)
{
	GLfloat  ambient[4] = {0.3, 0.0, 0.0, 1.0};
	GLfloat  diffuse[4] = {0.6, 0.0, 0.0, 1.0};
	GLfloat specular[4] = {0.8, 0.6, 0.6, 1.0};
	GLfloat shininess = 32.0;
	GLfloat normal[3] = {0.0,0.0,1.0};
	GLfloat position[4] = {1.0,1.0,1.0,1.0};

	glClearColor(0.0,0.0,1.0,1.0);

	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// gluLookAt(1.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glLightfv(GL_LIGHT0, GL_POSITION, position);

	
/*	glNormal3fv(normal);
	glBegin(GL_POLYGON);
		glVertex3f(-0.5,-0.5,0.0);
		glVertex3f(-0.5,0.5,0.0);
		glVertex3f(0.5,0.5,0.0);
		glVertex3f(0.5,-0.5,0.0);
	glEnd();
*/
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);


	glRotatef(rotate_x, 0, 1, 0);
	glRotatef(rotate_y, 1, 0, 0);
	glutSolidCube(0.5);
	glutSwapBuffers();
	
	glFlush();
	return;
}

void motionFunc(int x, int y) {
	if (STATE == GLUT_UP) {
		printf("entered");
		saved_x = x;
		saved_y = y;
		printf("%d\n%d\n", x, y);
		STATE = GLUT_DOWN;
	}
    rotate_x = x - saved_x;
    rotate_y = y - saved_y;

	printf("-----%d\n------%d\n", x, y);
    if (rotate_x < -360 || rotate_x > 360) {rotate_x = 0;}
    if (rotate_y < -360 || rotate_y > 360) {rotate_y = 0;}
    glutPostRedisplay();
    return;
}

void mouseFunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		STATE = state;
		printf("fired");
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("cube");
	glutDisplayFunc(display);
    glutMotionFunc(motionFunc);
	glutMouseFunc(mouseFunc);
	// glutReshapeFunc(MyReshape);

	glutMainLoop();
}