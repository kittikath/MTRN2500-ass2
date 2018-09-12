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
}; 

#endif TRIPRISM_H

