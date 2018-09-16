// Code written by Group 30: Kate O'Sullivan (z5161671) and Kath-Lin Han (z5165314)

#ifndef RECPRISM_H
#define RECPRISM_H

#include "Shape.hpp"
 
// Class defining rectangluar prism, derived from 'Shape' class
class RecPrism : public Shape
{
private:
	// establishing parameters that determine size of prism
	float xl; // length along x-axis (width)
	float yl; // length along y-xis (height)
	float zl; // length along z-axis (depth/thickness of prism)

public:
	// initialises functions to be used in .cpp file
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
