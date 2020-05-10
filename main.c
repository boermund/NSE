//Loesung der Navier Stokes Gleichung 
// A. Rockstroh, T. Jungnickel 22.04.2020
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define RE      1000
#define A       10.0
#define B       10.0
#define IMAX    10
#define JMAX    10
#define UMAX    1
#define VMAX    1
#define TAU     0.8 //Factor for adaptive step control
#define OMEGA   1.7 //Relaxation Factor
#define EPSILON 0.1
#define STARTT  0  
#define STOPT   2
#define PI      3.14
#define GY      0
#define GX      0
//structure for filling the array
typedef struct
{
    float p;
    float u;
    float v;
} cell;

typedef struct
{
    float fvalue;
    float gvalue;
} f_and_g;

typedef struct
{
    f_and_g *fg;
    cell    *field;
} new_values;

typedef struct 
{
    float r;  
} res;

typedef struct 
{
    float p;  
} presit;

typedef struct 
{
    float rhs;  
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
    cell *old;
    f_and_g *passby;
    float gamma = 0;
    float dx,dy,timestep;
    dx = A/IMAX;
    dy= B/JMAX;
    rhs_struct *RHS;
    RHS = calloc((IMAX+2)*(JMAX+2),sizeof(rhs_struct)); 
    old = fieldalloc(IMAX+2,JMAX+2); //Size of the field plus the edges
    
    
    float t = 0;
    int i = 0;
    while(i<50){
        old         = cavity(old,IMAX+2,JMAX+2);
        timestep    = timecontrol(old,TAU,IMAX+2,JMAX+2,dx,dy,RE);
        t           = t + timestep;
        //printf("Zeit:%f\n",timestep);
        gamma       = findgamma(old, IMAX+2, JMAX+2, timestep, dx, dy);
        
        passby      = new_f_and_g(old,IMAX+2,JMAX+2,dy,dy,timestep,gamma);
        //RHS         = rhs_func(RHS, passby, dx, dy, timestep, IMAX+2, JMAX+2);
        RHS         = rhs_func(RHS, passby, dx ,dy ,timestep ,IMAX+2, JMAX+2); 
        old         = new_p(old, RHS, dx, dy, OMEGA, EPSILON, IMAX+2, JMAX+2);
        //printf("\nhello\n");
        old         = newspeed(old, passby,IMAX+2,JMAX+2,dx,dy,timestep,gamma);
        printf("Durchlauf:%d \t Zeit %f \n",i,t);
        i++;
        
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


