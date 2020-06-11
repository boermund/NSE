double Ffunction(cell* field,int z,int imax2, int jmax2, double dt, double dx, double dy,double gamma){ //Calculate the values for F
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
    - non_uvx(field[z+imax2].u,field[z].u,field[z-1].u,field[z-1+imax2].u,dx,field[z+1].v,field[z].v,field[z-1].v,gamma)
    + GY);
    return newG;
}

cell *newspeed(cell*old,f_and_g *newfg,int imax2,int jmax2,double dx,double dy,double dt, double gamma){
    //Calculte the new values for speed
    
for(int i = 0; i < imax2 * jmax2 ;i++)
    {
        if((i < (imax2 * (jmax2 - 1))) && ((i+1) % imax2 != 0)){
        old[i].u = newfg[i].fvalue -
        dt *
        first_d(old[i+1].p,old[i].p,dx);
        old[i].v = newfg[i].gvalue -
        dt * 
        first_d(old[i+imax2].p,old[i].p,dy);
        }
        else{
            if(i < imax2)
                old[i].v=0;
            if((i+1) % imax2 ==0)
                old[i].u=0;
        }
    }
    return old;
}

f_and_g *new_f_and_g(cell*old,f_and_g* newfg,int imax2,int jmax2,double dx,double dy,double dt, double gamma){
    for(int i = 0; i < imax2 * jmax2 ;i++)
    {
        if((i > 1 * imax2 && (i < imax2 * (jmax2 - 1))) && ((i % imax2 != 0) && (((i+2) % imax2 != 0) && ((i+1) % imax2 != 0)))){
            newfg[i].fvalue = Ffunction(old,i,imax2,jmax2,dt,dx,dy,gamma); //Derivations need values that are next to the one you want
        }
        else{
            if((i+1)%imax2 != 0) //Exclude those Values
                newfg[i].fvalue = old[i].u;
            else
               newfg[i].fvalue = old[i-1].u;//Does not have a real meaning. Is set to the same value 
             
        }
        if((i > 2 * imax2 && (i < imax2 * (jmax2-1))) && (( i % imax2 != 0) && ((i+1) % imax2 != 0))) //Same as above
        {
            newfg[i].gvalue = Gfunction(old,i,imax2,jmax2,dt,dx,dy,gamma); 
        }
        else
        {
            if(i>=imax2)
                newfg[i].gvalue = old[i].v;
            else 
                newfg[i].gvalue = newfg[i+imax2].gvalue;
        }
        
        
    }

    return newfg;
}
