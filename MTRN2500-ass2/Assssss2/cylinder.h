#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.hpp"
#include "Vehicle.hpp"

class Cylinder : public Shape
{
private:
	float radius; // distance from centre to circumference of circle
	float length; // depth/thickness of cylinder
	bool rolling; // parameter is TRUE (1) if the cylinder is meant to roll (wheel) and FALSE (0) if not
	bool steering; // paraemter is TRUE (1) if the cylinder is meant to steer (front wheels) and FALSE (0) if not
	double angle; // angle is used to determine rolling speed of wheel

public:
	// initialises functions to be used
	Cylinder(float x, float y, bool isSteering_, bool isRolling_);
	~Cylinder() = default;
	void draw();
	void setRadius(double radius);
	double getRadius();
	double getSteer();
	double steer;
	void setRolling(double speed_);
	void wheelRotation();
	void wheelSteering();
	bool isRolling;
	bool isSteering;
	double GetX();
	double GetY();
	bool getisrolling();
	bool getissteering();
	void SetX(double xx);
	void SetY(double yy);
	void setisrolling(bool setRoll);
	void setissteering(bool setSteer);
};
#endif CYLINDER_H
