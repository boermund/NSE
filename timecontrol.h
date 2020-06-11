#include <math.h>

cell max_field(cell *field,int imax2, int jmax2){
    cell max;
    max.p=max.u=max.v=0;
    for(int i=0 ; i<imax2*jmax2;i++)
        {
        if((i+1) % imax2 != 0){
            if(field[i].u   >   max.u)
                max.u   =   field[i].u;
        }
        if(i > imax2-1){
            if(field[i].v   >   max.v)
                max.v   =   field[i].v;
        }
        if(field[i].p   >   max.p)
            max.p   =   field[i].p;
        }
    if (max.u==0)
        max.u   =   0.000001;
    if (max.v==0)
        max.v   =   0.000001;
    return max;
}

double min(double a, double b, double c){
    double min   = a;
    if(min>b)
        min     = b;
    if(min>c)
        min     = c;
    return min;
}


double timecontrol(cell* feld,double tau,int imax2,int jmax2,double dx, double dy,double Re){
    cell max =  max_field(feld,imax2, jmax2);
    double newtime;
    newtime =   tau * min(dx/fabs(max.u),dy/fabs(max.v),Re/2*1/(pow(dx,-2)+pow(dy,-2)));
    //printf("\n%f",tau* min(dx/max.u,dy/max.v,Re/2*1/(pow(dx,-2)+pow(dy,-2))));
    //printf("\n%f\n",newtime);
    return newtime; 
}
