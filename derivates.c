#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* 
program to test the derivates n
*/

#define IMAX    50
#define JMAX    50
#define XMAX    13
#define YMAX    13

typedef struct
{
    float u;
    float v;
} cell;

typedef struct 
{
    float x; 
    float y; 
} xandy;


#include "read_data.h"
#include "allok.h"
#include "derivates.h"
#include "xandyvalues.h"
#include "gamma.h"
#include "testfunc.h"

void main(){

// define dx and dy and calculate them
    float dx, dy; 

    dx = (float)XMAX / (float)IMAX;
    dy =  (float)YMAX / (float)JMAX;

// put x and y values into a file and in a struct
    xandy *b;

    b = put_xy_in_file(IMAX,JMAX,dx,dy);

// calculate the values of u  and v
    FILE * testfile_u;
    testfile_u = fopen("testfunc_u.txt", "w+");

    FILE * testfile_v;
    testfile_v = fopen("testfunc_v.txt", "w+");
    
    for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(testfile_u, "%.6f\t", testfunc_u(b[i].x,b[j].y)) ;
           fprintf(testfile_v, "%.6f\t", testfunc_v(b[i].x,b[j].y)) ;
        }
        fprintf(testfile_u,"\n");
        fprintf(testfile_v,"\n");
    }

    fclose(testfile_u);
    fclose(testfile_v);

// write datas into a file
    testfile_u = fopen("testfunc_u.txt", "r");
    testfile_v = fopen("testfunc_v.txt", "r");

    cell *a;
    a = fieldalloc(IMAX,JMAX); 

    cell *u_values;
    u_values = read_data(a, testfile_u, testfile_v, IMAX, JMAX);

    fclose(testfile_u);
    fclose(testfile_v);
    
// derivates
// calculate the analytical and the numerical and put them in seperate files to plot an compare them. 

//first derivation dx
//numerical
    FILE * x_derivates;
    x_derivates = fopen("x_der_first.txt", "w+");


    for (int j = 0; j< JMAX; j++){
        for(int i = 0; i < IMAX -1; i++){
            fprintf(x_derivates, "%.6f\t", first_d(u_values[j*IMAX + (i+1)].u,u_values[j*IMAX + i].u,dx));
        }
        fprintf(x_derivates,"\n");
    }

    fclose(x_derivates);

//analytical
    FILE * x_derivates_ana;
    x_derivates_ana = fopen("x_der_ana_first.txt", "w+");

    for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(x_derivates_ana, "%.6f\t", test_der_u_x(b[i].x,b[j].y)) ;
        }
        fprintf(x_derivates_ana,"\n");
    }

fclose(x_derivates_ana);

// first derivation dy
//numerical
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

//analytical
    FILE * y_derivates_ana;
    y_derivates_ana = fopen("y_der_ana_first.txt", "w+");

    for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(y_derivates_ana, "%.6f\t", test_der_u_y(b[i].x,b[j].y)) ;
        }
        fprintf(y_derivates_ana,"\n");
    }

fclose(y_derivates_ana);

//second derivation dx
// numerical
FILE * x_sec_der;
x_sec_der = fopen("x_sec_der.txt","w+");

for(int j=0;j<JMAX;j++){
    for(int i = 0; i< IMAX-2; i++){
        fprintf(x_sec_der,"%.6f\t",secondx_d(u_values[IMAX*j+(i+2)].u,u_values[IMAX*j+(i+1)].u, u_values[IMAX*j+(i)].u, dx));
    }
    fprintf(x_sec_der,"\n");
}

fclose(x_sec_der);

//analytical
FILE * x_sec_der_ana;
x_sec_der_ana  = fopen("x_sec_der_ana.txt","w+");

for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(x_sec_der_ana, "%.6f\t", test_sec_der_x(b[i].x,b[j].y)) ;
        }
        fprintf(x_sec_der_ana,"\n");
    }

fclose(x_sec_der_ana);


//second derivation dy
//numerical
FILE * y_sec_der;
y_sec_der = fopen("y_sec_der.txt","w+");

for(int j=0;j<JMAX-2;j++){
    for(int i = 0; i< IMAX; i++){
        fprintf(y_sec_der,"%.6f\t",secondx_d(u_values[IMAX*(j+2)+(i)].u,u_values[IMAX*(j+1)+(i)].u, u_values[IMAX*j+(i)].u, dy));
    }
    fprintf(y_sec_der,"\n");
}
fclose(y_sec_der);

//analytical
FILE * y_sec_der_ana;
y_sec_der_ana  = fopen("y_sec_der_ana.txt","w+");

for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(y_sec_der_ana, "%.6f\t", test_sec_der_y(b[i].x,b[j].y)) ;
        }
        fprintf(y_sec_der_ana,"\n");
    }
