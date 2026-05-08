#include "linSysType.h"
#include "meshType.h"
#include "surfaceScalarField.h"
#include "volScalarField.h"
#include "velocityField.h"
#include "Time.h"
#include <iostream>

// matrixType Member Functions Defined 
// Initialize
linSysType::linSysType(const meshType& Mesh){
    Nx = Mesh.Nx ;
    Ny = Mesh.Ny ;
    Nx2 = Nx + 2;
    Ny2 = Ny + 2;
    B = Eigen::VectorXd::Zero( Nx2 * Ny2 ); // initialize RHS
    X = Eigen :: VectorXd :: Zero ( Nx2 * Ny2 ); // initialize solution
}

// add a matrix entry at row , col
void linSysType::addEntry ( int row , int col , double val ){
    ROW.push_back ( row );
    COL.push_back ( col );
    VAL.push_back ( val );
}

// set RHS at cell (i , j )
void linSysType::setRHS( int i , int j , double val ){
    B[ i + j * Nx2 ] = val ;
}

// get RHS at cell (i , j )
double linSysType::getRHS( int i , int j ) const {
    return B[ i + j * Nx2 ];
}

// Clears matrix
void linSysType::resetA() {
    B.setZero();
    VAL.assign(VAL.size(),0.0);
}

// Function to build a sparse matrix
void linSysType::buildA(const meshType& Mesh, const surfaceScalarField& flux, const volScalarField& C, const Time& runTime) {
    double dx = Mesh.dx;
    double dy = Mesh.dy;
    int row ;
    double a,b,g;
    double t = runTime.time;

    // south / north boundary conditions
    for (int i = 1; i <= Nx; i++) {
        // south
        row = i ;
        C.BC.south(Mesh.xc[i],t,a,b,g);
        addEntry(row,row,0.5*a+b/dy);
        addEntry(row,row + Nx2,0.5*a-b/dy);

        // north
        row = (Ny2-1)* Nx2 + i;
        C.BC.north(Mesh.xc[i],t,a,b,g);
        addEntry(row,row,0.5*a+b/dy);
        addEntry(row,row - Nx2,0.5*a-b/dy);
    }

    // east / west boundary conditions
    for (int j = 1; j <= Ny; j++) {
    // west 
        row = j * Nx2;
        C.BC.west(Mesh.yc[j],t,a,b,g);
        addEntry(row,row,0.5*a+b/dx);
        addEntry(row,row+1, 0.5*a-b/dx);

    // east
        row = (j+1) * Nx2 - 1;
        C.BC.east(Mesh.yc[j],t,a,b,g);
        addEntry(row,row,a*0.5+b/dx);
        addEntry(row,row-1,a*0.5-b/dx);
    }

    // 5-point stencil
    double ae = C.k*dy/dx;
    double aw = C.k*dy/dx;
    double an = C.k*dx/dy;
    double as = C.k*dx/dy;

    double ap = ae + aw + an + as;

    // unsteady term
    double dt = runTime.dt;
    double a_time = C.rho * C.cp * dx * dy / dt;

    for (int i = 1; i <= Nx; i++) {
        for (int j = 1; j <= Ny; j++) {

            row = j * Nx2 + i;

            double phi_e = flux.gete(i,j);
            double phi_w = flux.getw(i,j);
            double phi_s = flux.gets(i,j);
            double phi_n = flux.getn(i,j);

            double Fe = C.cp*phi_e*dy;
            double Fw = C.cp*phi_w*dy;
            double Fs = C.cp*phi_s*dx;
            double Fn = C.cp*phi_n*dx;

            double cE = 0.5*Fe;
            double cW = -0.5*Fw;
            double cS = -0.5*Fs;
            double cN = 0.5*Fn;
            double cP = 0.5*(Fe-Fw+Fn-Fs);

            // Center
            addEntry(row,row,ap+cP+a_time); 

            // East
            addEntry(row,row+1,-ae+cE);

            // West
            addEntry(row,row-1,-aw+cW);

            // North
            addEntry(row,row+Nx2,-an+cN);

            // South
            addEntry(row,row-Nx2,-as+cS);
        }
    }

    // extraneous nodes
    addEntry(0,0,1.0);
    addEntry(Nx+1,Nx+1,1.0);
    addEntry((Ny2-1)*Nx2,(Ny2-1)*Nx2,1.0);
    addEntry(Nx2*Ny2-1,Nx2*Ny2-1,1.0);

}

// Build right - hand side vector
void linSysType::buildRHS( const meshType& Mesh, const volScalarField& C, const Time& runTime ){
    double a,b,g;
    double t = runTime.time;
    t=t;
    
    // south / north boundary conditions
    for ( int i = 1; i <= Nx ; i++){
    
        C.BC.south(Mesh.xc[i],t,a,b,g);
        setRHS(i,0,g);

        C.BC.north(Mesh.xc[i],t,a,b,g);
        setRHS(i,Ny2-1,g);
        
    }

    // east / west boundary conditions
    for ( int j = 1; j <= Ny ; j ++){

        C.BC.east(Mesh.yc[j],t,a,b,g);
        setRHS(Nx2-1,j,g);

        C.BC.west(Mesh.yc[j],t,a,b,g);
        setRHS(0,j,g);
    }

    // internal nodes
    for (int i = 1; i <= Nx; i++){
        for (int j = 1; j <= Ny; j++){
            setRHS(i, j, (C.rho*C.cp*Mesh.dx*Mesh.dy/runTime.dt )* C.t0.get(i,j));
        }
    }

}

// Solve Matrix
void linSysType::solve( volScalarField & T){
    // solve system using prefactorized LU
    X = solver.solve(B);
    // check if successful
    if (solver.info () != Eigen::Success){
        std::cerr << " Solving failed !\n ";
        return ;
    }

    // load solution into volScalarField T . t1
    for ( int j = 0; j < Ny2 ; ++ j) {
        for ( int i = 0; i < Nx2 ; ++ i) {
            T.t1.set(i , j , X[i + j * Nx2 ]);
        }
    }
}


void linSysType::factorize () {
    int Ntot = Nx2*Ny2 ;

    // load matrix
    Eigen::SparseMatrix < double > A( Ntot , Ntot );
    std::vector < Eigen :: Triplet < double >> triplets ;
    triplets.reserve (VAL.size ());
    for ( size_t k = 0; k < VAL . size (); ++ k) { triplets.emplace_back ( ROW [k] , COL [k] , VAL [ k ]);}
    A.setFromTriplets ( triplets.begin (), triplets.end ());
    A.makeCompressed ();

    // compute the LU factorization of A
    solver.compute(A);
    if( solver.info() != Eigen::Success ) {
        std::cerr << " Decomposition failed !\n "; 
        return;
    }
}