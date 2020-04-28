//Loesung der Navier Stokes Gleichung 
// A. Rockstroh, T. Jungnickel 22.04.2020
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define RE      100
#define A       5.0
#define B       5.0
#define IMAX    33
#define JMAX    33 
#define UMAX    100
#define VMAX    100
#define TAU     0.5 //Factor for adaptive step control
#define OMEGA   0.5 //Relaxation Factor
#define STARTT  0  
#define STOPT   10
#define PI      3.14

//structure for filling the array
typedef struct
{
    float p;
    float u;
    float v;
} cell;


#include "allok.h"
#include "output.h"
#include "timecontrol.h"
#include "ghostcell.h"
#include "outputtest.h"

//main
void main(){
    cell *old;

    old = fieldalloc(IMAX+2,JMAX+2); //Size of the field plus the edges

    float dx,dy,timestep;
    dx = A/IMAX;
    dy= B/JMAX;
    old=fieldalloc(IMAX+2,JMAX+2); //Size of the field plus the edges
    timestep=timecontrol(old,TAU,IMAX+2,JMAX+2,dx,dy,RE);
    /*printf("%f",timestep);*/
    old=outputtest(old,IMAX+2,JMAX+2);
    old=cavity(old,IMAX+2,JMAX+2);
    output(old,IMAX+2,JMAX+2);
    printf("%.2f", old->v);
}


