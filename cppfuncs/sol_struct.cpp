typedef struct sol_struct
{
 double* V;
 double* c;
 double* labor;
} sol_struct;

double* get_double_p_sol_struct(sol_struct* x, char* name){

 if( strcmp(name,"V") == 0 ){ return x->V; }
 else if( strcmp(name,"c") == 0 ){ return x->c; }
 else if( strcmp(name,"labor") == 0 ){ return x->labor; }
 else {return NULL;}

}


