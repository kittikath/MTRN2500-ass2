#include <iostream>
#include "cylinder.h"

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
	//this->isRolling = NULL;
	//this->isSteering = NULL;
	isRolling = isRolling_;
	isSteering = isSteering_;
}



void Cylinder::draw()
{
	float slice = 6;
	glPushMatrix();
	positionInGL();
	setColorInGL();

	glTranslated(0, radius, -length / 2);
	GLUquadricObj *p = gluNewQuadric();
	gluCylinder(p, radius, radius, length, slice, 1);

	GLUquadric *c = gluNewQuadric();
	gluDisk(c, 0, radius, slice, 1);

	glTranslated(0, 0, length);
	GLUquadric *d = gluNewQuadric();
	gluDisk(d, 0, radius, slice, 1);

		// set something with the angle
		// glRotated (angle + radisu *2 or something, 0, 0, 1)

	glPopMatrix();
}




/* void Cylinder::setroll(double speed) {
	// Update angle
	float angle = 0;
	// angular velovity = velocity/radius
	float angvel = speed / radius;
	// curent angle  = angle velocity + last angle 
	angle = angvel + angle;
	// current angle value goes to glrotated
} */
