#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define IMAX    2
#define JMAX    3

typedef struct 
{
    float r;  
} cell;

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
fg = calloc(IMAX*JMAX,sizeof(cell_fg));

for(int j = 0; j < JMAX; j++){
    for(int i = 0; i < IMAX; i++){
        fg[IMAX*j + i].f = 1;
        fg[IMAX*j + i].g = 1;
        printf(" f: %.6f\t",fg[i].f);
        printf(" g: %.6f\t \n",fg[i].g);
    }
}



// test function

// create a field and inialisize dx, dy, dz

float dx = 1, dy = 1, dt =  1; 

rhs_struct *RHS;
RHS = calloc(IMAX*JMAX,sizeof(rhs_struct)); 

rhs_func(RHS, fg ,dx, dy, dt, IMAX, JMAX);

free(fg); // frei setzt mir bestimmer werte auf null

}