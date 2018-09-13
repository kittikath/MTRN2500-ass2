#ifndef MYVEHICLE_H
#define MYVEHICLE_H


#include "RecPrism.h"
#include "TrapPrism.h"
#include "TriPrism.h"
#include "cylinder.h"
#include "Vehicle.hpp"
//#include "Wheel.h"

#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class MyVehicle : public Vehicle {
	private:
		float X;
		float Y;
		float Z;

	public:
		MyVehicle();
		MyVehicle(float x_, float y_, float z_);
		~MyVehicle() = default;
		void draw();
		//void addShape(Shape *shape);
		std::vector<Shape *>getShapes();
		
};

#endif MYVEHICLE_H
