#include "fieldVal.h"

void fieldVal::allocate( int N , int M ) {
    Nrow = N;
    Ncol = M;
    values.assign (N*M,0);
}

void fieldVal::set( int i , int j , double val ) {
    values [i + j * Nrow ] = val ;
}

double fieldVal::get( int i , int j) const {
    return values [ i + j* Nrow ];
}