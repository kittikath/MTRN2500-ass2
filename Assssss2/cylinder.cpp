#include <iostream>
#include "cylinder.h"

#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>



using namespace std;
Cylinder::Cylinder(float x, float y, float z) {
	radius = x;
	length = y;
	slice = z;
}

void Cylinder::draw() 
{
	glPushMatrix();
		positionInGL();
		setColorInGL();
		glTranslated(0, radius, -length/2);
		GLUquadricObj *p = gluNewQuadric();
		gluCylinder(p, radius, radius, length, slice, 1);

		GLUquadric *c = gluNewQuadric();
		gluDisk(c, 0, radius, slice, 1);
        
		glTranslated(0,0,length);
		GLUquadric *d = gluNewQuadric();
		gluDisk(d, 0, radius, slice, 1);   

	

	glPopMatrix();


}