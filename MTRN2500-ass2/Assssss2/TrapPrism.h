// Code written by Group 30: Kate O'Sullivan (z5161671) and Kath-Lin Han (z5165314)

#ifndef TRAPPRISM_H
#define TRAPPRISM_H

#include "Shape.hpp"

// Class defining trapezium prism, derived from 'Shape' class
class TrapPrism : public Shape
{
private:
    float al; // a length (width of bottom base)
    float bl; // b length (width of top base)
    float dl; // depth (thickness of prism)
    float hl; // height
    float os; // offset (how far from the left edge of bottom base should the top base left edge be)

public:
	// initialises functions to be used in .cpp file
    TrapPrism(float a, float b, float d, float h, float offset);
    ~TrapPrism() = default;
    void draw();
	double GetX();
	double GetY();
	double GetDepth();
	double GetHeight();
	double GetOffset();
	void SetX(double xx);
	void SetY(double yy);
	void SetDepth(double dd);
	void SetHeight(double hh);
	void SetOffset(double oo);
}; 

#endif TRAPPRISM_H
