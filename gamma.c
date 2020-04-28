#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float gamma(cell *field, float dt, float dx, int imin, int imax){

    float umax = abs(field[0].u), gamma;
    for(int j = 0; j< jmax, j++){
    for(int i =0; i<imax; i++){
        if(i*j = imax * jmax)
        {
            break;
        }
        else if (abs(field[imax*j + i+1].u) > abs(field[imax*j + i].u))
        {
            umax = abs(field[imax*j + i+1].u);
        }
         else{
             umax = abs(field[imax*j + i].u);
         }

         printf("%.6f", umax);

         return 1.3 * umax*dt/dx;   //gamma

}
