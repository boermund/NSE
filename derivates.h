#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
file for the different derivates as funcion
 return an double

p: plus
m: minus
i: consider i
j: consider j

If ther is no dx, x stands for u or v

derivats of the same structure are only written for one direction 
*/

// first derivation (forward) for pressure

double first_d(double xpi ,double x ,double dx){
    return (xpi - x)/dx; 
     
}
// second derivation 
double secondx_d(double xpi ,double x ,double xmi,double dx){
    return (xpi-2*x + xmi)/pow(dx,2);   // hier nochmal wegen potenzen schauen und semikolon 
    }

// non linear derivations

//du^2/dx
double non_l_quad(double xpi,double x,double xmi,double dx,double gamma){
    return 1/dx * ( pow(((x+xpi)/2),2) - pow(((xmi+x)/2),2) ) 
    + gamma * 1/dx * ( ((fabs(x + xpi))/2) * ((x-xpi)/2)- ((fabs(xmi + x))/2) * ((xmi-x)/2) );

}

// d(uv)/dx
double non_uvx(double xpj,double x,double xmi,double xmipj,double dx,double ypi,double y,double ymi,double gamma){
    return 1/dx * ( ( ((x+xpj)/2) * ((y+ypi)/2) )  - ( ((xmi + xmipj)/2) * ((ymi+y)/2) ) ) +
    gamma * 1/dx * (  ((fabs(x + xpj))/2) * ((y-ypi)/2) - ((fabs(xmi + xmipj))/2) * ((ymi-y)/2) );
}

// d(uv)/dy
double non_uvy(double ypi,double y,double ymj,double ypimj,double dy,double xpj,double x,double xmj,double gamma){
    return 1/dy * ( ( ((y+ypi)/2) * ((x+xpj)/2) )  - ( ((ymj + ypimj)/2) * ((xmj+x)/2) ) ) +
    gamma * 1/dy * (  ((fabs(y + ypi))/2) * ((x-xpj)/2) - ((fabs(ymj + ypimj))/2) * ((xmj-x)/2) );

}
