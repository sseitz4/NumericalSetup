
// functions for solving model for singles.
#ifndef MAIN
#define SIMULATE
#include "myheader.h"
#endif

namespace simulation {

    void model(sim_struct *sim, sol_struct *sol, par_struct *par){
    
        #pragma omp parallel num_threads(par->num_threads)
        {
            #pragma omp for
            for (int i=0; i<par->simN; i++){
                for (int t=0; t < par->T; t++){
                    int it = index::d2(i,t,par->simN,par->T);
                    int it1 = index::d2(i,t+1,par->simN,par->T);

                    // a. initialize state variables
                    if (t==0){
                        // income
                        sim->P[it] = sim->P_init[i];
                        sim->Y[it] = sim->P[it]*sim->xi[it];

                        // assets
                        sim->a[it] = sim->a_init[i];
                        sim->A[it] = sim->a[it]*sim->P[it];
                        
                        // resources (normalized)
                        sim->M[it] = par->R*sim->A[it] + sim->Y[it];
                        sim->m[it] = sim->M[it]/sim->P[it];
                        
                        // Kids:
                        sim->Kids[it] = sim->kids_init[i];
                    } 

                    // b. interpolate optimal consumption (normalized)
                    // |C:| I think here is an error... Something in the interpolation goes wrong
                    int idx_interp = index::d2(t, 0,par->T, par->num_m);

                    if( sim->Kids[it] == 0) {
                        sim->c[it] = tools::interp_1d(par->grid_m,par->num_m,&sol->c_no[idx_interp],sim->m[it]);
                        sim->g_K[it] = tools::interp_1d(par->grid_m,par->num_m,&sol->g_Kids[idx_interp],sim->m[it]);
                    } else {
                       sim->c[it] = tools::interp_1d(par->grid_m,par->num_m,&sol->c_w[idx_interp],sim->m[it]);
                       sim->g_K[it] = 1;
                    }
                    
                    sim->V_no[it] = tools::interp_1d(par->grid_m,par->num_m,&sol->V_no[idx_interp],sim->m[it]);
                    sim->V_w[it] = tools::interp_1d(par->grid_m,par->num_m,&sol->V_w[idx_interp],sim->m[it]);

                    // c. Update next-period states
                    if (t<(par->T-1)){
                        sim->P[it1] = par->G*sim->P[it]*sim->psi[it1];
                        sim->Y[it1] = sim->P[it1]*sim->xi[it1];

                        sim->a[it1] = sim->m[it] - sim->c[it];
                        sim->A[it1] = sim->a[it1]*sim->P[it1];

                        sim->M[it1] = par->R*sim->A[it1] + sim->Y[it1];
                        sim->m[it1] = sim->M[it1]/sim->P[it1];

                        if (sim -> V_w[it] > sim-> V_no[it]){
                            sim->Kids[it1] = 1;
                        } else {
                            sim->Kids[it1] = 0;
                        }
                       /*if (sim -> g_K[it] > 0.5){
                            sim->Kids[it1] = 1;
                        } else {
                            sim->Kids[it1] = 0;
                        }*/

                        
                    }

                } // t
            } // i

        } // pragma

    } // simulate
}
