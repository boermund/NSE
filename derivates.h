#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
p:plus
m:minus
i: auf ite Variable bezogen
j: auf jte Variable bezogen
*/

/* bei den gleichen ableitungen immer x mit y und i mit j ersetzen*/

// first derivation (forward) for pressure

float first_d(float xpi ,float x ,float dx){
    return (xpi - x)/dx; 
     
}
// second derivation 
float secondx_d(float xpi ,float x ,float xmi,float dx){
    return (xpi-2*x + xmi)/pow(dx,2);   // hier nochmal wegen potenzen schauen und semikolon 
    }

/*float second_d(float xpi ,float x ,float xmi,float dx){
    return  (xpi-2*x + xmi)/ pow(dx,2);   // hier nochmal wegen potenzen schauen und semikolon 
    }*/

// non linear derivations

//du^2/dx
float non_l_quad(float xpi,float x,float xmi,float dx,float gamma){
    return 1/dx * ( pow(((x+xpi)/2),2) - pow(((xmi+x)/2),2) ) 
    + gamma * 1/dx * ( ((abs(x + xpi))/2) * ((x-xpi)/2)- ((abs(xmi + x))/2) * ((xmi-x)/2) );

}

// dv^2/dy - noch nicht richtig

/*
float non_l_quad(ypj, y, ymj, dy, gamma){
    return 1/dy * ( (((y+ypj)/2)**2) - (((ymj+y)/2)**2) ) 
    + gamma * 1/dx * ( ((abs(y + ypj))/2) * ((y-ypj)/2)- ((abs(ymj + y))/2) * ((ymj-y)/2) )

}*/

// d(uv)/dx
float non_uvx(float xpj,float x,float xmi,float xmipj,float dx,float ypi,float y,float ymi,float gamma){
    return 1/dx * ( ( ((x+xpj)/2) * ((y+ypi)/2) )  - ( ((xmi + xmipj)/2) * ((ymi+y)/2) ) ) +
    gamma * 1/dx * (  ((abs(x + xpj))/2) * ((y-ypi)/2) - ((abs(xmi + xmipj))/2) * ((ymi-y)/2) );

}

// d(uv)/dy

float non_uvy(float ypi,float y,float ymj,float ypimj,float dy,float xpj,float x,float xmj,float gamma){
    return 1/dy * ( ( ((y+ypi)/2) * ((x+xpj)/2) )  - ( ((ymj + ypimj)/2) * ((xmj+x)/2) ) ) +
    gamma * 1/dy * (  ((abs(y + ypi))/2) * ((x-xpj)/2) - ((abs(ymj + ypimj))/2) * ((xmj-x)/2) );

}

float testfunc_u(float x,float y){
    return cos(x)*sin(y);
}

float testfunc_v(float x, float y){
    return pow(x,2)+pow(y,2);
}