#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float gamma_v(cell *field, float dt, float dx, int imax, int jmax){

    float umax = fabs(field[0].u), gamma;

    for(int j = 0; j< jmax; j++){
    for(int i =0; i<imax; i++){
        if(i*j == imax * jmax)
        {
            break;
        }
        else if (fabs(field[imax*j + i].u) >= umax)
        {
            umax = fabs(field[imax*j + i].u);
            //printf("%.6f ja\n", umax);
        }
         else{
             //printf("%.6f nein\n", umax);
         }

         
        }
    }   
    
    printf("%.6f\n", umax);
         return 1.3 * umax*dt/dx;   //gamma

    

}
