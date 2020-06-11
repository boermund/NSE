//Loesung der Navier Stokes Gleichung 
// A. Rockstroh, T. Jungnickel 22.04.2020
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define RE      10
#define A       1.0
#define B       1.0
#define IMAX    150
#define JMAX    150
#define UMAX    10.0
#define VMAX    10.0
#define TAU     0.8 //Factor for adaptive step control
#define OMEGA   1.7 //Relaxation Factor
#define EPSILON 0.0001
#define STARTT  0  
#define STOPT   1
#define PI      3.14
#define GY      0
#define GX      0
//structure for filling the array
typedef struct
{
    double p;
    double u;
    double v;
} cell;

typedef struct
{
    double fvalue;
    double gvalue;
} f_and_g;

typedef struct
{
    f_and_g *fg;
    cell    *field;
} new_values;

typedef struct 
{
    double r;  
} res;

typedef struct 
{
    double p;  
} presit;

typedef struct 
{
    double rhs;  
} rhs_struct;



#include "derivates.h"
#include "allok.h"
#include "output.h"
#include "timecontrol.h"
#include "ghostcell.h"
#include "outputtest.h"
#include "newspeed.h"
#include "findgamma.h"
#include "SOR.h"

//main
void main(){

    //printf("\nhello\n");
    cell *old;
    f_and_g *passby;
    double gamma = 0;
    double dx,dy,timestep;
    dx = A/IMAX;
    dy= B/JMAX;
    printf("%f\t%f\n",dx,dy);
    rhs_struct *RHS;
    RHS = calloc((IMAX+2)*(JMAX+2),sizeof(rhs_struct)); //Array with data of the RHS
    old = fieldalloc(IMAX+2,JMAX+2); //Size of the field plus the edges
    passby = calloc((IMAX+2)*(JMAX+2),sizeof(f_and_g)); //f and g values
    double t = 0; //time
    int i = 0;  //Number of iteration


    while(t<STOPT){
        
        old         = cavity(old,IMAX+2,JMAX+2, i); //Boundary conditions
        timestep    = timecontrol(old,TAU,IMAX+2,JMAX+2,dx,dy,RE); // Calculating the new timestep
        t           = t + timestep; //Adding the timestep

        //printf("Zeit:%f\n",timestep);
        gamma       = findgamma(old, IMAX+2, JMAX+2, timestep, dx, dy); //Calculate the gamma balue for the nonlinear derivations

        passby      = new_f_and_g(old,passby,IMAX+2,JMAX+2,dy,dy,timestep,gamma); //Calculate F and G
        //RHS         = rhs_func(RHS, passby, dx, dy, timestep, IMAX+2, JMAX+2);
        //printf("\nhere\n");
        
        RHS         = rhs_func(RHS, passby, dx ,dy ,timestep ,IMAX+2, JMAX+2); //Calculate the Right Hand site
        old         = new_p(old, RHS, dx, dy, OMEGA, EPSILON, IMAX+2, JMAX+2); //Calculating the new pressure
        //printf("\nhello\n");
        old         = newspeed(old, passby,IMAX+2,JMAX+2,dx,dy,timestep,gamma); //Callculate the new Speed
        printf("Durchlauf: %d\t Zeit %f \n",i,t);
        i++;

        if((i%50==0) && (i<1000)){ //Print the current solution to check 
            old         = cavity(old,IMAX+2,JMAX+2,i);
            output(old,IMAX+2,JMAX+2);
            printf("output done");
        }
        
        if((i%1000==0) && (i>1000)){
            old         = cavity(old,IMAX+2,JMAX+2,i);
            output(old,IMAX+2,JMAX+2);
            printf("output done");
        }
    }

    old = cavity(old,IMAX+2,JMAX+2,i);
    output(old,IMAX+2,JMAX+2); //Print the final Solution

    

}


