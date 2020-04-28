//Functions for output of data

void output(cell *field,int imax,int jmax)
{
    FILE * vspeed;
    vspeed = fopen ("vspeed.csv","w+");
    FILE * uspeed;
    uspeed = fopen ("uspeed.csv","w+");
    FILE * pressure;
    pressure = fopen ("pressure.csv","w+");
    for(int j=0;j<jmax;j++){
        for(int i=0;i<imax;i++){
            fprintf(vspeed,"%.2f,",field[i+imax*j].v);
            fprintf(uspeed,"%.2f,",field[i+imax*j].u);
            fprintf(pressure,"%.2f,",field[i+imax*j].p);
            //printf("%d",i+imax*j);
        }
        fprintf(vspeed,"\n");
        fprintf(uspeed,"\n");
        fprintf(pressure,"\n");
    }

}