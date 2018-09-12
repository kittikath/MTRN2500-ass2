#ifndef TRAPPRISM_H
#define TRAPPRISM_H
#include "Shape.hpp"

class TrapPrism : public Shape
{
private:
    float al; // base lenghth
    float bl; // top length
    float dl; // depth
    float hl; // height
    float os; // offset

public:
    //TrapPrism();
    TrapPrism(float a, float b, float d, float h, float offset);
    ~TrapPrism() = default;
    void draw();
}; 

#endif TRAPPRISM_H
