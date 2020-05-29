//Functions for output of data

void output(cell *field,int imax2,int jmax2)
{   
    printf("hello1\n");
    FILE * vspeed;
    vspeed = fopen ("vspeed.csv","w+");
    FILE *uspeed;
    uspeed = fopen("uspeed.csv", "w+");
    FILE *pressure;
    pressure = fopen("pressure.csv", "w+");

    printf("\nhello2\n");
    //for (int z = 0; z < imax2 * jmax2; z++)
        //printf("%d:\t%.2f\t%.2f\t%.2f\n",z,field[z].u,field[z].v,field[z].p);
    for(int j=0;j<jmax2;j++){
        for(int i=0;i<imax2;i++){
            fprintf(vspeed,"%.5f,",field[i+imax2*j].v);
            fprintf(uspeed,"%.5f,",field[i+imax2*j].u);
            fprintf(pressure,"%.5f,",field[i+imax2*j].p);
        
        }
        fprintf(vspeed,"\n");
        fprintf(uspeed,"\n");
        fprintf(pressure,"\n");
    }
    fclose(vspeed);
    fclose(uspeed);
    fclose(pressure);
    printf("Output Done");
}