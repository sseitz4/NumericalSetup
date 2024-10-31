typedef struct sim_struct
{
 double* c;
 double* m;
 double* a;
 double* C;
 double* M;
 double* A;
 double* P;
 double* Y;
 int* Kids;
 double* a_init;
 double* P_init;
 double* xi;
 double* psi;
 int* kids_init;
 double* kids_update;
} sim_struct;

double* get_double_p_sim_struct(sim_struct* x, char* name){

 if( strcmp(name,"c") == 0 ){ return x->c; }
 else if( strcmp(name,"m") == 0 ){ return x->m; }
 else if( strcmp(name,"a") == 0 ){ return x->a; }
 else if( strcmp(name,"C") == 0 ){ return x->C; }
 else if( strcmp(name,"M") == 0 ){ return x->M; }
 else if( strcmp(name,"A") == 0 ){ return x->A; }
 else if( strcmp(name,"P") == 0 ){ return x->P; }
 else if( strcmp(name,"Y") == 0 ){ return x->Y; }
 else if( strcmp(name,"a_init") == 0 ){ return x->a_init; }
 else if( strcmp(name,"P_init") == 0 ){ return x->P_init; }
 else if( strcmp(name,"xi") == 0 ){ return x->xi; }
 else if( strcmp(name,"psi") == 0 ){ return x->psi; }
 else if( strcmp(name,"kids_update") == 0 ){ return x->kids_update; }
 else {return NULL;}

}


int* get_int_p_sim_struct(sim_struct* x, char* name){

 if( strcmp(name,"Kids") == 0 ){ return x->Kids; }
 else if( strcmp(name,"kids_init") == 0 ){ return x->kids_init; }
 else {return NULL;}

}


