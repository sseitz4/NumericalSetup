#ifndef MAIN
#define SOLUTION
#include "myheader.cpp"
#endif

namespace solution {

    double value_of_choice(double cons,double m, double* V_next, par_struct* par){

        // flow-utility
        double Util = utils::util(cons,par);

        // savings
        double savings = m - cons;

        // penalty for borrowing
        double penalty = 0.0;
        if (savings < 0.0){
            penalty = savings * 1000.0; // very high penalty for borrowing

            cons = m - 1.0e-6; // consume all resources
            savings = 1.0e-6; // no savings
        }
        
        // expected continuation value
        double EV_next = 0.0;
        for (int i_shock=0; i_shock<par->num_shocks; i_shock++){
            
            double fac = par->G*par->grid_psi[i_shock]; // normalization factor

            // interpolate next period value function for this combination of transitory and permanent income shocks
            double m_next = par->R*savings/fac + par->grid_xi[i_shock];
            double V_next_interp = tools::interp_1d(par->grid_m,par->num_m,V_next,m_next);
            V_next_interp = pow(fac , (1.0-par->rho)) * V_next_interp; // normalization factor

            // add to expectation
            double prob = par->psi_w[i_shock]*par->xi_w[i_shock];
            EV_next += prob*V_next_interp;
            
        }
        
        
        // return discounted sum
        return Util + par->beta*EV_next + penalty;
    }

    typedef struct {
        double m;             
        double *V_next;               
        par_struct *par;      

    } solver_struct;

    double objfunc_wrap(unsigned n, const double *x, double *grad, void *solver_data_in){
        // This is a wrapper for NLopt.

        // unpack
        solver_struct *solver_data = (solver_struct *) solver_data_in;  
        
        double cons = x[0];
        double m = solver_data->m;
        par_struct *par = solver_data->par;

        return - value_of_choice(cons,m,solver_data->V_next,par); // negative since we minimize

    }



    void solve_period(int t, int n_kids,sol_struct *sol,par_struct *par){
        
        if (t == (par->T-1)){
            // terminal period: consume all resources
            for (int iM=0; iM<par->num_m;iM++){
                int idx = index::d2(t,iM,par->T,par->num_m);
                
                double m = par->grid_m[iM];
                for(int iNkids = 0; iNkids <par->Max_num_kids, iNkids++){
                    sol->c[idx] = m;
                    sol->V[idx] = utils::util(sol->c[idx],par);
                }
            }

        } else {

            // setup parallel region. after this, each thread will have its own copy of the solver_data object.
            #pragma omp parallel num_threads(par->num_threads)
            {

                // 1. allocate objects for solver. 
                solver_struct* solver_data = new solver_struct;
                
                int const dim = 1;
                double lb[dim],ub[dim],x[dim];
                
                auto opt = nlopt_create(NLOPT_LN_BOBYQA, dim); //different types of solvers: NLOPT_LN_BOBYQA,NLOPT_LD_MMA NLOPT_LD_LBFGS NLOPT_GN_ORIG_DIRECT
                double minf=0.0;

                // 2. loop over resources (in parallel)
                #pragma omp for
                for (int iM=0; iM<par->num_m;iM++){
                    int idx = index::d2(t,iM,par->T,par->num_m);
                    int idx_next = index::d2(t+1,iM,par->T,par->num_m);
                    int idx_next_interp = index::d2(t+1,0,par->T,par->num_m);
                    
                    // resources
                    double m = par->grid_m[iM];
                    
                    // search over optimal total consumption, C
                    solver_data->m = m;
                    solver_data->V_next = &sol->V[idx_next_interp];
                    solver_data->par = par;
                    nlopt_set_min_objective(opt, objfunc_wrap, solver_data); 

                    // bounds
                    lb[0] = 1.0e-6;
                    ub[0] = m-1.0e-6; // cannot borrow
                    nlopt_set_lower_bounds(opt, lb);
                    nlopt_set_upper_bounds(opt, ub);

                    // optimize
                    x[0] = sol->c[idx_next]*0.98; // initial value is last period's consumption
                    nlopt_optimize(opt, x, &minf); 

                    // store results
                    sol->c[idx] = x[0];
                    sol->V[idx] = -minf;  // negative since we minimize   
                    
                } // iM

                // 4. destroy optimizer
                nlopt_destroy(opt);
                delete solver_data;

            } // pragma
            
        }   // period-check
        
    } // solve function


}
