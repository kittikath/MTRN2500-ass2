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

//	float angle;
	bool rolling;
	bool steering;
	double roll;

	double angle;
	double store;


public:
	Cylinder();
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

	//double lastAngle;
	//double newAngle;
};




#endif CYLINDER_H
/*
#ifndef MTRN3500_CYLINDER_H
#define MTRN3500_CYLINDER_H
#include <iostream>
#include "Shape.hpp"


using namespace std;

class Cylinder : public Shape {

public:
	Cylinder(float Length, float Radius, int sides);
	virtual void draw();
	virtual void CylinderDraw();
	void setSize(float Length, float Radius, int sides);
	Cylinder();
	float getRadius();

protected:

	float length, radius;
	int sides;

};


#endif // for MTRN3500_SHAPE_H
/*
private:
	//set values
	float radius;
	float length;
	float slice;
	float angle;
	//	bool rolling;
	//	bool steering;
	double roll;

public:
	Cylinder();
	Cylinder(float x, float y, bool isSteering, bool isRolling);

	~Cylinder() = default;

	void draw();

	void wheelRotation();
	void wheelSteering();
	void wheelDraw();
	//	void draw();
	bool rolling;
	bool steering;
	void setRolling(double roll);
	float getRoll();
};
*/