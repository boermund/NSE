//Loesung der Navier Stokes Gleichung 
// A. Rockstroh, T. Jungnickel 22.04.2020
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define RE      0.0001
#define A       100.0
#define B       100.0
#define IMAX    150.0
#define JMAX    150.0
#define UMAX    1.0
#define VMAX    1.0
#define TAU     0.8 //Factor for adaptive step control
#define OMEGA   1.7 //Relaxation Factor
#define EPSILON 0.00001
#define STARTT  0  
#define STOPT   0.1
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
    RHS = calloc((IMAX+2)*(JMAX+2),sizeof(rhs_struct)); 
    old = fieldalloc(IMAX+2,JMAX+2); //Size of the field plus the edges
    passby = calloc((IMAX+2)*(JMAX+2),sizeof(f_and_g));
    double t = 0;
    int i = 0;

    while(t<STOPT){
        
        old         = cavity(old,IMAX+2,JMAX+2, i);
        timestep    = timecontrol(old,TAU,IMAX+2,JMAX+2,dx,dy,RE);
        t           = t + timestep;

        //printf("Zeit:%f\n",timestep);
        gamma       = findgamma(old, IMAX+2, JMAX+2, timestep, dx, dy);

        passby      = new_f_and_g(old,passby,IMAX+2,JMAX+2,dy,dy,timestep,gamma);
        //RHS         = rhs_func(RHS, passby, dx, dy, timestep, IMAX+2, JMAX+2);
        //printf("\nhere\n");
        
        RHS         = rhs_func(RHS, passby, dx ,dy ,timestep ,IMAX+2, JMAX+2); 
        old         = new_p(old, RHS, dx, dy, OMEGA, EPSILON, IMAX+2, JMAX+2);
        //printf("\nhello\n");
        old         = newspeed(old, passby,IMAX+2,JMAX+2,dx,dy,timestep,gamma);
        printf("Durchlauf: %d\t Zeit %f \n",i,t);
        i++;
        if((i%10==0) && (i<1000)){
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
    //main loop
    old = cavity(old,IMAX+2,JMAX+2,i);
    output(old,IMAX+2,JMAX+2);

    // FG Randwerte

    
    


    // Druck in den Randzellen anpassen
    //printf("%.2f", old->v);
    //free(newfield);
    //free(old);
    //free(passby);
    
}


