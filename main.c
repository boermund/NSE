//Loesung der Navier Stokes Gleichung 
// A. Rockstroh, T. Jungnickel 22.04.2020
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define RE      5
#define A       1.0
#define B       1.0
#define IMAX    300
#define JMAX    300
#define UMAX    1
#define VMAX    1
#define TAU     0.8 //Factor for adaptive step control
#define OMEGA   1.7 //Relaxation Factor
#define EPSILON 0.001
#define STARTT  0  
#define STOPT   10
#define PI      3.14
#define GY      1
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
    rhs_struct *RHS;
    RHS = calloc((IMAX+2)*(JMAX+2),sizeof(rhs_struct)); 
    old = fieldalloc(IMAX+2,JMAX+2); //Size of the field plus the edges
    passby = calloc((IMAX+2)*(JMAX+2),sizeof(f_and_g));
    
    double t = 0;
    //int i = 0;

    while(t < STOPT){
        
        old         = cavity(old,IMAX+2,JMAX+2);
        timestep    = timecontrol(old,TAU,IMAX+2,JMAX+2,dx,dy,RE);
        t           = t + timestep;
        //printf("Zeit:%f\n",timestep);
        gamma       = findgamma(old, IMAX+2, JMAX+2, timestep, dx, dy);
        
        passby      = new_f_and_g(old,passby,IMAX+2,JMAX+2,dy,dy,timestep,gamma);
        //RHS         = rhs_func(RHS, passby, dx, dy, timestep, IMAX+2, JMAX+2);
        RHS         = rhs_func(RHS, passby, dx ,dy ,timestep ,IMAX+2, JMAX+2); 
        old         = new_p(old, RHS, dx, dy, OMEGA, EPSILON, IMAX+2, JMAX+2);
        //printf("\nhello\n");
        old         = newspeed(old, passby,IMAX+2,JMAX+2,dx,dy,timestep,gamma);
        printf("Durchlauf: \t Zeit %f \n",t);
        //i++;
                
    }
    //main loop
    old = cavity(old,IMAX+2,JMAX+2);
    output(old,IMAX+2,JMAX+2);

    // FG Randwerte

    
    


    // Druck in den Randzellen anpassen
    //printf("%.2f", old->v);
    //free(newfield);
    //free(old);
    //free(passby);
    
}


