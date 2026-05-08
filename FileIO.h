// header file

// header guards
#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>
#include <sstream>
#include <vector>

/**
 * @brief helper function that reads a file and saves a line without
 * the description as an integer
 * 
 * @param infile file being read
 */
int readInt(std::ifstream& infile);

/**
 * @brief helper function that reads a file and saves a line without
 * the description as a double
 * 
 * @param infile file being read
 */
double readDouble( std::ifstream& infile);

#endif