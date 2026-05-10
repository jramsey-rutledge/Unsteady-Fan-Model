#ifndef LINSPACETYPE_H
#define LINSPACETYPE_H

#include <vector>
#include <Eigen/Sparse>
#include <Eigen/SparseLU>

class meshType;
class surfaceScalarField;
class volScalarField;
class velocityField;
class simTime;

// structure
struct linSysType {

    // members
    Eigen::SparseLU < Eigen::SparseMatrix<double> > solver;
    double Nx,Ny,Nx2,Ny2;
    std::vector<int> ROW ;      // row indices of nonzeros
    std::vector<int> COL ;      // column indices of nonzeros
    std::vector<double> VAL ;   // values of nonzeros
    Eigen::VectorXd B;          // right-hand side vector
    Eigen::VectorXd X;          // solution vector

    // methods
    linSysType(const meshType& Mesh);
    void addEntry(int row, int col, double val);
    void setRHS(int i, int j, double val);
    double getRHS(int i, int j) const;
    void resetA();
    void buildA(const meshType& Mesh, const surfaceScalarField& flux, const volScalarField& C, const simTime& runTime);
    void buildRHS( const meshType& Mesh, const volScalarField& C, const simTime& runTime);
    void factorize();
    void solve(volScalarField& T);

};

#endif