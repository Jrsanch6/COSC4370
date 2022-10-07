/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "./freeglut-3.2.1/include/GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {
  for(int i = 0; i < 10; i++){
    glPushMatrix();
    glRotatef (36*i, 0, 0, 1);
    glTranslatef(1.4,.5,0);
    glutSolidTeapot(.2);
    glPopMatrix();
  }
}

void problem2() {
  for(int x = 0; x < 20; x++){
    glPushMatrix();
    glTranslatef((10-x)*.2, x*0.02, 0);
    glScalef(1, 2 + x * 0.2, 1);
    glutSolidCube(0.2);
    glPopMatrix();
  }
}

void problem3() {
  int rotation_number = 0;
  for(int i = 6; i > 0; i--){
    glPushMatrix();
    glTranslatef((-i-1)*(0.3),1.6,0);
    for(int j = 0; j < i; j++){
      glTranslatef(2*0.3,(i*0.6)-4,0);
      glutSolidTeapot(.2);
      glTranslatef(0,(-i*0.6)+4,0);
    }
    glPopMatrix();
    rotation_number++;
  }
}

void problem4() {
  float height = 0;
  float position = 0;
  glPushMatrix();
glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, -1.0f, 0.5f);
    glVertex3f(0.87f,  0.5f, 0.5f);
    glVertex3f(-0.87f, 0.5f, 0.5f);
glEnd();
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 3; j++){
      glPushMatrix();
      glTranslatef(-0.77 + position, 0.6+height,0);
      glRotatef (7*j, 1, 0, 0);
      glScalef(1, 2 , 1);
      glutSolidCube(.2);
      glPopMatrix();
      height+=.4;
    }
    height = 0;
    position += .5;
  }
  position = 0;
  height = 0;
  for(int j = 0; j < 3; j++){
    glPushMatrix();
    glTranslatef(.8 + position, j*0.2,0);
    glRotatef (-45, 0, 0, 1);
    glRotatef (7*j, 1, 0, 0);
    glScalef(1, 2 , 1);
    glutSolidCube(.2);
    glPopMatrix();
    height+=.4;
    position+= .2;
    height += .0005;
  }
  glPopMatrix();

}

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
