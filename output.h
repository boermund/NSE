//Functions for output of data

void output(cell *field,int imax,int jmax)
{   
    printf("hello1\n");
    FILE * vspeed;
    vspeed = fopen ("vspeed.csv","w+");
    FILE *uspeed;
    uspeed = fopen("uspeed.csv", "w+");
    FILE *pressure;
    pressure = fopen("pressure.csv", "w+");

    printf("\nhello2\n");
    for (int z = 0; z < IMAX * JMAX; z++)
        //printf("%d:\t%.2f\t%.2f\t%.2f\n",z,field[z].u,field[z].v,field[z].p);
    for(int j=0;j<jmax;j++){
        for(int i=0;i<imax;i++){
            fprintf(vspeed,"%.2f,",field[i+imax*j].v);
            fprintf(uspeed,"%.2f,",field[i+imax*j].u);
            fprintf(pressure,"%.2f,",field[i+imax*j].p);
        
        }
        fprintf(vspeed,"\n");
        fprintf(uspeed,"\n");
        fprintf(pressure,"\n");
    }
    fclose(vspeed);
    fclose(uspeed);
    fclose(pressure);
    
}