fclose(y_sec_der_ana);

// non linear derivates and gamma

// calculate gamma an choose a dt
float gamma, dt;
dt = 0.01; // don't choose dt to big
gamma = gamma_v(u_values,dt,dx,IMAX,JMAX);

//derivate u^2 /dx
//numerical
FILE * x_nl2_der;
x_nl2_der = fopen("x_nl2_der.txt","w+");

for(int j=0;j<JMAX;j++){
    for(int i = 0; i< IMAX-2; i++){
        fprintf(x_nl2_der,"%.6f\t", non_l_quad(u_values[IMAX*j+(i+2)].u,u_values[IMAX*j+(i+1)].u, u_values[IMAX*j+(i)].u, dx, gamma));
    }
    fprintf(x_nl2_der,"\n");
}
fclose(x_nl2_der);

//analytical
FILE * x_nl2_der_ana;
x_nl2_der_ana  = fopen("x_nl2_der_ana.txt","w+");

for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(x_nl2_der_ana, "%.6f\t", test_nl2_der_x(b[i].x,b[j].y)) ;
        }
        fprintf(x_nl2_der_ana,"\n");
    }
fclose(x_nl2_der_ana); 

// derivate u^2/dy
//numerical
FILE * y_nl2_der;
y_nl2_der = fopen("y_nl2_der.txt","w+");

for(int j=0;j<JMAX-2;j++){
    for(int i = 0; i< IMAX; i++){
        fprintf(y_nl2_der,"%.6f\t", non_l_quad(u_values[IMAX*(j+2)+(i)].u, u_values[IMAX*(j+1)+(i)].u, u_values[IMAX*j+(i)].u, dy, gamma));
    }
    fprintf(y_nl2_der,"\n");
}

fclose(y_nl2_der);

//analytical
FILE * y_nl2_der_ana;
y_nl2_der_ana  = fopen("y_nl2_der_ana.txt","w+");

for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(y_nl2_der_ana, "%.6f\t", test_nl2_der_y(b[i].x,b[j].y)) ;
        }
        fprintf(y_nl2_der_ana,"\n");
    }
fclose(y_nl2_der_ana); 

// calculate u*v 
FILE * uv;
uv  = fopen("uv_test.txt","w+");

for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(uv, "%.6f\t", testfunc_uv(b[i].x,b[j].y, testfunc_u, testfunc_v)) ;
        }
        fprintf(uv,"\n");
    }
fclose(uv); 

// derivate u*v /dx

//numerical
FILE * x_nluv_der;
x_nluv_der = fopen("x_nluv_der.txt","w+");

for(int j=0;j<JMAX-1;j++){
    for(int i = 0; i< IMAX-2; i++){
        fprintf(x_nluv_der,"%.6f\t", non_uvx(u_values[IMAX*(j+1)+(i+1)].u,u_values[IMAX*j+(i+1)].u, u_values[IMAX*j+(i)].u,u_values[IMAX*(j+1)+(i)].u,  dx, u_values[IMAX*(j)+(i+2)].v,u_values[IMAX*j+(i+1)].v, u_values[IMAX*j+(i)].v, gamma));
    }
    fprintf(x_nluv_der,"\n");
}
fclose(x_nluv_der);

// analytical
FILE * uv_x;
uv_x  = fopen("x_nluv_der_ana.txt","w+");

for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(uv_x, "%.6f\t", testfunc_uv_der_x(b[i].x, b[j].y, testfunc_u, testfunc_v)) ;
        }
        fprintf(uv_x,"\n");
    }
fclose(uv_x);


// derivate u*v/dy

// numerical
FILE * y_nluv_der;
y_nluv_der = fopen("y_nluv_der.txt","w+");

for(int j=0;j<JMAX-2;j++){
    for(int i = 0; i< IMAX-1; i++){
        fprintf(y_nluv_der,"%.6f\t", non_uvy(u_values[IMAX*(j+1)+(i+1)].v,u_values[IMAX*(j+1)+(i)].v, u_values[IMAX*(j)+(i)].v,u_values[IMAX*(j)+(i+1)].v,  dy, u_values[IMAX*(j+2)+(i)].u,u_values[IMAX*(j+1)+(i)].u, u_values[IMAX*j+(i)].u, gamma));
    }
    fprintf(y_nluv_der,"\n");
}
fclose(y_nluv_der);

// analytical
FILE * uv_y;
uv_y  = fopen("y_nluv_der_ana.txt","w+");

for(int j=0;j<JMAX;j++){
        for(int i=0;i<IMAX;i++){
           fprintf(uv_y, "%.6f\t", testfunc_uv_der_y(b[i].x, b[j].y, testfunc_u, testfunc_v)) ;
        }
        fprintf(uv_y,"\n");
    }
fclose(uv_y); 
}






