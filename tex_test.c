#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <stdio.h>

GLubyte image [64][64][3];
float rotate = 0;

void drawShape() {
    glBegin(GL_POLYGON);
        glColor3f(0.0, 1.0, 1.0);

        glTexCoord2f(0, 1);
        glVertex3f(-0.5, 0.5, 0.0); // bottom right

        glTexCoord2f(0, 0);
        glVertex3f(0.5, 0.5, 0.0); // top right 

        glTexCoord2f(1, 0);
        glVertex3f(0.5, -0.5, 0.0); // top left

        glTexCoord2f(1, 1);
        glVertex3f(-0.5, -0.5, 0.0); // bottom left
    glEnd();
}

void display() {
    glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glPushMatrix();
        // glTranslatef(-0.25, -0.25, 0);
        glRotatef(rotate, 0, 0, 1);
        drawShape();
    glPopMatrix();


    glEnable(GL_TEXTURE_2D);

    glFlush();
    return;
}

void idle() {
    rotate += 0.1;
    if (rotate >= 360) rotate = 0;
    glutPostRedisplay();
    // printf("%.2f", rotate);
}

void main(int argc, char **argv) {
    int i,j;
	FILE *fp;
	char buffer[4096],*pb;

	fp = fopen("texture.bin","r");
	fread(buffer, 4096,1,fp);

	pb = buffer;

	for(i=0; i<64; i++) {
	    for(j=0; j<64; j++) {		
            image[i][j][0]=(GLubyte)*pb;
            image[i][j][1]=(GLubyte)*pb;
            image[i][j][2]=(GLubyte)*pb;
            pb++;
	    }
    }
    
    glutInit(&argc, argv);
	// glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
    glutCreateWindow("Messing with Textures");

    glutIdleFunc(idle);
    glutDisplayFunc(display);

    
	glEnable(GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// glutReshapeFunc(MyReshape);
	// glutIdleFunc(MyIdle);

    glutMainLoop();
}