
cell* cavity(cell *field,int imax, int jmax)
{
    int a=0;
    float b=1;
    
    for(int i = 0;i<imax;i++)
    {
        field[(jmax-1)*imax+i].v    = -field[(jmax-2)*imax+i].v;
        field[(jmax-1)*imax+i].u    = a;
        field[i+imax].u                  = b;
        //printf("%f\n",field[i+imax].u);
        field[i].v                  = -field[i+imax].v;
    }
    for(int j = 0;j<jmax;j++)
    {
        field[j*(imax)].u           = -field[j*(imax)+1].u;
        //printf("%f",-field[j*(imax)+1].u);
        field[j*(imax)].v           = a;
        field[j*(imax)+imax-1].u    = -field[j*(imax)+imax-2].u;
        field[j*(imax)+imax-2].v    = a;
    }

    printf("cavity:\n");
    for(int i=0;i<imax*jmax;i++){
        printf("%d:%.2f\t%.2f\n",i,field[i].u,field[i].v);
    }

    return field;
}