#include "draw_linkage.h"
#include "linkage_properties.h"
#include "window_properties.h"
#include <gl/glut.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <math.h>

#include <iostream>
using namespace std;

// Choose the bottom midpoint of the linkage
struct MyPOINT midPoint = {0, 0};
float size_of_triangle_sides = 25;

struct MyPOINT trLS1, trLS2, trLS3;
struct MyPOINT trRS1, trRS2, trRS3;

void init_linkage()
{
	// draw static parts
	calculate_static_parts();
}

void calculate_static_parts()
{
	trLS3.x = midPoint.x - L0; trLS3.y = midPoint.y;
	trLS1.x = trLS3.x - size_of_triangle_sides / 2.0; trLS1.y = trLS3.y - sqrt(pow(size_of_triangle_sides, 2.0) - pow(size_of_triangle_sides / 2.0, 2.0));
	trLS2.x = trLS3.x + size_of_triangle_sides / 2.0; trLS2.y = trLS1.y;

	trRS3.x = midPoint.x + L0; trRS3.y = midPoint.y;
	trRS1.x = trRS3.x - size_of_triangle_sides / 2.0; trRS1.y = trRS3.y - sqrt(pow(size_of_triangle_sides, 2.0) - pow(size_of_triangle_sides / 2.0, 2.0));
	trRS2.x = trRS3.x + size_of_triangle_sides / 2.0; trRS2.y = trRS1.y;
}

void draw_five_bar_linkage(float x, float y)
{
	float angles[2] = { 0.0 };
	calculate_inverse_kinematics(x, y, angles);
	float th1 = angles[0], th4 = angles[1];

	//cout << th1 << " " << th4 << endl;

	draw_base_of_linkage();

	struct MyPOINT B1, B2, P;
	B1.x = L1 * cos(th1) - L0 + midPoint.x; B1.y = midPoint.y + L1 * sin(th1);
	B2.x = L1 * cos(th4) + L0 + midPoint.x; B2.y = midPoint.y + L1 * sin(th4);
	P.x = x;								P.y = y;
	//cout << sqrt(pow(B2.x - trRS3.x, 2) + pow(B2.y - trRS3.y, 2)) << endl;
	draw_line(trLS3, B1);
	draw_line(trRS3, B2);
	draw_line(B1, P);
	draw_line(B2, P);
}

void draw_base_of_linkage()
{
	// Draw triangles
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
		glVertex2f(trLS1.x, trLS1.y);
		glVertex2f(trLS2.x, trLS2.y);
		glVertex2f(trLS3.x, trLS3.y);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
		glVertex2f(trRS1.x, trRS1.y);
		glVertex2f(trRS2.x, trRS2.y);
		glVertex2f(trRS3.x, trRS3.y);
	glEnd();

	// draw line between triangles
	glColor3f(1.0, 0.0, 1.0);
	draw_line(trLS3, trRS3);
}

void draw_line(struct MyPOINT p1, struct MyPOINT p2)
{
	glBegin(GL_LINES);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
	glEnd();
}

void calculate_inverse_kinematics(float x, float y, float* buf)
{
	float D1 = pow(L1, 2) - pow(L2, 2) + pow(y, 2) + pow(x + L0, 2) + 2 * L1*(x + L0);
	float E1 = 2.0 * y * L1;
	float F1 = pow(L1, 2) - pow(L2, 2) + pow(y, 2) + pow(x + L0, 2) - 2 * L1*(x + L0);

	float D4 = pow(L1, 2) - pow(L2, 2) + pow(y, 2) + pow(x - L0, 2) + 2 * L1*(x - L0);
	float E4 = 2.0 * y * L1;
	float F4 = pow(L1, 2) - pow(L2, 2) + pow(y, 2) + pow(x - L0, 2) - 2 * L1*(x - L0);

	float t1 = (E1 + sqrt(pow(E1, 2) - D1 * F1)) / D1;
	float t4 = (E4 + sqrt(pow(E4, 2) - D4 * F4)) / D4;

	buf[0] = 2 * atan(t1);
	buf[1] = 2 * atan(t4);
}

float map_between(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}