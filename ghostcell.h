
cell* cavity(cell *field,int imax, int jmax)
{
    int a=0;
    int b=0;
    for(int j = 1;j<jmax-1;j++)
    {
        field[j*(imax)].u           = -field[j*(imax)+1].u;
        printf("%f",-field[j*(imax)+1].u);
        field[j*(imax)].v           = a;
        field[j*(imax)+imax-1].u    = -field[j*(imax)+imax-2].u;
        field[j*(imax)+imax-2].v    = a;
    }
    for(int i = 1;i<imax-1;i++)
    {
        field[(jmax-1)*imax+i].v    = -field[(jmax-2)*imax+i].v;
        field[(jmax-1)*imax+i].u    = a;
        field[i].u                  = b;
        //printf("%f\n",field[i+imax].u);
        field[i].v                  = -field[i+imax].v;
    }
    return field;
}