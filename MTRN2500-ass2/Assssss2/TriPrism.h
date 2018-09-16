// Code written by Group 30: Kate O'Sullivan (z5161671) and Kath-Lin Han (z5165314)

#ifndef TRIPRISM_H
#define TRIPRISM_H
#include "Shape.hpp"

// Class defining triangular prism, derived from 'Shape' class
class TriPrism : public Shape
{
private:
	// setting parameters that determine size of prism
	float al;	// base length
	float bl;	// left side length length
	float dl;	// depth/thickness of prism
	float t;	// theta (angle between al and bl)

public:
	// initialises functions to be used
	TriPrism(float a, float b, float d, float theta);
	~TriPrism() = default;
	void draw();
	double GetX();
	double GetY();
	double GetZ();
	double GetAngle();
	void SetX(double xx);
	void SetY(double yy);
	void SetZ(double zz);
	void SetAngle(double qq);
}; 

#endif TRIPRISM_H


