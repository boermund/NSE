#include <math.h>

cell max_field(cell *field,int imax, int jmax){
    cell max;
    max.p=max.u=max.v=0;
    for(int i=0 ; i<imax*jmax;i++)
        {
        if(field[i].u   <   max.u)
            max.u   =   field[i].u;
        if(field[i].v<max.v)
            max.v   =   field[i].v;
        if(field[i].p<max.p)
            max.p   =   field[i].p;
        }
    if (max.u==0)
        max.u   =   0.000001;
    if (max.v==0)
        max.v   =   0.000001;
    return max;
}

float min(float a, float b, float c){
    float min   = a;
    if(min>b)
        min     = b;
    if(min>c)
        min     = c;
    return min;
}


float timecontrol(cell* feld,float tau,int imax,int jmax,float dx, float dy,float Re){
    cell max =  max_field(feld,imax, jmax);
    float newtime;
    newtime =   tau * min(dx/max.u,dy/max.v,Re/2*1/(pow(dx,-2)+pow(dy,-2)));
    //printf("\n%f",tau* min(dx/max.u,dy/max.v,Re/2*1/(pow(dx,-2)+pow(dy,-2))));
    //printf("\n%f\n",newtime);
    return newtime; 
}
