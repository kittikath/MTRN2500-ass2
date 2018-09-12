#include <iostream>
#include "MyVehicle.h"
#include "Vehicle.hpp"


using namespace std;

MyVehicle::MyVehicle()
{
}

MyVehicle::MyVehicle(float x_, float y_, float z_) {
	//X = x_;
	//Y = y_;
	//Z = z_;

	setX(x_);
	setY(y_);
	setZ(z_);

		//void addShape(Shape * shape);

		RecPrism *CarRec = new RecPrism(20, 4, 10);
		CarRec->setPosition(0, 3, 0);
		CarRec->setColor(1, 0, 0);
		addShape(CarRec);

		TriPrism *Tri = new TriPrism(2, 2, 10, 45);
		Tri->setPosition(-9, 7.5, 0);
		Tri->setColor(1, 1, 0);
		addShape(Tri);

		TrapPrism *CarTrap = new TrapPrism(12, 6, 10, 2, 2);
		CarTrap->setPosition(0, 7, 0);
		CarTrap->setColor(0, 1, 1);
		addShape(CarTrap);

		Cylinder *Wheel1 = new Cylinder(2, 4, 6, 0, 0);
//		Cylinder *cyl1 = dynamic_cast<Cylinder*>(Wheel1);
		Wheel1->setPosition(6.5, 0, 5.5);
		Wheel1->setColor(0.5, 0.5, 0.5);
//		Wheel1->setRotation(steering);
		addShape(Wheel1);

		Cylinder *Wheel2 = new Cylinder(2, 4, 6, 0, 0);
//		Cylinder *cyl2 = dynamic_cast<Cylinder*>(Wheel2);
		Wheel2->setPosition(6.5, 0, -5.5);
		Wheel2->setColor(0.5, 0.5, 0.5);
//		Wheel2->setRotation(steering);
		addShape(Wheel2);

		Cylinder *Wheel3 = new Cylinder(2, 4, 6, 0, 0);
//		Cylinder *cyl3 = dynamic_cast<Cylinder*>(Wheel3);
		Wheel3->setPosition(-6.5, 0, -5.5);
		Wheel3->setColor(1, 1, 1);
//		Wheel3->setRotation(steering);
		addShape(Wheel3);

		Cylinder *Wheel4 = new Cylinder(2, 4, 6, 0, 0);
		Wheel4->setPosition(-6.5, 0, 5.5);
		Wheel4->setColor(0.5, 0.5, 0.5);
//		Wheel4->setRotation(steering);
		addShape(Wheel4);

	//	Wheel1->setSteer(TRUE);
	//	Wheel2->setSteer(TRUE);
}

/*
void MyVehicle::addShape(Shape * shape) {
	addShape(shape);
}
*/

void MyVehicle::draw()
{

	glPushMatrix();
	positionInGL();
	setColorInGL();

	std::vector<Shape *>::iterator it;

//	Cylinder *cyl;
		for (it = shapes.begin(); it != shapes.end(); it++)
		{
	/*		if (dynamic_cast <Cylinder *> (*it)){
				dynamic_cast<Cylinder *>(*it) -> setSteer(getSteer());
				dynamic_cast<Cylinder *>(*it)->setRoll(-speed / dynamic_cast<Cylinder *>(*it) - getRadius() + dynamic_cast<Cylinder *> (*it)->getRolling());
			}*/
			(*it)->draw();
			//cyl = dynamic_cast<Cylinder*>(*it);
		//	if (cyl != nullptr)

		}
//	for (int i = 0; i < shapes.size(); i++) {
//		Cylinder *cyl = dynamic_cast<Cylinder*>(cyl);
//		shapes[i]->draw();	}

	

	glPopMatrix();
}

std::vector<Shape*> MyVehicle::getShapes()
{
	return std::vector<Shape*>();
}
