#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(10.0);
	glBegin(GL_POINTS);
		
		glColor3f(0, 0.0, 1.0);
		glVertex2f(0, 0.25); // top point
		
		glColor3f(0, 1.0, 0.0);
		glVertex2f(-0.25,0.1); // first left point
		
		glColor3f(0.0, 1.0, 0);
		glVertex2f(-0.25, -0.35); // bottom left point
		
		glColor3f(0, 0.0, 1.0);
		glVertex2f(0, -0.5); // bottom point
		
		glColor3f(0, 1.0, 0);
		glVertex2f(0.25, -0.35); // bottom right point
		
		glColor3f(0, 1, 0);
		glVertex2f(0.25,0.1); // first right point 
		
	glEnd();

	glBegin(GL_LINE_LOOP);
	
		glColor3f(0, 0, 1);
		glVertex2f(-0.25, 0.1); // top left
		glVertex2f(0.25, -0.35); // bottom right
		glColor3f(1, 0, 0);
		glVertex2f(0.25, -0.35); // bottom right
		glVertex2f(-0.25, -0.35); // bottom left
		glColor3f(0, 0, 1);
		glVertex2f(0.25, 0.1); // top right
	
	glEnd();
	
	glFlush();
	return;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("simple");
	glutDisplayFunc(display);
	glutMainLoop();
}