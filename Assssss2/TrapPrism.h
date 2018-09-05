#ifndef TRAPPRISM_H
#define TRAPPRISM_H

class TrapPrism 
{

private:
    //set values
    float al; // base lenghth
    float bl; // top length
    float dl; // depth
    float hl; // height
    float os; // offset
	float red;
	float green;
	float blue;

public:
    TrapPrism();
    TrapPrism(float a, float b, float d, float h, float offset, float r, float g, float blu);
    ~TrapPrism() = default;
    void draw();
    /*double GetX();
    double GetY();
    double GetZ();
    void SetX(double xx);
    void SetY(double yy);
    void SetZ(double zz);*/
}; 

#endif TRAPPRISM_H
