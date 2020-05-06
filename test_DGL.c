// test the SOR with the elliptical PDG laplace(p(x,y)) = -2p(x,y)
// the solution is p(x,y) = -exp(x+y)
// Idea: put righthandside RHS as -2*exp(x+y) [is 1/dt*(diff(F)/dx + diff(G)/dy) in equation (41)) and solve the equation with a startvector p_(it=0)
//c 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//define the constants
#define IMAX    300
#define JMAX    300 //length of the lattice(begins at zero)
#define XMAX    6//length of the lattice(begins at zero)
#define YMAX    6
#define OM      0.3
#define EPS     0.2

/* 
filling of the latice with IMAX = 2, JMAX = 3
0 1 2 
4 5 6
7 8 9
*/


// define structs
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

typedef struct 
{
    float fvalue;
    float gvalue;  
} f_and_g;

typedef struct
{
    float p;
    float u;
    float v;
} cell;

typedef struct 
{
    float e;  
} ellip;

typedef struct 
{
    double x;
    double y;   
} xyel;

// include the functions that we need
#include "SOR.h"
#include "test_DGL.h"



//begin mainfunction
void main(){

//define IMX, JMAx plus the Boundaries
int imax2, jmax2; 
imax2 = IMAX + 2;
jmax2 = JMAX + 2;

//calculate dx, dy
float dx, dy;
dx  = (float)(XMAX)/(float)IMAX;
dy = (float)(YMAX)/(float)JMAX; 

// define the struct for x,y values and calculate them
xyel *xy;
xy = calloc((IMAX+2)*(JMAX+2),sizeof(xyel));
xy = xyvalues(xy, dx, dy, imax2, jmax2);

/* 
//print them
printf("\nxyvalues\n");
for(int j =0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            printf("x: %.6f\t y: %.6f\t", xy[j*imax2 + i].x, xy[j*imax2 + i].y);
        }
        printf("\n");
    }
*/

// put x and y values into a file
FILE * xval;
    xval = fopen("xval.txt", "w+");
FILE * yval;
    yval = fopen("yval.txt", "w+");


    for(int i = 0; i < imax2; i++){
        fprintf(xval, " %.6f\t", xy[i].x);
        }
    for(int j = 0; j < jmax2; j++){
        fprintf(yval, " %.6f\t", xy[j].y);
    }

fclose(xval);
fclose(yval);

//define a struct for the values of testfunction/ solve of the PDF (-exp(x+y))
ellip * testel;
testel = calloc((IMAX+2)*(JMAX+2),sizeof(ellip));
testel = ellipt_struct(testel, xy, ellipt, imax2, jmax2);

/*
//print them
printf("values -exp(x+y)\n");
for(int j =0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            printf("%.6f\t", testel[j*imax2 + i].e);
        }
        printf("\n");
    }
*/

// put the analytical values into a file
FILE * p_ana;
    p_ana = fopen("p_ana.txt", "w+");

    for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            fprintf(p_ana, " %.6f\t", testel[j*imax2 + i].e);
        }
        fprintf(p_ana, "\n");
        }

fclose(p_ana);

//define the struct for the RHS
rhs_struct * RHS; 
RHS = calloc((IMAX+2)*(JMAX+2),sizeof(rhs_struct));

//define cell (it has 3 values (u,v,p) and we need it for in the right algrorithm. the aim of the SOR is to give the p value of the cell back)
// What would be the first pressure I have to put in (p_(it=0))
    // Options: calculatet of the testfunction; everithing is zero, everything  except the boundaries are zero, everything has a value except the boundaries (they are zero) 
    // here I choose the third option


cell * h; 
h = calloc((IMAX+2)*(JMAX+2),sizeof(cell));

for(int j =0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            h[j*imax2 + i].p = testel[j*imax2 + i].e +1;
        }
}


// fill the start pressure with zeros
/*for(int j =0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            h[j*imax2 + i].p = 0.1;
        }
    }*/


// fill RHS with the first values of pressure (same one like the first one of the cell)
for(int j =0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            RHS[j*imax2 + i].rhs = -2* h[j*imax2 + i].p;
        }
    }

/*
for(int j =0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            RHS[j*imax2 + i].rhs =-2* 0.1;
        }
    }
*/

// print pressure
/*
printf("\npressure 0\n");
for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
           
            printf(" %.6f\t", h[imax2*j+i].p);
        }
        printf("\n");
        }
*/

// print RHS
/*
printf("\nRHS\n");
for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            printf(" %.6f\t", RHS[imax2*j+i].rhs);
        }
        printf("\n");
        }*/


//define a resstruct that we need to caluculate the residuum
res * res_st;
res_st = calloc((IMAX)*(JMAX),sizeof(res));

// SOR: calculate the new pressure and put it in the cell
h = new_p(h,RHS,res_st, abs_pres, p_it, pres_it, res_func, res_struct, abs_res, dx, dy, OM, EPS, imax2, jmax2);

//print the new_p an put them in to a txt file
FILE * newp;
    newp = fopen("new_p.txt", "w+");
//as I understand, it has to be -exp(x+y) with the values we already calculated

printf("\nNew pressure/ solve of the PDG\n");
for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
          //  printf(" %.6f\t", h[imax2*j+i].p);
            fprintf(newp, " %.6f\t", h[imax2*j+i].p);
        }
        //printf("\n");
        fprintf(newp, "\n");
        }

fclose(newp);

// problem if we observe the SOR: 
    // error of the residuum ist constant, pressure rises very fast and becomes to big
    // problem if we choose the first option of the pressure p_it=0: abs(p_it =0) = 0 and t the alorithm doesnt't end
    // try it with different values for epsilon and omega and different values for IMAX, JMax to get smaller dx, dy

}