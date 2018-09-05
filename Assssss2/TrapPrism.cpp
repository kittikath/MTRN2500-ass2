#include "TrapPrism.h"

#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

TrapPrism::TrapPrism(float a, float b, float d, float h, float offset) {
    al = a; // a length (length along base)
    bl = b; // b length (length of side)
    dl = d; // depth
    hl = h; //height
    os = offset; // offset
}

void TrapPrism::draw() 
{
    glPushMatrix();
    
    //bottom face :)
    glBegin(GL_QUADS);
        glVertex3f(-al / 2, 0, dl / 2);
        glVertex3f(al/2, 0, dl/2);
        glVertex3f(al/2, 0, -dl/2);
        glVertex3f(-al/2, 0, -dl/2);
    glEnd();

    // top face
    
    glBegin(GL_QUADS);
        glVertex3f((-al / 2) + os, hl, dl / 2);
        glVertex3f((al / 2) + os, hl,  dl / 2);
        glVertex3f((al / 2) + os, hl, -dl / 2);
        glVertex3f((-al / 2) + os, hl, -dl / 2);
    glEnd();

    // front face

    glBegin(GL_QUADS);
        glVertex3f((-al / 2), 0, dl / 2);
        glVertex3f((-al / 2) + os, hl,  dl / 2);
        glVertex3f((al / 2) + os, hl, dl / 2);
        glVertex3f((-al / 2), 0, dl / 2);
    glEnd();

        // back face

    glBegin(GL_QUADS);
        glVertex3f((-al / 2), 0, -dl / 2);
        glVertex3f((-al / 2) + os, hl,  -dl / 2);
        glVertex3f((al / 2) + os, hl, -dl / 2);
        glVertex3f((-al / 2), 0, -dl / 2);
    glEnd();

        // left side face

    glBegin(GL_QUADS);
        glVertex3f((-al / 2), 0, dl / 2);
        glVertex3f((-al / 2), 0,  -dl / 2);
        glVertex3f((-al / 2) + os, hl, -dl / 2);
        glVertex3f((-al / 2) + os, hl, dl / 2);
    glEnd();
    
        // right side face

    glBegin(GL_QUADS);
        glVertex3f((al / 2), 0, dl / 2);
        glVertex3f((al / 2), 0,  -dl / 2);
        glVertex3f((al / 2) + os, hl, -dl / 2);
        glVertex3f((al / 2) + os, hl, dl / 2);
    glEnd();
   

    glPopMatrix();
