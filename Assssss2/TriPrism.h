#ifndef TRIPRISM_H
#define TRIPRISM_H
#endif TRIPRISM_H

class TriPrism 
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
    /*double GetX();
    double GetY();
    double GetZ();
    void SetX(double xx);
    void SetY(double yy);
    void SetZ(double zz);*/
}; 



/*
FOR MAIN FUNCTION

    glColor3d(1, 0, 0);
    TriPrism Tri(10, 10, 10, 45);
    Tri.draw();


*/