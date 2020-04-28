#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define IMAX    2
#define JMAX    6



//Matrix: SPeicher reservieren
//#define BUF 255

typedef struct
{
    float u;
} cell;

#include "allok.h"
#include "read_data.h"
#include "gamma.h"

int main(void) {

    FILE *myFile;
    myFile = fopen("test.txt", "r");

    if (myFile == NULL){
        printf("Error Reading File\n");
        exit (0);
    }

    cell *a, *new;
    a = fieldalloc(IMAX,JMAX);
    
    new = read_data(a, myFile, IMAX,JMAX); //Size of the field plus the edges
    fclose(myFile);

   
   //gibt das Strukt aus
   for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
        printf("%.6f\t",new[i+IMAX*j].u);}
    } 

    printf("\n");

    float gamma;

    gamma = gamma_v(new,0.001, 0.5, IMAX, JMAX);
    printf("%.6f", gamma);
    return 0;
}