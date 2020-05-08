//Loesung der Navier Stokes Gleichung 
// A. Rockstroh, T. Jungnickel 22.04.2020
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define RE      100
#define A       5.0
#define B       5.0
#define IMAX    10
#define JMAX    100 
#define UMAX    10
#define VMAX    10
#define TAU     0.5 //Factor for adaptive step control
#define OMEGA   0.5 //Relaxation Factor
#define STARTT  0  
#define STOPT   10
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
    cell *newfield;
    new_values temp;
    f_and_g *passby;
    float gamma = 0;
    float dx,dy,timestep;
    dx = A/IMAX;
    dy= B/JMAX;
    
    old=fieldalloc(IMAX+2,JMAX+2); //Size of the field plus the edges
    
    gamma = findgamma(old, IMAX+2, JMAX+2, timestep, dx, dy);
    old=vandp_linear(old,IMAX+2,JMAX+2);

    /*printf("%f",timestep);*/
    //old=outputtest(old,IMAX+2,JMAX+2);
    float t = 0;
    while(t<STOPT){
        timestep    = timecontrol(old,TAU,IMAX+2,JMAX+2,dx,dy,RE);
        t           = t + timestep;
        old         = cavity(old,IMAX+2,JMAX+2);
        gamma       = findgamma(old, IMAX+2, JMAX+2, timestep, dx, dy);
        passby      = new_f_and_g(old,IMAX+2,JMAX+2,dy,dy,timestep,gamma);


        
    }
    //main loop

    temp = newspeed(old, IMAX+2, JMAX+2, dx ,dy, timestep, gamma);
    
    passby  = temp.fg;
    newfield     = temp.field;
    // FG Randwerte

    
    


    // Druck in den Randzellen anpassen
    output(newfield,IMAX+2,JMAX+2);
    //printf("%.2f", old->v);
    //free(newfield);
    //free(old);
    //free(passby);
    
}


