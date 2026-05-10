// Libraries
#include "meshType.h"
#include "volScalarField.h"
#include "FileIO.h"
#include "bcType.h"
#include "fieldVal.h"
#include "simTime.h"
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <iostream>
#include <math.h>
#define _USE_MATH_DEFINES

using namespace std;

void volScalarField::read(){
    std :: ifstream file ;
    file.open (name + ".inp");
    rho = readDouble ( file );
    cp = readDouble ( file );
    k = readDouble ( file );
    file.close ();

    std::ifstream file2; 
    file2.open("controlDict.inp");
    readDouble(file2); // disregard starttime
    dt = readDouble(file2);
    file2.close();
}

void volScalarField::dispInputs() const {
    std::cout << "- -- " << name << " inputs - --" << "\n";
    std::cout << " rho = " << rho << "\n ";
    std::cout << " cp = " << cp << "\n ";
    std::cout << " k = " << k << "\n ";
    std::cout << "dt = " << dt << "\n";
}

void volScalarField::allocate(const meshType& Mesh) {
    Nx = Mesh.Nx;
    Ny = Mesh.Ny;
    Ntot = (Nx+2)*(Ny+2);
    values.assign(Ntot, 0.0);

    t1.allocate (Nx +2 , Ny +2);
    t0.allocate (Nx +2 , Ny +2);
    F.allocate (Nx +2 , Ny +2); // allocate source term
}

// Constructors
volScalarField::volScalarField(){
    name = "T";
    read();
    dispInputs();
}

volScalarField::volScalarField(string fieldName){
    name = fieldName;
    read();
    dispInputs();
}

volScalarField::volScalarField(string fieldName, const meshType& Mesh){
    name = fieldName;
    read();
    dispInputs();
    allocate(Mesh);
}

// Getters and Setters
double volScalarField::get(int i, int j) const {
    return values[i+j*(Nx+2)];
}

void volScalarField::set(int i, int j, double val) {
    values[i+j*(Nx+2)] = val;
}

// Save final results
void volScalarField::Save(double t) {
    std::string filename = "output/" + name + "_" + std::to_string(t) + ".dat";
    std::ofstream cfile(filename);
    cfile << std::scientific << std::setprecision(16);
    for (int i = 0; i < Nx+2; i++) {
        for (int j=0; j < Ny+2; j++){
            cfile << t1.get(i,j) << "\n";
        }
    }
    cfile.close();
}

void volScalarField::setUniformIC( double val) {
    for ( int i = 1; i <= Nx+1 ; i++) {
        for ( int j = 1; j <= Ny+1 ; j++) {
            t0.set (i , j, val); // set value in T^n
        }
    }
}

void volScalarField::setSource( const meshType& Mesh, const simTime& runTime) {
    double t = runTime.time;
    double omega = 6.2831853;
    for ( int i = 1; i <= Nx ; i ++) {
        for ( int j = 1; j <= Ny ; j ++) {
            double x = Mesh.xc[i];
            double y = Mesh.yc[j];

            double term_time = -omega * cos(x)*cos(y)*sin(omega*t);

            double term_adv = cos(omega*t) * (pow(sin(x),2)*pow(cos(y),2)-pow(cos(x),2)*pow(sin(y),2));

            double term_diff = 2.0 * cos(x)*cos(y)*cos(omega*t);

            double f = rho*cp*term_time + rho*cp*term_adv + k*term_diff;
            
            F.set(i,j,f);
        }
    }
}

double volScalarField::residual() {
    double Tmax = 0.0;

    for (int i=1; i <= Nx; i++) {
        for (int j=1; j <= Ny; j++) {
            double val = std::abs((t1.get(i,j) - t0.get(i,j)) / dt);
            Tmax = std::max(Tmax, val);
        }
    }

    return Tmax;
}

void volScalarField::update() {
    t0 = t1;
}
