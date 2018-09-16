#include <iostream>
#include "cylinder.h"
#include "Vehicle.hpp"

#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define	PI 3.14159265
//#define slice 6

using namespace std;

Cylinder::Cylinder(float x, float y, bool isRolling_, bool isSteering_) {
	radius = x;
	length = y;
	isRolling = isRolling_;
	isSteering = isSteering_;
	angle = 0;
}



void Cylinder::draw()
{
	float slice = 6;
//	double angle = 0;

	glPushMatrix();
	positionInGL();



	setColorInGL();

	glTranslated(0, radius, -length / 2);
//	cout << angle << endl;

	glRotated(angle, 0, 0, 1);

	GLUquadricObj *p = gluNewQuadric();
	gluCylinder(p, radius, radius, length, slice, 1);

	GLUquadric *c = gluNewQuadric();
	gluDisk(c, 0, radius, slice, 1);

	glTranslated(0, 0, length);
	GLUquadric *d = gluNewQuadric();
	gluDisk(d, 0, radius, slice, 1);

	glPopMatrix();
}

void Cylinder::setRolling(double speed_)
{
	angle = (speed_ / radius)*(180 / PI) + angle;
}

double Cylinder::GetR() {
	return radius;
}
double Cylinder::GetL() {
	return length;
}
bool Cylinder::GetisRolling() {
	return isRolling;
}
bool Cylinder::GetisSteering() {
	return isSteering;
}
void Cylinder::SetisRolling(bool setRoll) {
	isRolling = setRoll;
}
void Cylinder::SetisSteering(bool setSteer) {
	isSteering = setSteer;
}
void Cylinder::SetX(double xx) {
	radius = xx;
}

void Cylinder::SetY(double yy) {
	length = yy;
}