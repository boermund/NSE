#include <stdio.h>
#include <math.h>
#include <stdlib.h>


///////// AUFPASSEN WEGEN IMAX UND IMIN IN VORSCHLEIFEN

#define IMAX    2
#define JMAX    3

typedef struct 
{
    float r;  
} cell;

typedef struct 
{
    float p;  
} presit;

typedef struct 
{
    float rhs;  
} rhs_struct;

typedef struct 
{
    float f;
    float g;  
} cell_fg;


#include "allok.h"
#include "SOR.h"

void main(){
int imax2, jmax2; 
imax2 = IMAX + 2;
jmax2 = JMAX + 2;

// test the abs_residuum_function

//fill a field with numbers
cell *a;
a = fieldalloc(IMAX,JMAX); 


for(int j = 0; j < JMAX; j++){
    for(int i = 0; i < IMAX; i++){
        a[IMAX*j + i].r = pow(i,2);
        //printf("%.6f\t",a[i].r);
    }
}

free(a);

//test the function
float residuum;
residuum = abs_res(a, IMAX, JMAX);

//printf("\n %.6f \n", residuum);





// test the RHS function

// fill two fields
cell_fg * fg;
fg = calloc((IMAX+2)*(JMAX+ 2),sizeof(cell_fg));

for(int j = 0; j < JMAX + 2; j++){
    for(int i = 0; i < IMAX + 2; i++){
        fg[(IMAX+2)*j + i].f = 2*j - i*j;
        fg[(IMAX+2)*j + i].g = 2*i + i*j;
        //printf(" f: %.6f\t",fg[(IMAX+2)*j +i].f);
        //printf(" g: %.6f\t \n",fg[(IMAX+2)*j +i].g);
    }
}

// test function

// create a field and inialisize dx, dy, dz
float dx = 1, dy = 1, dt =  1; 

rhs_struct *RHS;
RHS = calloc((IMAX+2)*(JMAX+2),sizeof(rhs_struct)); 

rhs_func(RHS, fg ,dx, dy, dt, IMAX + 2, JMAX + 2);


printf("\nRHS\n");
for(int j = 0; j < JMAX + 2; j++){
    for(int i = 0; i < IMAX + 2; i++){
        
        printf(" %.6f\t",RHS[(IMAX+2)*j +i].rhs);
    }
    printf("\n");
}

printf("\n\n");







///// Pressure

// test boundary cells 

presit * pres;
pres = calloc((IMAX+2)*(JMAX+2),sizeof(presit));

printf("\nDruckwerte0:\n");
for(int j = 0; j < JMAX+2; j++){
    for(int i = 0; i < IMAX+2; i++){
        pres[(IMAX+2)*j + i].p = i*j;
        printf("%.6f\t",pres[(IMAX+2)*j + i].p);
    }
    printf("\n");
}

 printf("\n");
/*
// new i boundaries
for(int i = 0; i < imax2; i++){
        pres[i].p = pres[imax2 + i].p;
        pres[(jmax2-1)*imax2 + i].p = pres[(jmax2-2)*imax2 + i].p;
    }

  // printf("\n") ;

// new j boundaries
    for(int j = 0; j < jmax2; j++ ){
        pres[imax2*j].p = pres[j*imax2 + 1].p;
        pres[imax2 * j + (imax2-1)].p = pres[imax2 * j + (imax2-2)].p;
    }

   // printf("\n");

    for(int j = 0; j < JMAX+2; j++){
    for(int i = 0; i < IMAX+2; i++){
       // printf("%.6f\t",pres[(IMAX+2)*j + i].p);
    }
    printf("\n");
}
*/

// test the pres_it function

float omega = 0.8;

pres = pres_it(pres,  RHS, dx,  dy,  omega, p_it, IMAX +2, JMAX + 2);

printf("\n\n");
printf("Druckwerte1:\n");

for(int j = 0; j < JMAX+2; j++){
    for(int i = 0; i < IMAX+2; i++){
       printf("%.6f\t",pres[(IMAX+2)*j + i].p);
    }
    printf("\n");
}

printf("\n");

pres = pres_it(pres,  RHS, dx,  dy,  omega, p_it, IMAX +2, JMAX + 2);

printf("Druckwerte2:\n");
for(int j = 0; j < JMAX+2; j++){
    for(int i = 0; i < IMAX+2; i++){
       printf("%.6f\t",pres[(IMAX+2)*j + i].p);
    }
    printf("\n");
}

printf("\n");


}