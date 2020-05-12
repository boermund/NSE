double Ffunction(cell* field,int z,int imax, int jmax, double dt, double dx, double dy,double gamma){
    double newF = field[z].u
    + dt*(
    (
    secondx_d(field[z+1].u,field[z].u,field[z-1].u,dx) +
    secondx_d(field[z+1].v,field[z].v,field[z-1].v,dy)
    ) 
    / RE
    - non_l_quad(field[z+1].u,field[z].u,field[z-1].u,dx,gamma)
    - non_uvy(field[z+1].v,field[z].v,field[z-imax].v,field[z+1-imax].v,dy,field[z+imax].v,field[z].u,field[z-imax].u,gamma)
    + GX);
    return newF;
}

double Gfunction(cell* field,int z,int imax, int jmax, double dt, double dx, double dy, double gamma){
    double newG = field[z].v
    + dt*(
    (
    secondx_d(field[z+1].v,field[z].v,field[z-1].v,dx) +
    secondx_d(field[z+1].v,field[z].v,field[z-1].v,dy)
    ) /RE
    - non_l_quad(field[z+1].v,field[z].v,field[z-1].v,dy,gamma) 
    - non_uvx(field[z+imax].u,field[z].u,field[z-1].u,field[z-1+imax].u,dx,field[z+1].v,field[z].v,field[z-1].v,gamma)
    + GY);
    return newG;
}

cell *newspeed(cell*old,f_and_g *newfg,int imax,int jmax,double dx,double dy,double dt, double gamma){
    //Zwei kleiner weil die Randwertew fehlen
    
for(int i = 0; i < imax * jmax ;i++)
    {
        //if((i>imax+1 && (i<imax*(jmax-1)))&&((i%imax!=0)&&(i*imax!=imax-1))){
        
        old[i].u = newfg[i].fvalue -
        dt *
        first_d(old[i+1].p,old[i].p,dx);

        old[i].v = newfg[i].gvalue -
        dt * 
        first_d(old[i+imax].p,old[i].p,dy);
        //printf("speed%d:%.2f\t%.2f\n",i,old[i].u,old[i].v);
        //printf("%d:\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\n",i,newfg[i].fvalue,newfg[i].gvalue,newuv[i].u,newuv[i].v,newuv[i].p);
        //output(new,IMAX+2,JMAX+2);
    }
    return old;
}

f_and_g *new_f_and_g(cell*old,int imax,int jmax,double dx,double dy,double dt, double gamma){
    f_and_g *newfg; //In deiner Funktion wieder frei machen
    newfg = calloc((imax)*(jmax),sizeof(f_and_g)); //Zwei kleiner weil die Randwertew fehlen
    for(int i = 0; i < imax * jmax ;i++)
    {
        if((i > imax && (i < imax * (jmax - 1))) && ((i % imax != 0) && (i % imax != (imax - 1)))){
            newfg[i].fvalue = Ffunction(old,i,imax,jmax,dt,dx,dy,gamma);
        }
        else{
            newfg[i].fvalue = old[i].u;
        }
        if((i > 1 * imax && (i < imax * (jmax-1))) && (( i % imax != 0) && (i % imax != (imax - 1))))
        {
            newfg[i].gvalue = Gfunction(old,i,imax,jmax,dt,dx,dy,gamma); 
        }
        else
        {
            newfg[i].gvalue = old[i].v;
        }
        
        
        //printf("%d:\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\n",i,newfg[i].fvalue,newfg[i].gvalue,newuv[i].u,newuv[i].v,newuv[i].p);
        //output(new,IMAX+2,JMAX+2);
        
        //printf("%d:%.2f\t%.2f\n",i,newfg[i].fvalue,newfg[i].gvalue);
    }
    //printf("f&g:");
    //for(int i=0;i<imax*jmax;i++){
    //printf("%d:%.2f\t%.2f\n",i,newfg[i].fvalue,newfg[i].gvalue);
    //}

    return newfg;
}
