#ifndef TRIPRISM_H
#define TRIPRISM_H
#include "Shape.hpp"

class TriPrism : public Shape
{
	private:
		float al;	// base length
		float bl;	// top length
		float dl;	// depth
		float t;	// theta

	public:
		//TriPrism();
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


