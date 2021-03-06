﻿#ifndef TRAPPRISM_H
#define TRAPPRISM_H
#include "Shape.hpp"

class TrapPrism : public Shape
{
private:
    float al; // base lenghth
    float bl; // top length
    float dl; // depth
    float hl; // height
    float os; // offset

public:
    //TrapPrism();
    TrapPrism(float a, float b, float d, float h, float offset);
    ~TrapPrism() = default;
    void draw();
	double GetA();
	double GetB();
	double GetDepth();
	double GetHeight();
	double GetOffset();
	void SetA(double aa);
	void SetB(double bb);
	void SetDepth(double dd);
	void SetHeight(double hh);
	void SetOffset(double oo);
}; 

#endif TRAPPRISM_H
