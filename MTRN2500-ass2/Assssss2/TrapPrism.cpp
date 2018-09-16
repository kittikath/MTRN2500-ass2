// Code written by Group 30: Kate O'Sullivan (z5161671) and Kath-Lin Han (z5165314)

#include "TrapPrism.h"

#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

TrapPrism::TrapPrism(float a, float b, float d, float h, float offset) {
 	// In the constructor the parameters given are converted into known variables
    al = a;		
    bl = b;		
    dl = d;			
    hl = h;		
    os = offset; 
}

// Function that draws arbitrary trapezium prism
void TrapPrism::draw() {
	// difference in length of bottom and top base needed to translate top base to left
	// so with offset = 0, the left edges of the bases are aligned (same x-coordinate)
	float diff = (al - bl) / 2;  
	
	glPushMatrix(); // Ensures that the trapezium will be drawn from the origin
	positionInGL(); // Moves the entirety of the shape to a new origin
	setColorInGL(); // Changes the colour of the prism

	// Bottom Face, made up of four points, each point with an x, y and z coordinate
	glBegin(GL_QUADS);
		glVertex3f(-al / 2, 0, dl / 2);
		glVertex3f(al / 2, 0, dl / 2);
		glVertex3f(al / 2, 0, -dl / 2);
		glVertex3f(-al / 2, 0, -dl / 2);
	glEnd();

	// Top Face
	glBegin(GL_QUADS);
		glVertex3f((-bl / 2) - diff + os, hl, dl / 2);
		glVertex3f((bl / 2) - diff + os, hl, dl / 2);
		glVertex3f((bl / 2) - diff + os, hl, -dl / 2);
		glVertex3f((-bl / 2) - diff + os, hl, -dl / 2);
	glEnd();

	// Front Face
	glBegin(GL_QUADS);
		glVertex3f((-al / 2), 0, dl / 2);
		glVertex3f((-bl / 2) - diff + os, hl, dl / 2);
		glVertex3f((bl / 2) - diff + os, hl, dl / 2);
		glVertex3f((al / 2), 0, dl / 2);
	glEnd();

	// Back Face
	glBegin(GL_QUADS);
		glVertex3f((-al / 2), 0, -dl / 2);
		glVertex3f((-bl / 2) - diff + os, hl, -dl / 2);
		glVertex3f((bl / 2) - diff + os, hl, -dl / 2);
		glVertex3f((al / 2), 0, -dl / 2); 
	glEnd();

	// Left Side Face
	glBegin(GL_QUADS);
		glVertex3f((-al / 2), 0, dl / 2);
		glVertex3f((-al / 2), 0, -dl / 2);
		glVertex3f((-bl / 2) - diff + os, hl, -dl / 2);
		glVertex3f((-bl / 2) - diff + os, hl, dl / 2);
	glEnd();

	// Right Side Face
	glBegin(GL_QUADS);
		glVertex3f((al / 2), 0, dl / 2);
		glVertex3f((al / 2), 0, -dl / 2);
		glVertex3f((bl / 2) - diff + os, hl, -dl / 2);
		glVertex3f((bl / 2) - diff + os, hl, dl / 2);
	glEnd();

	// Resets the coordinate system so as to not affect other external functions
	glPopMatrix();
}

// The Get functions are used to retrieve parameters locally initialised
double TrapPrism::GetA() {
	return al;
}

double TrapPrism::GetB() {
	return bl;
}

double TrapPrism::GetDepth() {
	return dl;
}

double TrapPrism::GetHeight() {
	return hl;
}

double TrapPrism::GetOffset() {
	return os;
}

// The Set functions are used to set parameters
// Primarily used when sending vehicle and receiving other vehicles from server
void TrapPrism::SetX(double xx) {
	al = xx;
}

void TrapPrism::SetY(double yy) {
	bl = yy;
}

void TrapPrism::SetDepth(double dd) {
	dl = dd;
}

void TrapPrism::SetHeight(double hh) {
	hl = hh;
}

void TrapPrism::SetOffset(double oo) {
	os = oo;
}