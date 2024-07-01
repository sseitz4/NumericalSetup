////////////////
// 1. generic //
////////////////

#include <windows.h>
#include <cmath>
#include <stdio.h>
#include <omp.h>

#include "nlopt-2.4.2-dll64\nlopt.h"

///////////////
// 2. custom //
///////////////
#define EXPORT extern "C" __declspec(dllexport) 
// needed for Python link!

////////////////
// 3. structs //
////////////////

#include "par_struct.cpp"
#include "sol_struct.cpp"
#include "sim_struct.cpp"

////////////////
// 4. Globals //
////////////////
#define woman 1 // not used, but to illustrate
#define man 2

////////////////
// 5. Logs    //
////////////////
#include "logs.cpp"

/////////////////
// 6. includes //
/////////////////
#ifndef INDEX
#include "index.cpp"
#endif
#ifndef UTILS
#include "utils.cpp"
#endif
#ifndef TOOLS
#include "tools.cpp"
#endif
#ifndef SOLUTION
#include "solve.cpp"
#endif
#ifndef SIMULATE
#include "simulate.cpp"
#endif