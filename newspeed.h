float Ffunction(cell* field,int z,int imax, int jmax, float dt, float dx, float dy,float gamma){
    float newF = field[z].u
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

float Gfunction(cell* field,int z,int imax, int jmax, float dt, float dx, float dy, float gamma){
    float newG = field[z].v
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

new_values newspeed(cell*old,int imax,int jmax,float dx,float dy,float dt, float gamma){
    cell *newuv;
    f_and_g *newfg; //In deiner Funktion wieder frei machen
    newuv = calloc(imax*jmax,sizeof(cell));
    newfg = calloc((imax)*(jmax),sizeof(f_and_g)); //Zwei kleiner weil die Randwertew fehlen
    
for(int i = 0; i < imax * jmax ;i++)
    {
        if((i>imax+1 && (i<imax*(jmax-1)))&&((i%imax!=0)&&(i*imax!=imax-1))){
        newfg[i].fvalue = Ffunction(old,i,imax,jmax,dt,dx,dy,gamma);
        newfg[i].gvalue = Gfunction(old,i,imax,jmax,dt,dx,dy,gamma); 
        
        newuv[i].u = newfg[i].fvalue -
        dt *
        first_d(old[i+1].p,old[i].p,dx);

        newuv[i].v = newfg[i].gvalue -
        dt * 
        first_d(old[i+imax].p,old[i].p,dy);
        }
        newuv[i].p=old[i].p;
        else{
            
        }
        //printf("%d:\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\n",i,newfg[i].fvalue,newfg[i].gvalue,newuv[i].u,newuv[i].v,newuv[i].p);
        //output(new,IMAX+2,JMAX+2);
    }
    new_values passback;
    passback.field = newuv;
    //free(newuv);
    passback.fg = newfg;
    //free(newfg);
    return passback;
}

f_and_g *new_f_and_g(cell*old,int imax,int jmax,float dx,float dy,float dt, float gamma){
    cell *newuv;
    f_and_g *newfg; //In deiner Funktion wieder frei machen
    newuv = calloc(imax*jmax,sizeof(cell));
    newfg = calloc((imax)*(jmax),sizeof(f_and_g)); //Zwei kleiner weil die Randwertew fehlen
    
for(int i = 0; i < imax * jmax ;i++)
    {
        if((i>imax+1 && (i<imax*(jmax-1)))&&((i%imax!=0)&&(i*imax!=imax-1))){
        newfg[i].fvalue = Ffunction(old,i,imax,jmax,dt,dx,dy,gamma);
        newfg[i].gvalue = Gfunction(old,i,imax,jmax,dt,dx,dy,gamma); 
    
        //printf("%d:\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\n",i,newfg[i].fvalue,newfg[i].gvalue,newuv[i].u,newuv[i].v,newuv[i].p);
        //output(new,IMAX+2,JMAX+2);
    }
    new_values passback;
    passback.field = newuv;
    //free(newuv);
    passback.fg = newfg;
    //free(newfg);
    return passback;
}
