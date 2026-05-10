#include "velocityField.h"
#include "Time.h"
#include "FileIO.h"
#include <iostream>
#include <fstream>
#include <cmath>
#define M_PI 3.14159265359

using namespace std;

velocityField::velocityField( const meshType& Mesh ) {
    ifstream infile;
    infile.open("input/Fan.inp");

    if (!infile) {
        std::cout << "Error opening File\n";
        exit(1);
    }

    A = readDouble(infile);
    by = readInt(infile);
    bx = readInt(infile);

    infile.close();

    Lx = Mesh.Lx;
    Ly = Mesh.Ly;

    std::cout << "- -- Fan Parameters - --" << "\n";
    std::cout << " A = " <<  A << "\n ";
    std::cout << " bx = " << by << "\n ";
    std::cout << " by = " << bx << "\n ";
    
}

double velocityField::compU(double x, double y) const {
    return -A/(by*Ly) *std::sin((2*M_PI*x)/(bx*Lx))*std::cos((2*M_PI*y)/(by*Ly));
}

double velocityField::compV(double x, double y) const {
    return (A/(bx*Lx))*std::cos((2*M_PI*x)/(bx*Lx))*std::sin((2*M_PI*y)/(by*Ly));
}
