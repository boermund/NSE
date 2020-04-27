#include <stdlib.h>
#include <stdio.h>

xandy *put_xy_in_file(int imax, int jmax, float dx, float dy){
    // x und y Werte in ein File schreiben und arrays erstellen

    float xwert = 0, ywert = 0;
    
    xandy *c;
    c = calloc(imax + jmax,sizeof(xandy));

    FILE * xy;
    xy = fopen("x_and_y.txt", "w+");

    for(int i = 0; i < imax; i++){
        c[i].x  = xwert;
        fprintf(xy, "%.6f\t", xwert);
        xwert += dx;  
    }

    fprintf(xy, "\n");

    for(int j = 0; j < jmax; j++){
        c[j].y = ywert;
        fprintf(xy, "%.6f\t", ywert);
        ywert += dy;
        //printf("%.2f\n",y[j]);
    }

    int fclose (FILE *xy);
    return c; 

}