#include "simTime.h"
#include <iostream>
#include <iomanip>
#include <fstream>

// ---- constructor ----- //
simTime::simTime(){
    read();
    disp();
    time = startTime;
    timeStep = 0;
}

// ------ member functions ------- //
void simTime::read () {
    // read startTime , dt , Nt , and writeInterval from controlDict.inp
    std::ifstream infile;
    infile.open("input/controlDict.inp");

    if (!infile) {
        std::cout << "Error opening File\n";
        exit(1);
    }

    startTime = readDouble(infile);
    dt = readDouble(infile);
    Nt = readInt(infile);
    writeInterval = readInt(infile);
}

void simTime::disp() const {
    // display inputs read from controlDict.inp to the terminal
    std :: cout << "- -- Time Parameters -- -" << std :: endl ;
    std::cout << "startTime = " << startTime << std::endl;
    std::cout << "dt = " << dt << std::endl;
    std::cout << "Nt = " << Nt << std::endl;
    std::cout << "writeInterval = " << writeInterval << std::endl;
}

void simTime::advance() {
    timeStep = timeStep+1;
    time = time + dt;
}

bool simTime::run() const { return (timeStep < Nt);}

bool simTime::writeNow() const { return (timeStep % writeInterval == 0);}