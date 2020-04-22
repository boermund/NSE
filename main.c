//Loesung der Navier Stokes Gleichung 
// A. Rockstroh, T. Jungnickel 22.04.2020
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define RE      100
#define IMAX    100
#define JAMX    100 
#define UMAX    100
#define VMAX    100
#define TAU     0.5 //Factor for adaptive step control


//structure for filling the array
typedef struct
{
    long float P;
    long float u;
    long float v;
} cell;

