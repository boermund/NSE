
cell* cavity(cell *field,int imax, int jmax)
{
    int a=0;
    double b=0.05;
    /*
    for(int i=0;i<imax*jmax;i++){
        field[i].v  = 0.01;
        field[i].u  = 0;
        field[i].p  = 0;
        //printf("%d:%.2f\t%.2f\t%.2f\n",i,field[i].u,field[i].v,field[i].p);
    }
    */
    for(int i = 0;i<imax;i++)
    {
        field[(jmax-1)*imax+i].v    = -field[(jmax-2)*imax+i].v;
        field[(jmax-1)*imax+i].u    = a;
        field[i+imax*1].u                  = b;
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
        //field[j*imax + imax-3].u    = -3;
    
    }
    

    
    return field;
}