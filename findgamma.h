double max(double a, double b){
    double max   = a;
    if(max<b)
        max     = b;
    return max;
}

double findgamma(cell* field, int imax, int jmax, double dt, double dx, double dy){
    cell maxcell = max_field(field, imax, jmax);
    double gamma = max(maxcell.u*dt/dx,maxcell.v*dt/dy);
    return gamma;
}