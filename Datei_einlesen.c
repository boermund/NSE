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
    myFile0 = fopen("test0.txt", "w+");

    float k = 2.3;
    for(int j = 0; j < JMAX; j++){
        for( int i= 0; i< IMAX; i++){
        fprintf(myFile0,"%.6f\n", (float)pow(i,pow(-1,k))/k);
        printf("%.6f\n", (float)pow(i,pow(-1,k))/k);}
        fprintf(myFile0, "\n");
    }

    fclose(myFile0);

    FILE *myFile1;
    myFile1 = fopen("test1.txt", "w+");

    for(int j = 0; j < JMAX; j++){
        for( int i= 0; i< IMAX; i++){
        fprintf(myFile0,"%.6f\n", (float)pow(i,pow(-1,k))/k);
        printf("%.6f\n",  (float)pow(i,pow(-1,k))/k);}
        fprintf(myFile1, "\n");
    }

    fclose(myFile1);

    FILE *myFile;
    myFile = fopen("test0.txt", "r");

     FILE *myFile2;
    myFile = fopen("test1.txt", "r");

    cell *a, *new;
    a = fieldalloc(IMAX,JMAX);
    
    new = read_data(a, myFile, myFile2, IMAX,JMAX);

    fclose(myFile);
    fclose(myFile2);

    float gamma;

    gamma = gamma_v(new,0.001, 0.5, IMAX, JMAX);
    printf("%.6f", gamma);
    return 0;
}