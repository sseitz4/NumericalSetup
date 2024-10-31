typedef struct sol_struct
{
 double* V_no;
 double* c_no;
 double* V_w;
 double* c_w;
 double* V_int;
 double* g_Kids;
} sol_struct;

double* get_double_p_sol_struct(sol_struct* x, char* name){

 if( strcmp(name,"V_no") == 0 ){ return x->V_no; }
 else if( strcmp(name,"c_no") == 0 ){ return x->c_no; }
 else if( strcmp(name,"V_w") == 0 ){ return x->V_w; }
 else if( strcmp(name,"c_w") == 0 ){ return x->c_w; }
 else if( strcmp(name,"V_int") == 0 ){ return x->V_int; }
 else if( strcmp(name,"g_Kids") == 0 ){ return x->g_Kids; }
 else {return NULL;}

}


