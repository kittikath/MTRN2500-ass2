#ifndef TRIPRISM_H
#define TRIPRISM_H
#include "Shape.hpp"

class TriPrism : public Shape
{

	private:
		//set values
		float al;
		float bl;
		float dl;
		float t;

	public:
		TriPrism();
		TriPrism(float a, float b, float d, float theta);
		~TriPrism() = default;
		void draw();
}; 

#endif TRIPRISM_H

