#include <iostream>
#include "MyVehicle.h"
#include "Vehicle.hpp"


using namespace std;


MyVehicle::MyVehicle()
{
}

MyVehicle::MyVehicle(float x_, float y_, float z_) {
	setX(x_);
	setY(y_);
	setZ(z_);

		//Draw Body of Vehicle
		//Addshape function executes the parameters given
		//Sets colour and position of each shape respect to same coordinates
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

		//Draw wheels of car, last 2 parameters give boolean if function is called in server
		Cylinder *Wheel1 = new Cylinder(2, 4, TRUE, TRUE);
		Wheel1->setPosition(6.5, 0, 5.5);
		Wheel1->setColor(0.5, 0.5, 0.5);
		addShape(Wheel1);

		Cylinder *Wheel2 = new Cylinder(2, 4, TRUE, TRUE);
		Wheel2->setPosition(6.5, 0, -5.5);
		Wheel2->setColor(0.5, 0.5, 0.5);
		addShape(Wheel2);

		Cylinder *Wheel3 = new Cylinder(2, 4, TRUE, FALSE);
		Wheel3->setPosition(-6.5, 0, -5.5);
		Wheel3->setColor(0.5, 0.5, 0.5);
		addShape(Wheel3);

		Cylinder *Wheel4 = new Cylinder(2, 4, TRUE, FALSE);
		Wheel4->setPosition(-6.5, 0, 5.5);
		Wheel4->setColor(0.5, 0.5, 0.5);
		addShape(Wheel4);

}

void MyVehicle::draw()
{

	glPushMatrix();
	positionInGL();
	setColorInGL();
		//Draw motion of wheels through vector *wheel to access steering and rolling in cylinder
		for (int i = 0; i < shapes.size(); i++)
		{
			Cylinder *wheel = dynamic_cast <Cylinder *>(shapes[i]);

			if (wheel != nullptr && wheel->isSteering == TRUE)
			{
				//if wheel steer function is activated, steer
				wheel->setRotation(steering); 
			}
			
			if (wheel != nullptr && wheel->isRolling == TRUE)
			{
				//if wheel rolling function is activated, roll
				wheel->setRolling(speed);
			}
			
			shapes[i]->draw();

		}

	glPopMatrix();
}

std::vector<Shape*> MyVehicle::getShapes()
{
	return std::vector<Shape*>();
}
