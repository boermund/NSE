cell * outputtest(cell *a,int imax, int jmax){ 
    for(int z=0;z<imax*jmax;z++)
        {
        a[z].u=sin((z-imax*(10%imax))/imax)*cos((z-z%imax)/imax);
        a[z].v=sin((z-imax*(10%imax))/imax)*cos((z-z%imax)/imax);
        a[z].p=(z-z%imax)/imax;  
        }
    return a;
}