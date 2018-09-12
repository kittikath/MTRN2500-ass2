#ifndef RECPRISM_H
#define RECPRISM_H

#include "Shape.hpp"


class RecPrism : public Shape
{

private:
	//set values
	float xl;
	float yl;
	float zl;

public:
	RecPrism();
	RecPrism(float x, float y, float z);
	~RecPrism() = default;
	void draw();
	double GetX();
	double GetY();
	double GetZ();
	void SetX(double xx);
	void SetY(double yy);
	void SetZ(double zz);
}; 

#endif RECPRISM_H
