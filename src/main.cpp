/* MEGN 651: Modeling Unsteady Advection-Diffusion
 *
 * Author: Jenna Ramsey-Rutledge
 *
 * In this code, we build a advection-diffusion solver to handle an unsteady problem. This particular code can model a room with a fan and heater.
 */

// Libraries
#include "meshType.h"
#include "volScalarField.h"
#include "surfaceScalarField.h"
#include "velocityField.h"
#include "simTime.h"
#include "linSysType.h"
#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <cmath> 
#include <vector>

using namespace std;

// Main Function
int main() {

    // - - - - - - - - - preprocessing - - - - - - - - - -//

    // initialize runTime
    simTime runTime;

    // Create Mesh
    meshType Mesh;

    // Initialize T
    volScalarField T("T", Mesh);
    T.setUniformIC(295); 

    // Create velocity field
    velocityField U(Mesh);

    // Create flux
    surfaceScalarField flux;
    flux.allocate(Mesh);
    flux.computePhix(Mesh,T,U);
    flux.computePhiy(Mesh,T,U);

    // assemble and factorize the sparse matrix
    linSysType linSyst(Mesh);
    linSyst.buildA(Mesh,flux,T,runTime);
    linSyst.factorize();

    // 
    std::cout << "- -- Outputs -- -" << std::endl;

    // ---------- the time loop - - - - - - - - -//
    double res = 1;

    while ( runTime.run() ) {

        // advance time
        runTime.advance();

        // recompute fluxes
        flux.computePhix(Mesh, T, U);
        flux.computePhiy(Mesh, T, U);

        // rebuild matrix (velocity changed!)
        linSyst.resetA();   
        linSyst.buildA(Mesh, flux, T, runTime);

        // refactorize
        linSyst.factorize();

        // rebuild RHS
        linSyst.buildRHS(Mesh, T, runTime);

        // solve
        linSyst.solve(T);

        // compute residual
        if (runTime.writeNow()) {

            res = T.residual();

            std::cout
                << "Time = " << runTime.time
                << " Residual = "
                << std::setprecision(8)
                << res << "\n";
        }

        // update solution
        T.update();

        // save 
        if (runTime.writeNow()){
            T.Save(runTime.time);
        }
    }

    return 0;
}