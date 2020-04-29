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
    cell *new;
    f_and_g *newfg; //In deiner Funktion wieder frei machen
    new = calloc(imax*jmax,sizeof(cell));
    newfg = calloc((imax-2)-(jmax-2),sizeof(f_and_g)); //Zwei kleiner weil die Randwertew fehlen
    for(int i = 0; i < imax * jmax ;i++)
    {
        newfg[i].fvalue = Ffunction(old,i,imax,jmax,dt,dx,dy,gamma);
        newfg[i].gvalue = Gfunction(old,i,imax,jmax,dt,dx,dy,gamma); 
        
        new[i].u = newfg[i].fvalue -
        dt *
        first_d(old[i+1].p,old[i].p,dx);

        new[i].v = newfg[i].gvalue -
        dt * 
        first_d(old[i+1].p,old[i].p,dy);
    }
    new_values passback;
    passback.field = new;
    free(new);
    passback.fg = newfg;
    free(newfg);
    return passback;
}

