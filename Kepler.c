// Tom Jungnickel 2.5.19 Semniar 3
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define AU      1
#define STARTX  1 
#define STARTY  0
#define STARTT  0
#define ENDT    10000
#define STARTVX 0
#define STARTVY 2*3.141592
#define TUMLAUF 1
#define dt      0.01
#define AU      1
#define GM      M_PI*M_PI*4*AU/TUMLAUF

#define X_OLD 0
#define Y_OLD 1
#define VX_OLD 2
#define VY_OLD 3
#define X_NEW 4
#define Y_NEW 5
#define VX_NEW 6
#define VY_NEW 7

int main()
{   
    FILE * fp;
    fp = fopen ("Euler.txt","w+");
    int timesteps = (STARTT-ENDT)/dt;
    double t=STARTT,Ekin,Epot,Eges;
    double *p;
    p = calloc(8,sizeof(double));
    p[X_OLD]= STARTX;
    p[Y_OLD]= STARTY;
    p[VX_OLD]= STARTVX;
    p[VY_OLD]= STARTVY;
    //fprintf(fp,"t \t\t\t x \t\t\t y \t\t\t vx \t\t\t vy \t\t\t Ekin \t\t\t Epot \t\t\t Ekges \n");
    while(t<=ENDT)
    {
        p[VX_NEW]=p[VX_OLD] - dt * GM* (p[X_OLD] / pow( sqrt( pow(p[X_OLD],2) + pow(p[Y_OLD],2)) ,3));
        p[VY_NEW]=p[VY_OLD] - dt * GM* (p[Y_OLD] / pow( sqrt( pow(p[X_OLD],2) + pow(p[Y_OLD],2)) ,3));
        p[X_NEW]=p[X_OLD]+p[VX_OLD]*dt;
        p[Y_NEW]=p[Y_OLD]+p[VY_OLD]*dt;
        Ekin = +(pow(p[VX_NEW],2) + pow(p[VY_NEW],2));
        Epot = -GM/sqrt( pow(p[X_OLD],2) + pow(p[Y_OLD],2));
        Eges = Epot+Ekin;
        fprintf(fp,"%.9lf \t%.9lf \t%.9lf \t%.9lf \t%.9lf \t%.9lf \t%.9lf \t%.9lf  \n", t, p[0], p[1], p[2], p[3], Ekin ,Epot, Eges);
        p[X_OLD]=p[X_NEW];
        p[Y_OLD]=p[Y_NEW];
        p[VX_OLD]=p[VX_NEW];
        p[VY_OLD]=p[VY_NEW];
        t=t+dt;
    }
    free(p);
}
