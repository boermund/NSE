#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* testfile to write a txt file into a struct an caluculate the gamma value
*/
#define IMAX    2
#define JMAX    6

typedef struct
{
    float u;
    float v;
} cell;

#include "allok.h"
#include "read_data.h"
#include "gamma.h"

int main(void) {

    FILE *myFile0;
    myFile0 = fopen("test.txt", "w+");

    float g = 2.3;
    for(int j = 0; j < JMAX; j++){
        for( int i= 0; i< IMAX; i++){
        fprintf(myFile0,"%f\n", ((float)rand()/(float)(RAND_MAX)) * g);}
        fprintf(myFile0, "\n");
    }

    fclose(myFile0);

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