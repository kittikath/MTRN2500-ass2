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

	float angle;
	bool rolling;
	bool steering;
	double roll;

public:
	Cylinder();
	Cylinder(float x, float y, bool isSteering, bool isRolling);

	~Cylinder() = default;

	void draw();

	void setRadius(double radius);
	double getRadius();

//	void setSteer(double steering);
	double getSteer();
	double steer;
	
//	void setRoll(double rolling);
//	void getRoll();
//	void getRadius();
//	double getSteer;
	//	bool isRoll();
	//	bool isSteer();
	//	void setRolling(bool setRoll);
	//	void setSteering(bool setSteer);

	//bool setSpin();
	//bool roll();
	//float setroll(double speed);
	void wheelRotation();
	void wheelSteering();
	//void wheelDraw();
	//	void draw();
	bool isRolling;
	bool isSteering;
	//void setRolling(double roll);

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