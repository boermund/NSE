#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define IMAX    10
#define JMAX    20
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

    dx = (float)XMAX / (float)IMAX;
    dy =  (float)YMAX / (float)JMAX;

   cell *a;

    a = fieldalloc(IMAX,JMAX); //Size of the field plus the edges
    // Ziel: Testfunktion u = cos(x)sin(y) eingeben und ableitungen rausgeben. Dazu sollen erstmal werte von 0 bis 5


    printf("%.6f\n",dx);
    printf("%.6f",dy);


    xandy *b;

    b = put_xy_in_file(IMAX,JMAX,dx,dy);

//Funktionswerte berechnen und in ein File schreiben
    FILE * testfile_u;
    testfile_u = fopen("testfunc_u.txt", "w+");
    
    for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(testfile_u, "%.6f\t", testfunc_u(b[i].x,b[j].y)) ;
        }
        fprintf(testfile_u,"\n");
    }

fclose(testfile_u);

testfile_u = fopen("testfunc_u.txt", "r");

    //int fclose (FILE *testfile_u);

    cell *u_values;
    a = fieldalloc(IMAX,JMAX);

    u_values = read_data(a, testfile_u, IMAX, JMAX);

    /*for (int i = 0; i< IMAX*JMAX; i++){
    printf("%f", u_values[i].u);
    }

    fclose(testfile_u);*/


    //ABleitungen berechnen: IMAX - 1 mal der differenzenquotient möglich


    //Erste Ableittung
    // ABleitung nach x: 
    FILE * x_derivates;
    x_derivates = fopen("x_der_first.txt", "w+");


    for (int j = 0; j< JMAX; j++){
        for(int i = 0; i < IMAX -1; i++){
            fprintf(x_derivates, "%.6f\t", first_d(u_values[j*IMAX + (i+1)].u,u_values[j*IMAX + i].u,dx));
        }
        fprintf(x_derivates,"\n");
    }

    fclose(x_derivates);

    FILE * x_derivates_ana;
    x_derivates_ana = fopen("x_der_ana_first.txt", "w+");

    for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(x_derivates_ana, "%.6f\t", test_der_u_x(b[i].x,b[j].y)) ;
        }
        fprintf(x_derivates_ana,"\n");
    }

fclose(x_derivates_ana);

// Zweite ABleitung
FILE * y_derivates;
    y_derivates = fopen("y_der_first.txt", "w+");

    for(int j = 0; j < JMAX-1; j++){
        for (int i = 0; i< IMAX; i++)
        {
            fprintf(y_derivates, "%.6f\t", first_d(u_values[(j+1)*IMAX + i].u,u_values[j*IMAX + i].u,dy)); 
        }
        fprintf(y_derivates,"\n");  // hier werden die Daten in y richtung in eine Zeile geschrieben !! dir müssen alo für die Graphische darstellung noch transponiert werden
    }

    fclose(y_derivates);

    FILE * y_derivates_ana;
    y_derivates_ana = fopen("y_der_ana_first.txt", "w+");

    for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(y_derivates_ana, "%.6f\t", test_der_u_y(b[i].x,b[j].y)) ;
        }
        fprintf(y_derivates_ana,"\n");
    }

fclose(y_derivates_ana);

//zweite ABleitungen

FILE * x_sec_der;
x_sec_der = fopen("x_sec_der.txt","w+");

for(int j=0;j<JMAX;j++){
    for(int i = 0; i< IMAX-2; i++){
        fprintf(x_sec_der,"%.6f\t",secondx_d(u_values[IMAX*j+(i+2)].u,u_values[IMAX*j+(i+1)].u, u_values[IMAX*j+(i)].u, dx));
    }
    fprintf(x_sec_der,"\n");
}

fclose(x_sec_der);

FILE * x_sec_der_ana;
x_sec_der_ana  = fopen("x_sec_der_ana.txt","w+");

for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(x_sec_der_ana, "%.6f\t", test_sec_der_x(b[i].x,b[j].y)) ;
        }
        fprintf(x_sec_der_ana,"\n");
    }

fclose(x_sec_der_ana);



FILE * y_sec_der;
y_sec_der = fopen("y_sec_der.txt","w+");

for(int j=0;j<JMAX-2;j++){
    for(int i = 0; i< IMAX; i++){
        fprintf(y_sec_der,"%.6f\t",secondx_d(u_values[IMAX*(j+2)+(i)].u,u_values[IMAX*(j+1)+(i)].u, u_values[IMAX*j+(i)].u, dx));
    }
    fprintf(y_sec_der,"\n");
}

fclose(y_sec_der);

FILE * y_sec_der_ana;
y_sec_der_ana  = fopen("y_sec_der_ana.txt","w+");

for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(y_sec_der_ana, "%.6f\t", test_sec_der_y(b[i].x,b[j].y)) ;
        }
        fprintf(y_sec_der_ana,"\n");
    }

fclose(y_sec_der_ana);

// nicht lineare Ableitungen

//u^2

FILE * x_nl2_der;
x_nl2_der = fopen("y_nl2_der.txt","w+");

for(int j=0;j<JMAX-2;j++){
    for(int i = 0; i< IMAX; i++){
        fprintf(x_nl2_der,"%.6f\t", non_l_quad(u_values[IMAX*j+(i+2)].u,u_values[IMAX*j+(i+1)].u, u_values[IMAX*j+(i)].u, dx, ));
    }
    fprintf(x_nl2_der,"\n");
}

fclose(x_sec_der);

FILE * x_nl2_der_ana;
x_nl2_der_ana  = fopen("y_nl2_der_ana.txt","w+");

for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(x_nl2_der_ana, "%.6f\t", test_nl2_der_x(b[i].x,b[j].y)) ;
        }
        fprintf(x_nl2_der_ana,"\n");
    }

fclose(x_nl2_der_ana);





}







