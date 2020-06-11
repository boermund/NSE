double max(double a, double b){ //Find the maximum of two values
    double max   = a;
    if(max<b)
        max     = b;
    return max;
}

double findgamma(cell* field, int imax2, int jmax2, double dt, double dx, double dy){ //Calculate the new value for gamma
    cell maxcell = max_field(field, imax2, jmax2);
    double gamma = max(maxcell.u*dt/dx,maxcell.v*dt/dy);
    return gamma;
}