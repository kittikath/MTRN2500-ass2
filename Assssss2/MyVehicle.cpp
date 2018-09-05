#include <iostream>
#include "MyVehicle.h"


using namespace std;

MyVehicle::MyVehicle(float x, float y, float z) {
	X = x;
	Y = y;
	Z = z;
}

void MyVehicle::draw()
{

	glTranslated(X, Y, Z);
	
	glPushMatrix();
		glColor3d(1, 0, 0);
		glTranslated(0, 5, 0);
		RecPrism CarRec(20, 8, 10);
		CarRec.draw();
	glPopMatrix();
	
	glPushMatrix();
		glTranslated(13, 5, 0);
		glColor3d(0, 1, 0);
		TriPrism CarTri(6, 8, 10, 90);
		CarTri.draw();
	glPopMatrix();

	glPushMatrix();
		glTranslated(0, 13, 0);
		TrapPrism CarTrap(10, 4, 10, 4, -3, 0, 1, 1);
		CarTrap.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(8, 0, 4);
//		glColor3d(1, 0, 1);
		Cylinder cyl1(2.5, 2, 20);
		cyl1.draw();
	glPopMatrix();

	glPushMatrix();
		glTranslated(8, 0, -4);
//		glColor3d(1, 0, 1);
		Cylinder cyl2(2.5, 2, 20);
		cyl2.draw();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-8, 0, 4);
//		glColor3d(1, 0, 1);
		Cylinder cyl3(2.5, 2, 20);
		cyl3.draw();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-8, 0, -4);
//		glColor3d(1, 0, 1);
		Cylinder cyl4(2.5, 2, 20);
		cyl4.draw();
	glPopMatrix();
};