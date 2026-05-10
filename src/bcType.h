// header guards
#ifndef BCTYPE_H
#define BCTYPE_H

#include "FileIO.H"

struct bcType{

    // --- member data --- //
    double Vm ; // transmembrane velocity
    double k; // diffusivity

    // --- constructor --- //
    bcType ();

    // --- member functions --- //
    void west( double y , double t , double & a , double & b , double & g ) const ;

    void east( double y , double t , double & a , double & b , double & g ) const ;

    void south( double x , double t , double & a , double & b , double & g ) const ;

    void north( double x , double t , double & a , double & b , double & g ) const ;

};

#endif