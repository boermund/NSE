
cell* cavity(cell *field,int imax2, int jmax2,int p)
{
    double a = 0;
    double b = 1000;
    /*
    for(int i=0;i<imax2*jmax2;i++){
        field[i].v  = 0.1;
        field[i].u  = 0.1;
        field[i].p  = 1;
        //printf("%d:%.2f\t%.2f\t%.2f\n",i,field[i].u,field[i].v,field[i].p);
    }
    */
   
    for(int j = 0;j<jmax2;j++)
    {
        field[j*(imax2)].v            = -field[j*(imax2)+1].v;
        //printf("%f",-field[j*(imax2)+1].u);
        field[j*(imax2)].u            = a;
        field[j*(imax2)+imax2-1].v    = -field[j*(imax2)+imax2-2].v;
        field[j*(imax2)+imax2-2].u    = a;
        field[j*(imax2)+imax2-1].u    = field[j*(imax2)+imax2-2].u;
        //field[j*imax2 + imax2-3].u) = -3;
    
    }
    
    for(int i = 0;i<imax2;i++)
    {
        field[(jmax2-1)*imax2+i].u    = -field[(jmax2-2)*imax2+i].u;
        field[(jmax2-1)*imax2+i].v    = a;
        field[i].u                    = 2 * b - field[i+imax2].u;
        //printf("\n%.3f\n",field[i].u);
        field[i+imax2*1].v            = a;
        field[i].v                    = field[i+imax2*1].v;
        //printf("%f\n",field[i+imax2].u);
        //field[i].v                  = -field[i+imax2].v;
    }    

    
    return field;
}