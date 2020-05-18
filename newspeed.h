double Ffunction(cell* field,int z,int imax2, int jmax2, double dt, double dx, double dy,double gamma){
    double newF = field[z].u
    + dt*(
    (
    secondx_d(field[z+1].u,field[z].u,field[z-1].u,dx) +
    secondx_d(field[z+imax2].u,field[z].u,field[z-imax2].u,dy)
    ) 
    / RE
    - non_l_quad(field[z+1].u,field[z].u,field[z-1].u,dx,gamma)
    - non_uvy(field[z+1].v,field[z].v,field[z-imax2].v,field[z+1-imax2].v,dy,field[z+imax2].u,field[z].u,field[z-imax2].u,gamma)
    + GX);
    return newF;
}

double Gfunction(cell* field,int z,int imax2, int jmax2, double dt, double dx, double dy, double gamma){
    double newG = field[z].v
    + dt*(
    (
    secondx_d(field[z+1].v,field[z].v,field[z-1].v,dx) +
    secondx_d(field[z+imax2].v,field[z].v,field[z-imax2].v,dy)
    ) /RE
    - non_l_quad(field[z+imax2].v,field[z].v,field[z-imax2].v,dy,gamma) 
    - non_uvx(field[z+imax2].u,field[z].u,field[z-1].u,field[z-1+imax2] .u,dx,field[z+1].v,field[z].v,field[z-1].v,gamma)
    + GY);
    return newG;
}

cell *newspeed(cell*old,f_and_g *newfg,int imax2,int jmax2,double dx,double dy,double dt, double gamma){
    //Zwei kleiner weil die Randwertew fehlen
    
for(int i = 0; i < imax2 * jmax2 ;i++)
    {
        //if((i>imax2+1 && (i<imax2*(jmax2-1)))&&((i%imax2!=0)&&(i*imax2!=imax2-1))){
        
        old[i].u = newfg[i].fvalue -
        dt *
        first_d(old[i+1].p,old[i].p,dx);

        old[i].v = newfg[i].gvalue -
        dt * 
        first_d(old[i+imax2].p,old[i].p,dy);
        //printf("speed%d:%.2f\t%.2f\n",i,old[i].u,old[i].v);
        //printf("%d:\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\n",i,newfg[i].fvalue,newfg[i].gvalue,newuv[i].u,newuv[i].v,newuv[i].p);
        //output(new,imax2+2,jmax2+2);
    }
    return old;
}

f_and_g *new_f_and_g(cell*old,f_and_g* newfg,int imax2,int jmax2,double dx,double dy,double dt, double gamma){
    //f_and_g *newfg; //In deiner Funktion wieder frei machen
    //newfg = calloc((imax2)*(jmax2),sizeof(f_and_g)); //Zwei kleiner weil die Randwertew fehlen
    for(int i = 0; i < imax2 * jmax2 ;i++)
    {
        if((i > 1 * imax2 && (i < imax2 * (jmax2 - 1))) && ((i % imax2 != 0) && ((i+2) % imax2 != 0) && ((i+1) % imax2 != 0))){
            newfg[i].fvalue = Ffunction(old,i,imax2,jmax2,dt,dx,dy,gamma); //Ableitung benötigt Werte die eigentlich ausserhalb von Rand liegen
        }
        else{
            if((i+1)%imax2 != 0)
                newfg[i].fvalue = old[i].u; 
        }
        if((i > 2 * imax2 && (i < imax2 * (jmax2-1))) && (( i % imax2 != 0) && (i % imax2 != (imax2 - 1))))
        {
            newfg[i].gvalue = Gfunction(old,i,imax2,jmax2,dt,dx,dy,gamma); 
        }
        else
        {
            if(i>=imax2)
                newfg[i].gvalue = old[i].v;
        }
        
        
        //printf("%d:\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\n",i,newfg[i].fvalue,newfg[i].gvalue,newuv[i].u,newuv[i].v,newuv[i].p);
        //output(new,imax2+2,jmax2+2);
        
        //printf("%d:%.2f\t%.2f\n",i,newfg[i].fvalue,newfg[i].gvalue);
    }
    //printf("f&g:");
    //for(int i=0;i<imax2*jmax2;i++){
    //printf("%d:%.2f\t%.2f\n",i,newfg[i].fvalue,newfg[i].gvalue);
    //}

    return newfg;
}
