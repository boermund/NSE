#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define IMAX    10
#define JMAX    10
#define XMAX    10
#define YMAX    10

typedef struct
{
    float u;
} cell;

typedef struct 
{
    float x; // lange: IMAX
    float y; //lange: JMAX
} xandy;


#include "read_data.h"
#include "allok.h"
#include "derivates.h"
#include "xandyvalues.h"

void main(){

    float dx, dy; 

    dx = XMAX / IMAX;
    dy =  YMAX / JMAX;

   cell *a;

    a = fieldalloc(IMAX,JMAX); //Size of the field plus the edges
    // Ziel: Testfunktion u = cos(x)sin(y) eingeben und ableitungen rausgeben. Dazu sollen erstmal werte von 0 bis 5

    xandy *b;

    b = put_xy_in_file(IMAX,JMAX,dx,dy);

    

//Funktionswerte berechnen und in ein File schreiben
    FILE * testfile_u;
    testfile_u = fopen("testfunc_u.txt", "w+");
    
    for(int j=0;j<IMAX;j++){
        for(int i=0;i<JMAX;i++){
           fprintf(testfile_u, "%.6f\t", testfunc_u(b[i].x,b[j].y)) ;
        }
        fprintf(testfile_u,"\n");
    }


    int fclose (FILE *testfile_u);


    // nächste Aufgabe: ABleitungen berechnen 
        //erstmal die mit nur einer Funktion (morgen) 

}







