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
double rotations[40][3];

double spheres[40][2];
GLUquadric* sphere_objects[40][1];

int selected;
int state;

GLfloat light_pos[] = {1.0, 2.0, 3.0, 1.0};
double shape_state = 0; // Cube state // 1 is Sphere

int count = 0;
int sphere_count = 0;

enum {
  MENU_CUBE = 0,
  MENU_SPHERE,
  MOVE,
  ROTATE,
};

void display() {
    glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);

    // Draw Cubes
    for (int i = 0; i < count; i++) {
        glPushMatrix();
            glColor3f(colors[i][0], colors[i][1], colors[i][2]);
            glRotatef(rotations[i][0], 1, 0, 0);
            glRotatef(rotations[i][1], 0, 1, 0);
            glRotatef(rotations[i][2], 0, 0, 1);
            glTranslatef(cubes[i][1], cubes[i][2], cubes[i][3]);
            glutSolidCube(cubes[i][0]); 
        glPopMatrix();
    }
	glFlush();

    // Draw Spheres
    for (int i = 0; i < sphere_count; i++) {
        glPushMatrix();
            glColor3f(55, 55, 255);
            glRotatef(0, 1, 0, 0);
            glRotatef(0, 0, 1, 0);
            glRotatef(0, 0, 0, 1);
            glTranslatef(spheres[i][0], spheres[i][1], 0);
            GLUquadric *quad = sphere_objects[i][0];
            quad = gluNewQuadric();
            gluSphere(quad, 0.15, 24, 24);
        glPopMatrix();
    }
	
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
        screen_y = screen_y * -1;
        printf("(x, y)  :  (%f, %f) \n", screen_x, screen_y);

        if (shape_state == 0) {
            cubes[count][0] = 0.5;
            cubes[count][1] = screen_x;
            cubes[count][2] = screen_y;
            cubes[count][3] = 0;

            colors[count][0] = 55;
            colors[count][1] = 55;
            colors[count][2] = 255;

            rotations[count][0] = 0;
            rotations[count][1] = 0;
            rotations[count][2] = 0;
            count++;
        }
        else if (shape_state == 1) {
            GLUquadric *quad;
            sphere_objects[sphere_count][0] = quad;
            spheres[sphere_count][0] = screen_x;
            spheres[sphere_count][1] = screen_y;
            sphere_count++;
        }
    }

    glutPostRedisplay();
}

void keyboardFunc(unsigned char key, int x, int y) {
    // x and y are the mouse coordinates for some reason
    // printf("%c", key);
    // printf("%d and %d", x, y);
    switch (key) {
        case 'r':
            state = ROTATE;
            printf("Mode: ROTATE\n");
            break;
        case 'm':
            state = MOVE;
            printf("Mode: MOVE\n");
            break;
        case 'a':
            if (state == MOVE) {
                cubes[selected][1] -= 0.01;
            }
            else if (state == ROTATE) {
                // rotate the cube
                rotations[selected][1] -= 1;
                if (rotations[selected][1] < -360) {
                    rotations[selected][1] = 0;
                }
            }
            break;
        case 'd':
            if (state == MOVE) {
                cubes[selected][1] += 0.01;
            }
            else if (state == ROTATE) {
                rotations[selected][1] += 1;
                if (rotations[selected][1] < -360) {
                    rotations[selected][1] = 0;
                }
            }
            break;
        case 'w':
            if (state == MOVE) {
                cubes[selected][2] += 0.01;
            }
            else if (state == ROTATE) {
                rotations[selected][0] -= 1;
                if (rotations[selected][0] < -360) {
                    rotations[selected][0] = 0;
                }
            }
            break;
        case 's':
            if (state == MOVE) {
                cubes[selected][2] -= 0.01;
            }
            else if (state == ROTATE) {
                rotations[selected][0] += 1;
                if (rotations[selected][0] < -360) {
                    rotations[selected][0] = 0;
                }
            }
            break;
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

void main(int argc, char **argv) {
    glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
    glutCreateWindow("Sculpture Tool");

    glutCreateMenu(myMenu);
    glutAddMenuEntry("Add Cube\t", MENU_CUBE);
    glutAddMenuEntry("Add Sphere\t", MENU_SPHERE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMouseFunc(mouseFunc);

    glutKeyboardFunc(keyboardFunc);
	
    glutDisplayFunc(display);
    glutMainLoop();
}