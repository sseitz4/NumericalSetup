// functions related to utility and environment.
#ifndef MAIN
#define UTILS
#include "myheader.cpp"
#endif

namespace utils {

    double util(double cons,par_struct *par){
        // CRRA utility function
        return pow(cons , 1.0-par->rho)/(1.0-par->rho);
    }
    
}