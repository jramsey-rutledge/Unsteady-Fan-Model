#ifndef TIME_H
#define TIME_H

#include "FileIO.h"

struct Time{

// --- member data --- //
double startTime; // initial time ( for restarts )
double dt; // time step size
int Nt; // total number of time steps
int writeInterval; // output frequency
double time; // current simulation time
int timeStep; // current time step number

// --- constructor --- //
Time();

// --- member functions --- //
void read(); // read time parameters from file
void disp() const ; // display time inputs to terminal
void advance(); // increment time and Timestep
bool run() const; // continue running?
bool writeNow() const; // write output now?


};

#endif