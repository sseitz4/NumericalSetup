// functions related to utility and environment.
#ifndef MAIN
#define UTILS
#include "myheader.h"
#endif

namespace utils {

    double util(double cons, int number_kids, par_struct *par){
        // CRRA utility function
        return pow((cons/(1.0 + 0.3 * number_kids)), 1.0-par->rho)/(1.0-par->rho) + par-> util_kids * number_kids;
    }
    
}