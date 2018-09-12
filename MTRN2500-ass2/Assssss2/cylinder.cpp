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

Cylinder::Cylinder(float x, float y, float z, bool isRolling, bool isSteering) {
	radius = x;
	length = y;
	slice = z;
	//this->isRolling = NULL;
	//this->isSteering = NULL;
	rolling = isRolling;
	steering = isSteering;
}



void Cylinder::draw()
{
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

	glPopMatrix();

}

/*

void Cylinder::setSteer (double steering)
{
	this->steering = steering;
}

double Cylinder::getSteer()
{
	return steering;
}

void Cylinder::setRoll(double rolling)
{
	this->rolling = rolling;
}

double Cylinder::getRolling()
{
	return rolling;
}

bool Cylinder::isRoll()
{
	if (getRolling() != 0) {
		return true;
	}
	return false;
}

void Cylinder::setRolling(bool setRoll)
{
	rolling = setRoll;
}

bool Cylinder::isSteer()
{
	if (getSteer != 0) {
		return true;
	}
	return false;
}

void Cylinder::setSteering(bool setSteer)
{
	steering = setSteer;
}


		/*if (speed > 0) {
			isrolling = 1;
			glRotated(angle, 0, 0, 1);


ShapeParameter->CylinderParameters->isRolling 
			bool isRolling;	// needs to roll with vehicle?
			bool isSteering;// needs to steer with vehicle?

		} */

		




/* void Cylinder::setroll(double speed) {
	// Update angle
	float angle = 0;
	// angular velovity = velocity/radius
	float angvel = speed / radius;
	// curent angle  = angle velocity + last angle 
	angle = angvel + angle;
	// current angle value goes to glrotated
} */
