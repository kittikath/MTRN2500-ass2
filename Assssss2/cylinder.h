#ifndef CYLINDER_H
#define CYLINDER_H


class Cylinder {

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