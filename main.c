//Loesung der Navier Stokes Gleichung 
// A. Rockstroh, T. Jungnickel 22.04.2020
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define RE      100
#define A       5.0
#define B       5.0
#define IMAX    100
#define JMAX    100 
#define UMAX    100
#define VMAX    100
#define TAU     0.5 //Factor for adaptive step control
#define OMEGA   0.5 //Relaxation Factor
#define STARTT  0  
#define STOPT   10

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

//main
void main(){
    cell *a;
    float dx,dy,timestep;
    dx = A/IMAX;
    dy= B/JMAX;
    a=fieldalloc(IMAX+2,JMAX+2); //Size of the field plus the edges
    timestep=timecontrol(a,TAU,IMAX,JMAX,dx,dy,RE);
    printf("%f",timestep);
    output(a,IMAX,JMAX);
}