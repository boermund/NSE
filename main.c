//Loesung der Navier Stokes Gleichung 
// A. Rockstroh, T. Jungnickel 22.04.2020
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define RE      100
#define A       5.0
#define B       5.0
#define IMAX    10
#define JMAX    10 
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

#include "derivates.h"
#include "allok.h"
#include "output.h"
#include "timecontrol.h"
#include "ghostcell.h"
#include "outputtest.h"
#include "newspeed.h"

//main
void main(){
    cell *old;
    cell *newfield;
    new_values temp;
    f_and_g *passby;
    float gamma = 0;
    // Tom schreibt noch Gamma Funktion
    float dx,dy,timestep;
    dx = A/IMAX;
    dy= B/JMAX;
    old=fieldalloc(IMAX+2,JMAX+2); //Size of the field plus the edges
    timestep=timecontrol(old,TAU,IMAX+2,JMAX+2,dx,dy,RE);
    /*printf("%f",timestep);*/
    //old=outputtest(old,IMAX+2,JMAX+2);

    //old=cavity(old,IMAX+2,JMAX+2);
    
    temp = newspeed(old, IMAX+2, JMAX+2, dx ,dy, timestep, gamma);
    passby  = temp.fg;
    newfield     = temp.field;

    // Druck in den Randzellen anpassen
    //output(newfield,IMAX+2,JMAX+2);
    //printf("%.2f", old->v);
    //free(newfield);
    //free(old);
    //free(passby);
    printf("print1\n\n\n");
    for(int z = 0; z < (IMAX+2)*(JMAX+2);z++)
        printf("%d:\t%.2f\t%.2f\t%.2f\n",z,newfield[z].u,newfield[z].u,newfield[z].p);
    /*
    int imax = IMAX+2;
    int jmax = JMAX+2;
    FILE * vspeed;
    vspeed = fopen ("vspeed.csv","w");
    FILE * uspeed;
    uspeed = fopen ("uspeed.csv","w");
    FILE * pressure;
    pressure = fopen ("pressure.csv","w");
    */
    printf("print2\n\n\n");
    for(int z = 0; z < (IMAX+2)*(JMAX+2);z++)
        printf("%d:\t%.2f\t%.2f\t%.2f\n",z,newfield[z].u,newfield[z].u,newfield[z].p);
    /*
    for(int j=0;j<jmax;j++){
        for(int i=0;i<imax;i++){
            fprintf(vspeed,"%f,",newfield[i+imax*j].v);
            fprintf(uspeed,"%f,",newfield[i+imax*j].u);
            fprintf(pressure,"%f,",newfield[i+imax*j].p);
        
        }
        fprintf(vspeed,"\n");
        fprintf(uspeed,"\n");
        fprintf(pressure,"\n");
    }
    fclose(vspeed);
    fclose(uspeed);
    fclose(pressure);
    */
}


