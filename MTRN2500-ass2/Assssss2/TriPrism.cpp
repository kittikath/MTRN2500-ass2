// Code written by Group 30: Kate O'Sullivan (z5161671) and Kath-Lin Han (z5165314)

#include <iostream>
#include "TriPrism.h"

#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define PI 3.14159265

using namespace std;

TriPrism::TriPrism(float a, float b, float d, float theta) {
	// In the constructor the parameters given are converted into known variables
    al = a; 
    bl = b;
    dl = d;
    t = theta;
}

// Function that draws an arbitrary triangular prism
void TriPrism::draw() {
	t = t * (PI / 180); // Need to convery theta from degrees to radians for geometry

	glPushMatrix(); // Ensures that the prism will be drawn from the origin
	positionInGL(); // Moves the entirety of the shape to a new origin
	setColorInGL(); // Changes the colour of the prism

    // Bottom Face
    glBegin(GL_QUADS);
        glVertex3f(-al / 2, 0, dl / 2);
        glVertex3f(al/2, 0, dl/2);
        glVertex3f(al/2, 0, -dl/2);
		glVertex3f(-al/2, 0, -dl/2);
    glEnd();

    // Front Face
    glBegin(GL_TRIANGLES);
        glVertex3f(-al / 2, 0, dl / 2);
        glVertex3f((bl*cos(t))-(al/2), bl*sin(t),  dl / 2);
		glVertex3f(al / 2, 0, dl / 2);
    glEnd();

	// Back Face
    glBegin(GL_TRIANGLES);
        glVertex3f(-al / 2, 0, -dl / 2);
        glVertex3f((bl*cos(t))-(al/2), bl*sin(t),  -dl / 2);
        glVertex3f(al / 2, 0, -dl / 2);;
    glEnd();

	// Left Side Face
    glBegin(GL_QUADS);
        glVertex3f(-al / 2, 0, dl / 2);
        glVertex3f(-al / 2, 0, -dl / 2);
        glVertex3f((bl*cos(t))-(al/2), bl*sin(t),  -dl / 2);
        glVertex3f((bl*cos(t))-(al/2), bl*sin(t),  dl / 2);
    glEnd();

	// Right Side Face
    glBegin(GL_QUADS);
        glVertex3f(al / 2, 0, dl / 2);
        glVertex3f(al / 2, 0, -dl / 2);
        glVertex3f((bl*cos(t))-(al/2), bl*sin(t),  -dl / 2);
        glVertex3f((bl*cos(t))-(al/2), bl*sin(t),  dl / 2);
    glEnd();

	// Resets the coordinate system so as to not affect other external functions
    glPopMatrix();
}

// The Get functions are used to retrieve parameters locally initialised
double TriPrism::GetX() {
	return al;
}

double TriPrism::GetY() {
	return bl;
}

double TriPrism::GetZ() {
	return dl;
}

double TriPrism::GetAngle() {
	return t;
}

// The Set functions are used to set parameters
// Primarily used when sending vehicle and receiving other vehicles from server
void TriPrism::SetX(double xx) {
	al = xx;
}

void TriPrism::SetY(double yy) {
	bl = yy;
}

void TriPrism::SetZ(double zz) {
	dl = zz;
}

void TriPrism::SetAngle(double qq) {
	t = qq;
}