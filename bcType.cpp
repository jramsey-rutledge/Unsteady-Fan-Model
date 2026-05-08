#include "bcType.h"
#include <fstream>
#include <cmath>
#include <iostream>


// --- constructor --- //
bcType :: bcType (){
    // display for verification
    std :: cout << "- -- BC Info -- -" << std :: endl ;
    std :: cout << " East Window " << std :: endl ;
    std :: cout << " South Door"   << std :: endl ;

}

// west boundary condition
void bcType::west( double y, double t, double& a, double& b, double& g) const {
    a = 0.0; // coefficient multiplying T
    b = 1.0; // coefficient multiplying dT / dx
    g = 0.0;
    t=t;
    y=y;
}

// east boundary condition
void bcType::east( double y, double t, double& a, double& b, double& g) const {
    if (0.70<y && y<0.90) {
        a = 1.0;
        b = 0.0;
        g = 300.0;
    }
    else {
        a = 0.0; // coefficient multiplying T
        b = 1.0; // coefficient multiplying dT / dx
        g = 0.0;
    }
    t=t;
}

// north boundary condition
void bcType::north( double x, double t, double& a, double& b, double& g) const {
    a = 0.0;
    b = 1.0; // coefficient multiplying dT / dx
    g = 0.0;
    t=t;
    x=x;
}

// south boundary condition
void bcType::south( double x, double t, double& a, double& b, double& g) const {
    a = 1.0; // coefficient multiplying T
    b = 0.0; // coefficient multiplying dT / dx
    if (0.2<x && x<0.4) {
        a = 1.0;
        b = 0.0;
        g = 290.0;
    }
    else {
        a = 0.0;
        b = 1.0;
        g = 0.0;
    }
    t=t;
}