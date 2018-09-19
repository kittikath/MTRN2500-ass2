// Code written by Group 30: Kate O'Sullivan (z5161671) and Kath-Lin Han (z5165314)

#include <iostream>
#include "RecPrism.h"
#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

RecPrism::RecPrism(float x, float y, float z) {
	// In the constructor the parameters given are converted into known variables
	xl = x;
	yl = y;
	zl = z;
}

// Function that draws an arbitrary rectangular prism
void RecPrism::draw() {
	glPushMatrix(); // Ensures that the rectangle will be drawn from the origin
	positionInGL(); // This function is called to move the entirety of the shape to a new origin
	setColorInGL(); // This function is called to change the colour of the prism
	
	// Bottom Face, made up of four points, each point with an x, y and z coordinate
	glBegin(GL_QUADS);
		glVertex3f(-xl / 2, 0, zl / 2);
		glVertex3f(xl/2, 0, zl/2);
		glVertex3f(xl/2, 0, -zl/2);
		glVertex3f(-xl/2, 0, -zl/2);
	glEnd();

	// Top Face
	glBegin(GL_QUADS);;
		glVertex3f(-xl / 2, yl, zl / 2);
		glVertex3f(xl / 2, yl,  zl / 2);
		glVertex3f(xl / 2, yl, -zl / 2);
		glVertex3f(-xl / 2, yl, -zl / 2);
	glEnd();

	// Left Side Face
	glBegin(GL_QUADS);
		glVertex3f(-xl / 2, 0, zl / 2);
		glVertex3f(-xl / 2, 0, -zl / 2);
		glVertex3f(-xl / 2, yl, -zl / 2);
		glVertex3f(-xl / 2, yl, zl / 2);
	glEnd();

	// Right Side Face
	glBegin(GL_QUADS);
		glVertex3f(xl / 2, 0, zl / 2);
		glVertex3f(xl / 2, 0, -zl / 2);
		glVertex3f(xl / 2, yl, -zl / 2);
		glVertex3f(xl / 2, yl, zl / 2);
	glEnd();

	// Front Face
	glBegin(GL_QUADS);
		glVertex3f(-xl / 2, 0, zl / 2);
		glVertex3f(-xl / 2, yl, zl / 2);
		glVertex3f(xl / 2, yl, zl / 2);
		glVertex3f(xl / 2, 0, zl / 2);
	glEnd();

	// Back Face
	glBegin(GL_QUADS);
		glVertex3f(-xl / 2, 0, -zl / 2);
		glVertex3f(-xl / 2, yl, -zl / 2);
		glVertex3f(xl / 2, yl, -zl / 2);
		glVertex3f(xl / 2, 0, -zl / 2);
	glEnd();

	// Resets the coordinate system so as to not affect other external functions
	glPopMatrix();
}

// The Get functions are used to retrieve parameters locally initialised
double RecPrism::GetX() {
	return xl;
}

double RecPrism::GetY() {
	return yl;
}

double RecPrism::GetZ() {
	return zl;
}

// The Set functions are used to set parameters
// Primarily used when sending vehicle and receiving other vehicles from server
void RecPrism::SetX(double xx) {
	xl = xx;
}

void RecPrism::SetY(double yy) {
	yl = yy;
}

void RecPrism::SetZ(double zz) {
	zl = zz;
}
