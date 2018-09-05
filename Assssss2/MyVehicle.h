#ifndef MYVEHICLE_H
#define MYVEHICLE_H


#include "RecPrism.h"
#include "TrapPrism.h"
#include "TriPrism.h"
#include "cylinder.h"
#include "Vehicle.hpp"

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
		MyVehicle(float x, float y, float z);
		~MyVehicle() = default;
		void draw();
	
};

#endif MYVEHICLE_H
