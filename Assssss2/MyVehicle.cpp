#include <iostream>
#include "MyVehicle.h"


using namespace std;

MyVehicle::MyVehicle(float x_, float y_, float z_) {
	X = x_;
	Y = y_;
	Z = z_;
}

void MyVehicle::draw()
{

//	glTranslated(X, Y, Z);
	
	glPushMatrix();
	positionInGL();
	setColorInGL();

		RecPrism CarRec(20, 4, 10);
		CarRec.setPosition(0, 3, 0);
		CarRec.setColor(1, 0, 0);
		CarRec.draw();
	
		TriPrism CarTri(2, 2, 10, 90);
		CarTri.setPosition(-9, 7, 0);
		CarTri.setColor(1, 0, 0);
		CarTri.draw();

		TrapPrism CarTrap(12, 6, 10, 2, 2); // a, b, d, h, o
		CarTrap.setPosition(0, 7, 0);
		CarTrap.setColor(0, 1, 1);
		CarTrap.draw();


		Cylinder CarCyl1(2, 4, 20);
		CarCyl1.setPosition(6.5, 0, 5.5);
		CarCyl1.setColor(0.5, 0.5, 0.5);
		CarCyl1.draw();

		Cylinder CarCyl2(2, 4, 20);
		CarCyl2.setPosition(6.5, 0, -5.5);
		CarCyl2.setColor(0.5, 0.5, 0.5);
		CarCyl2.draw();

		Cylinder CarCyl3(2, 4, 20);
		CarCyl3.setPosition(-6.5, 0, -5.5);
		CarCyl3.setColor(0.5, 0.5, 0.5);
		CarCyl3.draw();

		Cylinder CarCyl4(2, 4, 20);
		CarCyl4.setPosition(-6.5, 0, 5.5);
		CarCyl4.setColor(0.5, 0.5, 0.5);
		CarCyl4.draw();

	glPopMatrix();


};