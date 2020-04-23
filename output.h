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
            fprintf(vspeed,"%.6f\t",field[i+imax*j].u);
            fprintf(uspeed,"%.6f\t",field[i+imax*j].v);
            fprintf(pressure,"%.6f\t",field[i+imax*j].p);
            //printf("%d",i+imax*j);
        }
        fprintf(vspeed,"\n");
        fprintf(uspeed,"\n");
        fprintf(pressure,"\n");
    }

}