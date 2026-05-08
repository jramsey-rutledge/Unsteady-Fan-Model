// header file

// header guards
#ifndef VOLSCALARFIELD_H
#define VOLSCALARFIELD_H

// libraries
#include <vector>
#include <string>
#include "bcType.h"
#include "fieldVal.h"

// define classes
class meshType;
class Time;


// Define volScalarField structure
struct volScalarField {
    double rho, cp, k;            // thermophysical properties
    int Nx, Ny;                   // grid resolution
    int Ntot;                     // total number of nodes
    std::vector<double> values;   // scalar field values
    std::string name;             // field name
    bcType BC;                    // boundary conditions
    fieldVal t1;                  // T^(n+1)
    fieldVal t0;                  // T^n
    fieldVal F;                   // source term
    double dt;                    // time step

    void read();

    void dispInputs() const;
    
    void allocate(const meshType& Mesh);

    // constructors
    volScalarField();
    volScalarField(std::string fieldName);
    volScalarField(std::string fieldName, const meshType& Mesh);

    double get(int i, int j) const ;

    void set(int i, int j, double val) ;

    void Save(double t);

    void setUniformIC(double val);

    // update source
    void setSource(const meshType& Mesh, const Time& runTime);

    void update();
    
    double residual();
};

#endif