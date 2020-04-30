#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// fpr die Interationen von p werde ich meine eigene Struct entwerfen

// p_it+1 function 
//returns a float
float p_it(float xpi, float x, float xmi, float xpj, float xmimj, float RHS, float dx, float dy, float omega){
return (1 - omega)*x + omega * (1/ (2*( 1/pow(dx,2) + 1/pow(dy,2)) ) ) * 
        ( (xpi + xmi)/pow(dx,2)  +  (xpj + xmimj)/pow(dy,2)  -  RHS);
}

// p_it+1 struct
// returns a struct with all p_it+1 values

//pres p_it_struct()

// RHS
//returns a struct

rhs_struct *rhs_func( rhs_struct * RHS, cell_fg * fg, float dx, float dy, float dt, int imax, int jmax){


    //Randwerte - müssen nachher noch übergeben werden
    float f1 = 0;
    float g1 = 3;

    for(int j = 0; j < JMAX; j++){
    for(int i = 0; i < IMAX; i++){
        printf(" f: %.6f\t",fg[i].f);
        printf(" g: %.6f\t \n",fg[i].g);
    }
}


    for(int j = 0; j < jmax; j++){
    for(int i = 0; i < imax; i++){
        if(i == 0 || j == 0){
            if( i == 0 && j == 0){
            RHS[imax * j +i].rhs = 1/dt * ( ( fg[imax * j + i].f - f1)/dx + (fg[imax * j + i].g - g1)/dy);
            }
            else if (i == 0 && j != 0)
            {
                RHS[imax * j +i].rhs = 1/dt * ( ( fg[imax * j + i].f - f1)/dx + (fg[imax * j + i].g - fg[imax * (j - 1) + i].g ) /dy);
            }
           else{ // wenn was nicht funktionieren hier mal  else if(j == 0 && i != 0) einfügen
                 RHS[imax * j +i].rhs = 1/dt * ( ( fg[imax * j + i].f - fg[imax * j + i-1].f)/dx + (fg[imax * j + i].g - g1)/dy);
                 }
            }
        else{
        RHS[imax * j +i].rhs = 1/dt * ((fg[imax * j + i].f - fg[imax * j + i-1].f) / dx + (fg[imax * j + i].g - fg[imax * (j - 1) + i].g) / dy);
            }
        printf("%.6f \t", RHS[imax * j +i].rhs);
        }
    } //Randwerte noch mit einbauen!!! Das könnte dann schwierig mit if bedingungen werden, da die Randwert immer nach j * imax Werten kommen
    free(RHS);
    return RHS; 
}

// residuum
// returns a struct





// abs(residuum) as L_2 norm
// returns a float
float abs_res(cell * resi, int imax, int jmax){

    float residuum = 0;

    for(int j = 0; j < jmax; j++){
        for(int i = 0; i < imax; i++){
        residuum += pow(resi[imax*j+i].r,2);
        }
    }

    residuum = sqrt(residuum / (imax * jmax));

    return residuum; 
}
// ghost cell
// fill the fist variables of the struct