#include <iostream>
#include "TriPrism.h"

#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define PI 3.14159265

// NEED TO INCLUDE MATH.H FOR SIN AND COS STUFF???

using namespace std;

TriPrism::TriPrism(float a, float b, float d, float theta) {
    al = a; // a length (length along base)
    bl = b; // b length (length of side)
    dl = d; // depth
    t = theta; // included angle between a and b
}

void TriPrism::draw() 
{
	t = t * (PI / 180);

    glPushMatrix();
	positionInGL();
	setColorInGL();

    //bottom face :)
    glBegin(GL_QUADS);
		//glColor3d(0, 1, 0);
        glVertex3f(-al / 2, 0, dl / 2);
        glVertex3f(al/2, 0, dl/2);
        glVertex3f(al/2, 0, -dl/2);
        glVertex3f(-al/2, 0, -dl/2);
    glEnd();

    // front face
    
    glBegin(GL_QUADS);
		//glColor3d(0, 1, 0);
        glVertex3f(-al / 2, 0, dl / 2);
        glVertex3f((bl*cos(t))-(al/2), bl*sin(t),  dl / 2);
        glVertex3f(al / 2, 0, dl / 2);
		glVertex3f(al / 2, 0, dl / 2);
    glEnd();

        // back face
    
    glBegin(GL_QUADS);
		//glColor3d(0, 1, 0);
        glVertex3f(-al / 2, 0, -dl / 2);
        glVertex3f((bl*cos(t))-(al/2), bl*sin(t),  -dl / 2);
        glVertex3f(al / 2, 0, -dl / 2);
		glVertex3f(al / 2, 0, -dl / 2);
    glEnd();

         // left side face
    
    glBegin(GL_QUADS);
		//glColor3d(1, 1, 0);
        glVertex3f(-al / 2, 0, dl / 2);
        glVertex3f(-al / 2, 0, -dl / 2);
        glVertex3f((bl*cos(t))-(al/2), bl*sin(t),  -dl / 2);
        glVertex3f((bl*cos(t))-(al/2), bl*sin(t),  dl / 2);
    glEnd();

         // right side face
    
    glBegin(GL_QUADS);
		//glColor3d(0, 1, 1);
        glVertex3f(al / 2, 0, dl / 2);
        glVertex3f(al / 2, 0, -dl / 2);
        glVertex3f((bl*cos(t))-(al/2), bl*sin(t),  -dl / 2);
        glVertex3f((bl*cos(t))-(al/2), bl*sin(t),  dl / 2);
    glEnd();

    glPopMatrix();

}