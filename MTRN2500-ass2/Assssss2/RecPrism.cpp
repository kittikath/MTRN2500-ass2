#include <iostream>
#include "RecPrism.h"
#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>



using namespace std;
RecPrism::RecPrism()
{
}
RecPrism::RecPrism(float x, float y, float z) {
	xl = x;
	yl = y;
	zl = z;
}

void RecPrism::draw() 
{
	glPushMatrix();
	positionInGL();
	setColorInGL();
	
	//bottom face :)
	glBegin(GL_QUADS);
		glVertex3f(-xl / 2, 0, zl / 2);
		glVertex3f(xl/2, 0, zl/2);
		glVertex3f(xl/2, 0, -zl/2);
		glVertex3f(-xl/2, 0, -zl/2);
	glEnd();

	// top face
	glBegin(GL_QUADS);;
		glVertex3f(-xl / 2, yl, zl / 2);
		glVertex3f(xl / 2, yl,  zl / 2);
		glVertex3f(xl / 2, yl, -zl / 2);
		glVertex3f(-xl / 2, yl, -zl / 2);
	glEnd();

	// left side face
	glBegin(GL_QUADS);
		glVertex3f(-xl / 2, 0, zl / 2);
		glVertex3f(-xl / 2, 0, -zl / 2);
		glVertex3f(-xl / 2, yl, -zl / 2);
		glVertex3f(-xl / 2, yl, zl / 2);
	glEnd();

	// right side face

	glBegin(GL_QUADS);
//		glColor3d(0, 1, 0);
		glVertex3f(xl / 2, 0, zl / 2);
		glVertex3f(xl / 2, 0, -zl / 2);
		glVertex3f(xl / 2, yl, -zl / 2);
		glVertex3f(xl / 2, yl, zl / 2);
	glEnd();

	// front face

	glBegin(GL_QUADS);
//		glColor3d(0, 0, 1);
		glVertex3f(-xl / 2, 0, zl / 2);
		glVertex3f(-xl / 2, yl, zl / 2);
		glVertex3f(xl / 2, yl, zl / 2);
		glVertex3f(xl / 2, 0, zl / 2);
	glEnd();

	// back face

	glBegin(GL_QUADS);
//		glColor3d(0, 0, 1);
		glVertex3f(-xl / 2, 0, -zl / 2);
		glVertex3f(-xl / 2, yl, -zl / 2);
		glVertex3f(xl / 2, yl, -zl / 2);
		glVertex3f(xl / 2, 0, -zl / 2);
	glEnd();

	

	glPopMatrix();
	

	//need to reset to reset coordinate system
	//can reverse functions done previously
	//or store the original coordinate system in the stack and then push it on to the stack and remove from the stack after editing
	//use push and pop

	//TO DO: 5 additional + header files (one for each dshape and vehicle) and then be able to draw each shape


}

double RecPrism::GetX()
{
	return xl;
}

double RecPrism::GetY()
{
	return yl;
}

double RecPrism::GetZ()
{
	return zl;
}

void RecPrism::SetX(double xx)
{
	xl = xx;
}

void RecPrism::SetY(double yy)
{
	yl = yy;
}

void RecPrism::SetZ(double zz)
{
	zl = zz;
}
