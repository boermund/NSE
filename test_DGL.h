// test elliptical PDG laplace(p(x,y)) = -2p(x,y) - functions

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// function wich solve the DGL
float ellipt(float x, float y){
    return sin(x+y);

}

// returns a struct with the xy values to calculate the analytical pressure
xyel * xyvalues(xyel* xy, float dx, float dy, int imax2, int jmax2){

    float xval, yval;
    xval = -0.5 * dx;
    yval = -0.5 * dy;

    for(int i = 0; i < imax2; i++){
       xy[i].x = xval;
       xval += dx;
    }
    for(int j = 0; j < jmax2; j++){ 
       xy[j].y = yval;
       yval += dy;
    }
    
    return xy;
}

// function wich gives a struct back with boundary values and inner values
ellip *ellipt_struct(ellip* el, xyel* xy, int imax2, int jmax2){
    for(int j =0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            el[j*imax2 + i].e = ellipt(xy[i].x, xy[j].y);
        }
    }
    return el;
}

