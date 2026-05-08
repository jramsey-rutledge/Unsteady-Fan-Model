// header guards
#ifndef VELOCITYFIELD_H
#define VELOCITYFIELD_H

#include "meshType.h"

struct velocityField{
    // --- member data --- //
    double Lx,Ly; // dimensions of the room
    double A; // velocity of fan
    int bx,by; // parameters of the fan

    // --- member functions --- //
    velocityField ( const meshType & Mesh );
    double compU (double x, double y) const;
    double compV (double x, double y) const;

};
#endif