float max(float a, float b){
    float max   = a;
    if(max<b)
        max     = b;
    return max;
}

float findgamma(cell* field, int imax, int jmax, float dt, float dx, float dy){
    cell maxcell = max_field(field, imax, jmax);
    float gamma = max(maxcell.u*dt/dx,maxcell.v*dt/dy);
    return gamma;
}