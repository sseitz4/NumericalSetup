// functions for calculating linear indices.
#ifndef MAIN
#define INDEX
#include "myheader.cpp"
#endif

namespace index {
    
    int d2(int i_x1, int i_x2, int Nx1, int Nx2){
        int i_grid = i_x1*Nx2
                        + i_x2;
        return i_grid;
    }

    int d3(int i_x1, int i_x2, int i_x3, int Nx1, int Nx2, int Nx3){

        int i_grid = (i_x1*Nx2
                        + i_x2)*Nx3
                        + i_x3;
        return i_grid;
    }

    int d4(int i_x1, int i_x2, int i_x3, int i_x4, int Nx1, int Nx2, int Nx3, int Nx4){

        int i_grid = ((i_x1*Nx2
                        + i_x2)*Nx3
                        + i_x3)*Nx4
                        + i_x4;
        return i_grid;
    }

    int d5(int i_x1, int i_x2, int i_x3, int i_x4, int i_x5, int Nx1, int Nx2, int Nx3, int Nx4, int Nx5){

        int i_grid = (((i_x1*Nx2
                        + i_x2)*Nx3
                        + i_x3)*Nx4
                        + i_x4)*Nx5
                        + i_x5;
        return i_grid;
    }


}