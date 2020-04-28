#include <stdlib.h>
#include <stdio.h>

xandy *put_xy_in_file(int imax, int jmax, float dx, float dy){
    // x und y Werte in ein File schreiben und arrays erstellen

    float xwert = 0, ywert = 0;
    
    xandy *c;
    c = calloc(imax + jmax,sizeof(xandy));

    FILE * xv;
    xv = fopen("x_values.txt", "w+");

	
	FILE * yv;
    yv = fopen("y_values.txt", "w+");

    for(int i = 0; i < imax; i++){
        c[i].x  = xwert;
        fprintf(xv, "%.6f\t", xwert);
        xwert += dx;  
    }

    //fprintf(xy, "\n");

    for(int j = 0; j < jmax; j++){
        c[j].y = ywert;
        fprintf(yv, "%.6f\t", ywert);
        ywert += dy;
        //printf("%.2f\n",y[j]);
    }

    int fclose (FILE *xv);
    int fclose (FILE *yv);

    return c; 

}