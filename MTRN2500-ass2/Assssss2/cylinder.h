#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.hpp"
#include "Vehicle.hpp"

class Cylinder : public Shape
{
private:
	//set values
	float radius;
	float length;
	float slice;
	float angle;
	bool rolling;
	bool steering;

public:
	Cylinder();
	Cylinder(float x, float y, float z, bool isSteering, bool isRolling);
	
	~Cylinder() = default;

	void draw();

	void setRadius(double radius);
	double getRadius();
	
	void setSteer(double steering);
	double getSteer();
	void setRoll(double rolling);
	double getRoll();

	bool isRoll();
	bool isSteer();
	void setRolling(bool setRoll);
	void setSteering(bool setSteer);

	//bool setSpin();
	//bool roll();
	//float setroll(double speed);
}; 



#endif CYLINDER_H

