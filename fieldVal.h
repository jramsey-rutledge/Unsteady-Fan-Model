#ifndef FIELDVAL_H
#define FIELDVAL_H

#include <vector>

struct fieldVal {

    int Nrow;
    int Ncol;
    std::vector <double> values;

    void allocate( int N , int M );

    void set( int i , int j , double val );

    double get(int i, int j) const;

};

#endif