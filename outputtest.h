cell * outputtest(cell *a,int imax, int jmax){ 
    for(int z=0;z<imax*jmax;z++)
        {
        a[z].u=sin((z-imax*(10%imax))/imax)*cos((z-z%imax)/imax);
        a[z].v=sin((z-imax*(10%imax))/imax)*cos((z-z%imax)/imax);
        a[z].p=(z-z%imax)/imax;  
        }
    return a;
}

cell * speedtest(cell *a, int imax, int jmax){
    float start = 0.1;
    float idef = (int)(imax/2)-0.5;
    float jdef = (int)(jmax/2)-0.5;
    for (int i=0; i < imax*jmax; i++){
        a[i].p= start / sqrt((pow((i%imax-idef),2)+pow(jdef-((i-i%imax)/jmax),2))+2);
    }
    return a;
}