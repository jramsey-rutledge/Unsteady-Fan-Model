// Libraries
#include "surfaceScalarField.h"
#include "meshType.h"
#include "volScalarField.h"
#include "velocityField.h"
#include <string>
#include <cmath>
#include <vector>
#include <math.h>

using namespace std;

// Defining surfaceScalarField member functions
void surfaceScalarField::allocate(const meshType& Mesh){
    Nx = Mesh.Nx;
    Ny = Mesh.Ny;
    phix.assign((Nx+1)*Ny,0.0);
    phiy.assign(Nx*(Ny+1),0.0);
}

double surfaceScalarField::getw(int i, int j) const {
    return phix[i-1 + (j-1)*(Nx+1)];
}

double surfaceScalarField::gete(int i, int j) const {
    return phix[i+(j-1)*(Nx+1)];
}

double surfaceScalarField::getn(int i, int j) const {
    return phiy[(i-1)+j*Nx];
}

double surfaceScalarField::gets(int i, int j) const {
    return phiy[(i-1)+(j-1)*Nx];
}

// Compute fluxes on east/west faces
void surfaceScalarField::computePhix(const meshType& Mesh, const volScalarField& T, const velocityField& U){
    int Nx = Mesh.Nx;
    int Ny = Mesh.Ny;
    for (int i=0; i<=Nx; i++){
        for (int j=0; j<Ny; j++){
            double x = Mesh.xf[i];
            double y = Mesh.yc[j+1];
            phix[i+j*(Nx+1)] = T.rho*U.compU(x,y);
        }
    }
}

// Compute fluxes on north/south faces
void surfaceScalarField::computePhiy(const meshType& Mesh, const volScalarField& T, const velocityField& U){
    int Nx = Mesh.Nx;
    int Ny = Mesh.Ny;
    for (int i=0; i<Nx; i++){
        for (int j=0; j<=Ny; j++){
            double x = Mesh.xc[i+1];
            double y = Mesh.yf[j];
            phiy[i+j*Nx] = T.rho*U.compV(x,y); 
        }
    }
}