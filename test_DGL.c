// test the SOR with the elliptical PDG laplace(p(x,y)) = -2p(x,y)
// the solution is p(x,y) = sin(x+y)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//define the constants
#define IMAX    100
#define JMAX    100
#define XMAX    1.5
#define YMAX    1.5
#define OM      1.7
#define EPS     0.00001 

/* 
filling of the latice with IMAX = 2, JMAX = 3
0 1 2 
4 5 6
7 8 9
*/

// define structs
typedef struct 
{
    double r;  
} res;

typedef struct 
{
    double p;  
} presit;

typedef struct 
{
    double rhs;  
} rhs_struct;

typedef struct 
{
    double fvalue;
    double gvalue;  
} f_and_g;

typedef struct
{
    double p;
    double u;
    double v;
} cell;

typedef struct 
{
    double e;  
} ellip;

typedef struct 
{
    double x;
    double y;   
} xyel;

// include the functions that we need
#include "SOR_testDGL.h"
#include "test_DGL.h"

// begin mainfunction
void main(){

// define IMX, JMAx plus the Boundaries
int imax2, jmax2; 
imax2 = IMAX + 2;
jmax2 = JMAX + 2;

// calculate dx, dy
double dx, dy;
dx  = (double)(XMAX)/(double)IMAX;
dy = (double)(YMAX)/(double)JMAX; 

// define the struct for x,y values and calculate them
xyel *xy;
xy = calloc((IMAX+2)*(JMAX+2),sizeof(xyel));
xy = xyvalues(xy, dx, dy, imax2, jmax2);

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
testel = ellipt_struct(testel, xy, imax2, jmax2);

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

cell * h; 
h = calloc((IMAX+2)*(JMAX+2),sizeof(cell));

// put on the values for boundaries and p^(it=0)
// boundaries
for(int j =0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            h[j*imax2 + i].p = testel[j*imax2 + i].e;
        }
}

// fill the inner cells
for(int j =1; j < jmax2-1; j++){
        for(int i = 1; i < imax2-1; i++){
            h[j*imax2 + i].p = 0;
            //h[j*imax2 + i].p = 1;
            //h[j*imax2 + i].p = 2;
            //h[j*imax2 + i].p = 2;
            //h[j*imax2 + i].p = testel[j*imax2 + i].e + 0.1;
        }
}  

//define the struct for the RHS
rhs_struct * RHS; 
RHS = calloc((IMAX+2)*(JMAX+2),sizeof(rhs_struct));

// fill RHS with the first values of pressure (same one like the first one of the cell)
for(int j =0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            RHS[j*imax2 + i].rhs = -2*h[j*imax2 + i].p;
        }
    }

// second struct for a constant rhs to calculate the residuum
rhs_struct * RHS2; 
RHS2 = calloc((IMAX+2)*(JMAX+2),sizeof(rhs_struct));

for(int j =0; j < jmax2; j++){
    for(int i = 0; i < imax2; i++){
        RHS2[j*imax2 + i].rhs = -2*testel[j*imax2 + i].e;
    }
}

// SOR: calculate the new pressure and put it in the cell
h = new_p(h,RHS, dx, dy, OM, EPS, imax2, jmax2, RHS2);

//print the new_p an put them in to a txt file
FILE * newp;
    newp = fopen("new_p.txt", "w+");
//printf("\nNew pressure/ solve of the PDG\n");
for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            fprintf(newp, " %.6f\t", h[imax2*j+i].p);
        }
        fprintf(newp, "\n");
        }
fclose(newp);

}