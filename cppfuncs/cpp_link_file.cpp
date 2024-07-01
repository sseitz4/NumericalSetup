#define MAIN
#include "myheader.h"

// all functions with "E X P O R T" can be called from Python via "model.cpp.solve(sol,par)", for example
EXPORT void solve(sol_struct *sol, par_struct *par){
    
    // loop backwards
    for(int t = par->T-1; t >= 0; t--){
        solution::solve_period(t,sol,par);
    }

}

EXPORT void simulate(sim_struct *sim, sol_struct *sol, par_struct *par){
    
    simulation::model(sim,sol,par);

}