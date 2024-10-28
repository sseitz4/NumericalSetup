typedef struct par_struct
{
 double R;
 double rho;
 double beta;
 int Max_num_kids;
 int T;
 int num_m;
 double max_m;
 double G;
 double sigma_psi;
 double sigma_xi;
 int num_psi;
 int num_xi;
 int simN;
 int seed;
 int num_threads;
 double* grid_m;
 double* grid_psi;
 double* psi_w;
 double* grid_xi;
 double* xi_w;
 int num_shocks;
} par_struct;

double get_double_par_struct(par_struct* x, char* name){

 if( strcmp(name,"R") == 0 ){ return x->R; }
 else if( strcmp(name,"rho") == 0 ){ return x->rho; }
 else if( strcmp(name,"beta") == 0 ){ return x->beta; }
 else if( strcmp(name,"max_m") == 0 ){ return x->max_m; }
 else if( strcmp(name,"G") == 0 ){ return x->G; }
 else if( strcmp(name,"sigma_psi") == 0 ){ return x->sigma_psi; }
 else if( strcmp(name,"sigma_xi") == 0 ){ return x->sigma_xi; }
 else {return NAN;}

}


int get_int_par_struct(par_struct* x, char* name){

 if( strcmp(name,"num_kids") == 0 ){ return x->num_kids; }
 else if( strcmp(name,"T") == 0 ){ return x->T; }
 else if( strcmp(name,"num_m") == 0 ){ return x->num_m; }
 else if( strcmp(name,"num_psi") == 0 ){ return x->num_psi; }
 else if( strcmp(name,"num_xi") == 0 ){ return x->num_xi; }
 else if( strcmp(name,"simN") == 0 ){ return x->simN; }
 else if( strcmp(name,"seed") == 0 ){ return x->seed; }
 else if( strcmp(name,"num_threads") == 0 ){ return x->num_threads; }
 else if( strcmp(name,"num_shocks") == 0 ){ return x->num_shocks; }
 else {return -9999;}

}


double* get_double_p_par_struct(par_struct* x, char* name){

 if( strcmp(name,"grid_m") == 0 ){ return x->grid_m; }
 else if( strcmp(name,"grid_psi") == 0 ){ return x->grid_psi; }
 else if( strcmp(name,"psi_w") == 0 ){ return x->psi_w; }
 else if( strcmp(name,"grid_xi") == 0 ){ return x->grid_xi; }
 else if( strcmp(name,"xi_w") == 0 ){ return x->xi_w; }
 else {return NULL;}

}


