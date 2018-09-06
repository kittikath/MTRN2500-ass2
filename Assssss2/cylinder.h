#ifndef CYLINDER_H
#define CYLINDER_H
#include "Shape.hpp"

class Cylinder : public Shape {

private:
	//set values
	float radius;
	float length;
	float slice;

public:
	Cylinder();
	Cylinder(float x, float y, float z);
	~Cylinder() = default;
	void draw();
}; 

#endif CYLINDER_H