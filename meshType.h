// header file

// header guards
#ifndef MESHTYPE_H
#define MESHTYPE_H

#include <fstream>
#include <sstream>
#include <vector>
#include "FileIO.h"


// structure definitons
struct meshType {
    int Nx, Ny;                   // number of cells
    double Lx, Ly;                // domain dimensions
    double dx, dy;                // cell sizes
    std::vector<double> xc, yc;   // cell-center coordinates
    std::vector<double> xf, yf;   // face centroids

// function prototypes
/**
 * @brief read a file and save it to a mesh
 * 
 * @param Mesh passed by reference to read
 */
void read();

/**
 * @brief constructor of Mesh grid
 * 
 * @param Mesh passed by reference to make a copy
 */
void create();

/**
 * @brief print dimensions of grid and domain size
 * 
 * @param Mesh passed by reference 
 */
void disp();

/**
 * @brief save xc and yc to files
 * 
 * @param Mesh passed by reference 
 */
void write();

/**
 * @brief constructor
 * 
 * @param 
 */
meshType();

};

#endif