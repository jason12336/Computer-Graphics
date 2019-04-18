#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <math.h>
#include <stdio.h>

// [0] is scale [1] is x [2] is y [3] is z
double cubes[40][4];
// [0] is r [1] is g [2] is b
double colors[40][3];
// [0] is x_angle [1] is y_angle [2] is z_angle
float theta2[64], theta3[64];

double spheres[40][2];
GLUquadric* sphere_objects[40][1];

int selected;
int state;
int shift = 0;

GLfloat light_pos[] = {1.0, 2.0, 3.0, 1.0};
double shape_state = 0; // Cube state // 1 is Sphere

int count = 0;
int sphere_count = 0;
float theta = M_PI/4;

enum {
  MENU_CUBE = 0,
  MENU_SPHERE,
  MOVE,
  ROTATE,
};

void display(void) {
	glClearColor(0.0,0.35,0.4,1.0);

	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat  ambient[4] = {0.1, 1, 0.0, 1.0};
	GLfloat  diffuse[4] = {0.2, 1, 0.0, 1.0};
	GLfloat specular[4] = {0.2, 0.8, 0.7, 1.0};
	GLfloat shininess = 32.0;
	GLfloat normal[3] = {0.0,0.0,0.25};
	GLfloat position[4] = {1.0,1.0,1.0,1.0};
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,10.0,0.0,0.0,0.0,0.0,1.0,0.0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	position[1] = cos(theta); 
	position[2] = sin(theta);

	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    // Draw Cubes
    for (int i = count-1; i >= 0; i--) {
        GLfloat x = cubes[i][1];
		GLfloat y =	-cubes[i][2];
        glRotatef(theta2[i], 0.0, 1.0, 0.0);
        glRotatef(theta3[i], 1.0, 0.0, 0.0);
        glTranslatef(x, y, 0.0);
        glutSolidCube(cubes[i][0]); 
        glTranslatef(-x, -y, 0.0);
    }

    // Draw Spheres
    for (int i = sphere_count-1; i >= 0; i--) {
        GLfloat x = spheres[i][0];
		GLfloat y =	-spheres[i][1];
        glRotatef(theta2[i],0.0,1.0,0.0);
        glRotatef(theta3[i],1.0,0.0,0.0);
        glTranslatef(x, y, 0);
        GLUquadric *quad = sphere_objects[i][0];
        quad = gluNewQuadric();
        gluSphere(quad, 0.15, 24, 24);
        glTranslatef(-x, -y, 0);
    }
	
    glutSwapBuffers();
    glFlush();
	return;

}

void myMenu(int id) {
    switch(id) {
        case MENU_CUBE:
            printf("Cube Mode Activated - Left Mouse Click will now spawn cubes\n");
            shape_state = 0;
            break;
        case MENU_SPHERE:
            printf("Sphere Mode Activated - Left Mouse Click will now spawn Sphere\n");
            shape_state= 1;
            break;
    }
}

void mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float screen_x = (x - 250.0) / 250.0;
        float screen_y = (y - 250.0) / 250.0;
        printf("(x, y)  :  (%f, %f) \n", screen_x, screen_y);

        if (shape_state == 0) {
            printf("Total Cubes: %d \n", count);
            cubes[count][0] = 0.5;
            cubes[count][1] = screen_x;
            cubes[count][2] = screen_y;
            cubes[count][3] = 0;
            count++;
        }

        else if (shape_state == 1) {
            GLUquadric *quad;
            sphere_objects[sphere_count][0] = quad;
            spheres[sphere_count][0] = screen_x;
            spheres[sphere_count][1] = screen_y;
            sphere_count++;
        }

        theta2[shift] = 0.0;
		theta3[shift] = 0.0;
        shift++;
    }

    glutPostRedisplay();
}

void keyboardFunc(unsigned char key, int x, int y) {
    // x and y are the mouse coordinates for some reason
    // printf("%c", key);
    // printf("%d and %d", x, y);
    switch (key) {
        case '1':
            colors[selected][0] = 255;
            colors[selected][1] = 0;
            colors[selected][2] = 0;
            break;
        case '2':
            colors[selected][0] = 0;
            colors[selected][1] = 255;
            colors[selected][2] = 0;
            break;
        case '3':
            colors[selected][0] = 0;
            colors[selected][1] = 0;
            colors[selected][2] = 255;
            break;
            
    }
    glutPostRedisplay();
}

void rotate(int key, int x, int y) {
    if(count > 0) {
        if(key == GLUT_KEY_LEFT) theta2[count-1] += 5.0;
        if(key == GLUT_KEY_RIGHT) theta2[count-1] -= 5.0;
        if(key == GLUT_KEY_UP) theta3[count-1] +=5;
        if(key == GLUT_KEY_DOWN) theta3[count-1] -= 5.0; 
    } else if (sphere_count > 0) {
        if(key == GLUT_KEY_LEFT) theta2[sphere_count-1] += 5.0;
        if(key == GLUT_KEY_RIGHT) theta2[sphere_count-1] -= 5.0;
        if(key == GLUT_KEY_UP) theta3[sphere_count-1] +=5;
        if(key == GLUT_KEY_DOWN) theta3[sphere_count-1] -= 5.0;
    }
	glutPostRedisplay();
}

void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-2.0,2.0,-2.0,2.0,0.3,5.0);
	glFrustum(-1.0,1.0,-1.0,1.0,8.0, 10.0);
	// gluPerspective(60,1.0,0.3,10.0);
	glViewport(0,0,w,h);
	return;
}

void main(int argc, char **argv) {
    glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,65);
    glutCreateWindow("Sculpture Tool");

    glutCreateMenu(myMenu);
    glutAddMenuEntry("Cube Mode (Left-Click-Spawn)\t", MENU_CUBE);
    glutAddMenuEntry("Sphere Mode (Left-Click-Spawn)\t", MENU_SPHERE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
    glutMouseFunc(mouseFunc);
	glutSpecialFunc(rotate);
    glutKeyboardFunc(keyboardFunc);
	
    glutMainLoop();
}