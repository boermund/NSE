#include <stdlib.h>
#include <stdio.h>

/* put x an y values in a seperate file and return a struct
needed for testfunctions
return a struct
*/

xandy *put_xy_in_file(int imax, int jmax, float dx, float dy){


    float xwert = 0, ywert = 0;
// make a struct
    xandy *c;
    c = calloc(imax + jmax,sizeof(xandy));

// open files
    FILE * xv;
    xv = fopen("x_values.txt", "w+");
	FILE * yv;
    yv = fopen("y_values.txt", "w+");

// write values into files
    for(int i = 0; i < imax; i++){
        c[i].x  = xwert;
        fprintf(xv, "%.6f\t", xwert);
        xwert += dx;  
    }

    for(int j = 0; j < jmax; j++){
        c[j].y = ywert;
        fprintf(yv, "%.6f\t", ywert);
        ywert += dy;
    }

    int fclose (FILE *xv);
    int fclose (FILE *yv);

    return c; 

}