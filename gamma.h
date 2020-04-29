#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
search for the biggest value of the testfunction of u
used to test the derivates
there ist an other function in timcontrol, using for the main program
returns gamma 
*/

float gamma_v(cell *field, float dt, float dx, int imax, int jmax){

    float umax = fabs(field[0].u), gamma;

//find the biggest value
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
 
  // calculate and return gamma
         return 1.3 * umax*dt/dx;   //gamma

    

}
