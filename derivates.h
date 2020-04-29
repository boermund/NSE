#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
file for the different derivates as funcion
 return an float

p: plus
m: minus
i: consider i
j: consider j

If ther is no dx, x stands for u or v

derivats of the same structure are only written for one direction 
*/

// first derivation (forward) for pressure

float first_d(float xpi ,float x ,float dx){
    return (xpi - x)/dx; 
     
}
// second derivation 
float secondx_d(float xpi ,float x ,float xmi,float dx){
    return (xpi-2*x + xmi)/pow(dx,2);   // hier nochmal wegen potenzen schauen und semikolon 
    }

// non linear derivations

//du^2/dx
float non_l_quad(float xpi,float x,float xmi,float dx,float gamma){
    return 1/dx * ( pow(((x+xpi)/2),2) - pow(((xmi+x)/2),2) ) 
    + gamma * 1/dx * ( ((fabs(x + xpi))/2) * ((x-xpi)/2)- ((fabs(xmi + x))/2) * ((xmi-x)/2) );

}

// d(uv)/dx
float non_uvx(float xpj,float x,float xmi,float xmipj,float dx,float ypi,float y,float ymi,float gamma){
    return 1/dx * ( ( ((x+xpj)/2) * ((y+ypi)/2) )  - ( ((xmi + xmipj)/2) * ((ymi+y)/2) ) ) +
    gamma * 1/dx * (  ((fabs(x + xpj))/2) * ((y-ypi)/2) - ((fabs(xmi + xmipj))/2) * ((ymi-y)/2) );
}

// d(uv)/dy
float non_uvy(float ypi,float y,float ymj,float ypimj,float dy,float xpj,float x,float xmj,float gamma){
    return 1/dy * ( ( ((y+ypi)/2) * ((x+xpj)/2) )  - ( ((ymj + ypimj)/2) * ((xmj+x)/2) ) ) +
    gamma * 1/dy * (  ((fabs(y + ypi))/2) * ((x-xpj)/2) - ((fabs(ymj + ypimj))/2) * ((xmj-x)/2) );

}
