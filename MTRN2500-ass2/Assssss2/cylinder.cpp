// Code written by Group 30: Kate O'Sullivan (z5161671) and Kath-Lin Han (z5165314)

#include <iostream>
#include "cylinder.h"
#include "Vehicle.hpp"

#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define	PI 3.14159265

using namespace std;

Cylinder::Cylinder(float x, float y, bool isRolling_, bool isSteering_) {
	// In the constructor the parameters given are converted into known variables
	radius = x;
	length = y;
	isRolling = isRolling_;
	isSteering = isSteering_;
	angle = 0;
}

// Function that draws an arbitrary cylinder
void Cylinder::draw() {
	float slice = 6; // slice is defined as how many triangles make up the face, the more triangle, the more resemblance to a complete circle

	glPushMatrix(); // Ensures that the shape will be drawn from the origin
	positionInGL(); //Moves the entirety of the shape to a new origin
	setColorInGL(); // Changes the colour of the cylinder

	glTranslated(0, radius, -length / 2); // sets cylinder's bottom point on 'floor' (where x = 0)

	glRotated(angle, 0, 0, 1); // variable 'angle' changes when car is moving forward or backwards to roll the wheel

	// Draw curved surface to connect two faces
	GLUquadricObj *p = gluNewQuadric();
	gluCylinder(p, radius, radius, length, slice, 1);

	// Front Face
	GLUquadric *c = gluNewQuadric();
	gluDisk(c, 0, radius, slice, 1);

	// Back Face
	glTranslated(0, 0, length);
	GLUquadric *d = gluNewQuadric();
	gluDisk(d, 0, radius, slice, 1);

	glPopMatrix(); // Resets the coordinate system
}

// Sets the 'speed' at which the wheel 'rolls' (rotates about z-axis) at
// Converts speed into angular velocity in degrees
void Cylinder::setRolling(double speed_) {
	angle = (speed_ / radius)*(180 / PI) + angle; 
}

// The Get functions are used to retrieve parameters locally initialised
double Cylinder::GetR() {
	return radius;
}
double Cylinder::GetL() {
	return length;
}
bool Cylinder::getisrolling() {
	return isRolling;
}
bool Cylinder::getissteering() {
	return isSteering;
}

// The Set functions are used to set parameters
// Primarily used when sending vehicle and receiving other vehicles from server
void Cylinder::setisrolling(bool setRoll) {
	isRolling = setRoll;
}
void Cylinder::setissteering(bool setSteer) {
	isSteering = setSteer;
}
void Cylinder::SetX(double xx) {
	radius = xx;
}

void Cylinder::SetY(double yy) {
	length = yy;
}