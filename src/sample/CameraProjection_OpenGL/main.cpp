#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>

#include "Camera.h"
#include "CameraUtility.h"


#define WINDOWNAME "Sample Application"

int W = 1280;
int H = 720;


int F = 45;

int P =    0;
int Q = -125;
int R =   35;
int S =    0;
int T =    0;
int U =    0;


void display(void)
{
	const int WIN_W = (int)(glutGet(GLUT_WINDOW_WIDTH));
	const int WIN_H = (int)(glutGet(GLUT_WINDOW_HEIGHT));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw Background
	{
		utvl::graphics::CameraOrtho2D c(WIN_W, WIN_H);

		c.enable();

		glViewport(0, 0, WIN_W, WIN_H);

		glColor4f(0.2f, 0.2f, 0.2f, 0.0f);

		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f((float)WIN_W, 0.0, 0.0);
		glVertex3f((float)WIN_W, (float)WIN_H, 0.0);
		glVertex3f(0.0, (float)WIN_H, 0.0);
		glEnd();

		utvl::graphics::print();

		c.disable();
	}

	// Draw Foreground
	{
		glEnable(GL_DEPTH_TEST);

		utvl::graphics::CameraPerspective c(F, (double)WIN_W / (double)WIN_H, 0.1, 1000.0,
			P, Q, R,
			S, T, U,
			0.0, 0.0, 1.0);

		c.enable();

		glColor4f(0.5f, 0.2f, 0.2f, 0.0f);

		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 50.0, 0.0);
		glVertex3f(50.0, 50.0, 0.0);
		glVertex3f(50.0, 0.0, 0.0);
		glEnd();

		glColor4f(0.0f, 0.5f, 0.2f, 0.0f);

		glBegin(GL_POLYGON);
		glVertex3f(-50.0, 0.0, 0.0);
		glVertex3f(-50.0, 50.0, 0.0);
		glVertex3f(0.0, 50.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glEnd();

		glColor4f(0.2f, 0.2f, 0.5f, 0.0f);

		glBegin(GL_POLYGON);
		glVertex3f(0.0, -50.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(50.0, 0.0, 0.0);
		glVertex3f(50.0, -50.0, 0.0);
		glEnd();

		glColor4f(0.5f, 0.5f, 0.5f, 0.0f);

		glBegin(GL_POLYGON);
		glVertex3f(-50.0, -50.0, 0.0);
		glVertex3f(-50.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, -50.0, 0.0);
		glEnd();

		utvl::graphics::print();

		c.disable();

		glDisable(GL_DEPTH_TEST);
	}

	glutSwapBuffers();
	glFinish();
}


void reshape(int width, int height)
{
	int w = height * 16 / 9;
	int left = (width - w) / 2;

	glViewport(left, 0, w, height);

	glutPostRedisplay();
}


void idle(void)
{
	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
	;
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize((int)W, (int)H);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(WINDOWNAME);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard);

	printf("Call GLUT main...\n");

	glutMainLoop();

	printf("Return from GLUT main\n");

	return 0;
}

