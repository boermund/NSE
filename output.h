//Functions for output of data

void output(cell *field,int imax,int jmax)
{
    FILE * vspeed;
    vspeed = fopen ("vspeed.txt","w+");
    FILE * uspeed;
    uspeed = fopen ("uspeed.txt","w+");
    FILE * pressure;
    pressure = fopen ("pressure.txt","w+");
    for(int j=0;j<jmax;j++){
        for(int i=0;i<imax;i++){
            fprintf(vspeed,"%.6f\t",field[i+jmax*j].u);
            fprintf(uspeed,"%.6f\t",field[i+jmax*j].v);
            fprintf(pressure,"%.6f\t",field[i+jmax*j].p);
            //printf("%d",i+jmax*j);
        }
        fprintf(vspeed,"\n");
        fprintf(uspeed,"\n");
        fprintf(pressure,"\n");
    }

}