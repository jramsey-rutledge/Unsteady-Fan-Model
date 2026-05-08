#include "FileIO.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <math.h>
using namespace std;

// function definitions
int readInt( ifstream& infile ) {
    int value;
    string line;
    getline(infile, line);
    stringstream(line) >> value;
    return value;
}

double readDouble( ifstream& infile ) {
    double value;
    string line;
    getline(infile, line);
    stringstream(line) >> value;
    return value;
}