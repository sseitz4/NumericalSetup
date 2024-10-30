// functions related to utility and environment.
#ifndef MAIN
#define UTILS
#include "myheader.cpp"
#endif

namespace utils {

    double util(double cons, double labor, par_struct *par){
        
        // Time endowment -> Translate labor into leisure:
        double leisure = 0.0;
        if (labor == 0){
            double leisure = par->Time_end;
        } else {
            double leisure = par->Time_end - labor - par->theta;
        }
        // CRRA utility function
        return pow((cons * leisure) , 1.0-par->rho)/(1.0-par->rho);
    }
    
}