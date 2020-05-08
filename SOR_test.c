// program to test the SOR stepwise, first the functions at the end the ful algorithm
// include the program SOR.h for the functions and the test

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define IMAX    2
#define JMAX    3
#define OM      1.3
#define EPS     0.001
// in this cas it is important for me to define dx, dy by my self
// normaly I would calculate them with the given size of the problem
#define DX      1
#define DY      1
// normaly DT is calculated automatically
#define DT      1

/* 
filling of the latice with IMAX = 2, JMAX = 3
0 1 2 
4 5 6
7 8 9
*/

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


#include "SOR.h"

void main(){

//define the numer of values with boundaries   
int imax2, jmax2; 
imax2 = IMAX + 2;
jmax2 = JMAX + 2;

/////////////////////////////////////////////////////////////////////

// test the abs_residuum_function
//fill a field with numbers
res *a;
a = calloc((IMAX)*(JMAX),sizeof(res));


for(int j = 0; j < JMAX; j++){
    for(int i = 0; i < IMAX; i++){
        a[IMAX*j + i].r = pow(i,2);
    }
}

/*
printf("\nresiduum struct\n");
for(int j = 0; j < JMAX; j++){
    for(int i = 0; i < IMAX; i++){
        printf("%.6f\t",a[(imax2-2)*j+i].r);
    }
    printf("\n");
}
*/

//calculate the abs(res)
float residuum;
residuum = abs_res(a, IMAX+2, JMAX+2);
printf("\nabs(res): %.6f \n", residuum);


/////////////////////////////////////////////////////////////////////

// test the RHS function

// define a struct with f and g values by my self
f_and_g * fg;
fg = calloc((IMAX+2)*(JMAX+ 2),sizeof(f_and_g));

for(int j = 0; j < JMAX + 2; j++){
    for(int i = 0; i < IMAX + 2; i++){
        fg[(IMAX+2)*j + i].fvalue = 2*j - i*j;
        fg[(IMAX+2)*j + i].gvalue = 2*i + i*j;
        //printf(" f: %.6f\t",fg[(IMAX+2)*j +i].fvalue);
        //printf(" g: %.6f\t \n",fg[(IMAX+2)*j +i].gvalue);
    }
}

// print the struct
/*
printf("\nf and g values\n");
for(int j = 0; j < JMAX + 2; j++){
    for(int i = 0; i < IMAX + 2; i++){
        printf(" f: %.6f\t",fg[(IMAX+2)*j +i].fvalue);
        printf(" g: %.6f\t \n",fg[(IMAX+2)*j +i].gvalue);
    }
}
*/

// test function
rhs_struct *RHS;
RHS = calloc((IMAX+2)*(JMAX+2),sizeof(rhs_struct)); 

rhs_func(RHS, fg ,DX, DY, DT, imax2, jmax2);

// print the new struct
/*
printf("\nRHS\n");
for(int j = 0; j < JMAX + 2; j++){
    for(int i = 0; i < IMAX + 2; i++){
        printf(" %.6f\t",RHS[(IMAX+2)*j +i].rhs);
    }
    printf("\n");
}
*/

/////////////////////////////////////////////////////////////// 

//pressure

// define a pressure by my self
presit * pres;
pres = calloc((IMAX+2)*(JMAX+2),sizeof(presit));

for(int j = 0; j < JMAX+2; j++){
    for(int i = 0; i < IMAX+2; i++){
        pres[(IMAX+2)*j + i].p = i*j;
    }
}
 printf("\n");


// print them
printf("\nDruckwerte0:\n");
for(int j = 0; j < JMAX+2; j++){
    for(int i = 0; i < IMAX+2; i++){
        printf("%.6f\t",pres[(IMAX+2)*j + i].p);
    }
    printf("\n");
}


// abs pressure
float abspres;
abspres = abs_pres(pres, imax2, jmax2);
//printf("\nabs pres: %.6f\n", abspres);

// test the pres_it function
//if you want to test the SOR below and compare it with the results here you
// have to comment the pres functions out and calculate the pressure with the SOR again

// calculate pres twice

//pres = pres_it(pres,  RHS, DX,  DY,  OM,  imax2, jmax2);


// print the new values
/*
printf("\nDruckwerte1:\n");
for(int j = 0; j < JMAX+2; j++){
    for(int i = 0; i < IMAX+2; i++){
       printf("%.6f\t",pres[(IMAX+2)*j + i].p);
    }
    printf("\n");
}*/



//pres = pres_it(pres,  RHS, DX,  DY,  OM, imax2, jmax2);

/*
printf("\nDruckwerte2:\n");
for(int j = 0; j < JMAX+2; j++){
    for(int i = 0; i < IMAX+2; i++){
       printf("%.6f\t",pres[(IMAX+2)*j + i].p);
    }
    printf("\n");
}
*/


// to test the boundary conditions there are print functions in the pres_it+1 in the SOR.h 


//////////////////////////////////////////////////////////

//residuum

// test function for struct residuum

res * res_str;
res_str = calloc((IMAX)*(JMAX),sizeof(res));

res_str = res_struct(res_str, RHS, pres,  DY,DX,imax2, jmax2); 

/*
// print it
printf("\nRes_struct:\n");
for(int j = 0; j < JMAX; j++){
    for(int i = 0; i < IMAX; i++){
       printf("%.6f\t", res_str[IMAX*j + i].r);
    }
    printf("\n");
}
*/

// abs res
float absres;
absres = abs_res(res_str, IMAX+2, JMAX+2);
//printf("abs res: %.6f\n", absres);


///////////////////////////////////////////////////////////////////////

// test SOR

// test function new_p, giving a new p field afther the SOR step
cell * h; 

h = calloc((imax2)*(jmax2),sizeof(cell));

// put in the cell struct the pressure values from above to look wether there are the same results
for(int j = 0; j < jmax2; j++){
    for(int i = 0; i < imax2; i++){
      h[(IMAX+2)*j + i].p  = pres[(imax2)*j + i].p;
    }
}

// print pressure
/*
printf("\nDruckwerte0- before SOR:\n");
    for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){ 
            printf(" %.6f\t",h[imax2*j+i].p);
        }
        printf("\n");
        }
*/   

// if you want to compare the new pressures with that one obove you have to comment out that one above and calculate them new
h = new_p(h, RHS,  DX, DY, OM, EPS, imax2, jmax2);

//print the new_p
printf("\nNew pressure/ solve of the PDG\n");
for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            printf(" %.6f\t", h[imax2*j+i].p);
        }
        printf("\n");
        }

}