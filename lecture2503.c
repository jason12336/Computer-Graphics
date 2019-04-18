#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"


void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,3.0,0.0,0.0,0.0,0.0,1.0,0.0);

	glutWireCube(0.5);

	glTranslatef(0.0,0.7,0.0);
	glPushMatrix();
		glutWireCube(0.5);

		//glTranslatef(0.0,0.7,0.0);
		glRotatef(45.0,0.0,0.0,1.0);
		glTranslatef(0.0,0.7,0.0);
		glScalef(0.5,1.0,1.0);
		
		glutWireCube(0.5);
	glPopMatrix();
	
	glPushMatrix();
		glutWireCube(0.5);

		glRotatef(-45.0, 0, 0, 1);
		glTranslatef(0, 0.7, 0);
		glScalef(0.5, 1, 1);
		
		glutWireCube(0.5);
	glPopMatrix();
	
	glPushMatrix();
		glutWireCube(0.5);
		
		glRotatef(45, 0, 0, 1);
		glTranslatef(0,-0.7, 0);
		glScalef(0.5, 1, 1);
		
		glutWireCube(0.5);
	glPopMatrix();
	
	glPushMatrix();
		glutWireCube(0.5);
		
		glRotatef(-45, 0, 0, 1);
		glTranslatef(0, -0.7, 0);
		glScalef(0.5, 1, 1);
		
		glutWireCube(0.5);
	glPopMatrix();
	
	glTranslatef(0.0,0.7,0.0);
	glutWireCube(0.5);
	
	glFlush();
	return;
}


void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-2.0,2.0,-2.0,2.0,0.3,5.0);
//	glFrustum(-1.0,1.0,-1.0,1.0,9.5,12.0);
	gluPerspective(60,1.0,0.3,10.0);
	glViewport(0,0,w,h);
	return;
}




int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("cube");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);


	glutMainLoop();
}
