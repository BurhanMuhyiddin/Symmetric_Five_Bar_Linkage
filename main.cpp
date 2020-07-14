#include <iostream>
#include <gl/glut.h>
#include <gl/GLU.h>
#include <gl/GL.h>

// Additional header files
#include "window_properties.h"
#include "draw_linkage.h"
// End of additional header files

using namespace std;

#define PI				3.14159265359

// Definitions of callback functions
void display_callback();
void reshape_callback(int, int);
void motion_callback(int, int);
void timer_callback(int);
// End of definitions of callback functions

float mouseX = 0.0, mouseY = 0.0;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	init_linkage();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(W_W, W_H);
	glutCreateWindow("Symmetric Five Bar Linkage");

	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutMotionFunc(motion_callback);
	glutTimerFunc(0, timer_callback, 0);

	init();

	glutMainLoop();
}

//float theta = 0.0, step = 0.1;
//float R = 60.0;

void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	draw_five_bar_linkage(mouseX, mouseY);

	/*draw_five_bar_linkage(-37, 144);*/
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex2f(mouseX, mouseY);
	glEnd();

	glutSwapBuffers();
}

void reshape_callback(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-W_W/2.0, W_W/2.0, -W_H/2.0, W_H/2.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void motion_callback(int x, int y)
{
	mouseX = x*1.0;
	mouseY = y*1.0;
	//cout << mouseX << " " << mouseY << endl;
	mouseX = map_between(mouseX, 0.0, W_H, -W_H / 2.0, W_H / 2.0);
	mouseY = map_between(mouseY, 0.0, W_W, W_W / 2.0, -W_W / 2.0);
}

void timer_callback(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer_callback, 0);
}