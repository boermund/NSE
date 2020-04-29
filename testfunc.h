#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* testfunctions to check the derivates. The functions give the analytic derivations of the function u = cos(x)sin(y)
 and later v = x^2 + y^2
*/

//u = cos(x)sin(y)
float testfunc_u(float x,float y){
    return cos(x)*sin(y);
}

//v = x^2 + y^2
float testfunc_v(float x, float y){
    return pow(x,2)+pow(y,2);
}

//derivations

//first derivation /dx
float test_der_u_x(float x, float y){
    return -sin(x)*sin(y);
}

//first derivation /dy
float test_der_u_y(float x, float y){
    return cos(x)*cos(y);
}



//sec derivation /dx
float test_sec_der_x(float x, float y){
    return -cos(x)*sin(y);
}

//sec derivation /dy
float test_sec_der_y(float x, float y){
    return cos(x)*(-sin(y));
}



// non linear derivation u^2  /dx
float test_nl2_der_x(float x, float y){
    return -2.0*cos(x)*(sin(x))*pow(sin(y),2.0);
}

// non linear derivation u^2  /dy
float test_nl2_der_y(float x, float y){
    return 2.0*cos(y)*(sin(y))*pow(cos(x),2.0);
    }



// non linear derivation u*v /dx
float testfunc_uv(float x, float y, float (*u)(float,float), float (*v)(float,float)){
    return (*u)(x,y) * (*v)(x,y);
}

// non linear derivation u*v /dy
float testfunc_uv_der_x(float x, float y, float (*u)(float,float), float (*v)(float,float)){
    return -sin(x)*sin(y)*(*v)(x,y)+(*u)(x,y)*2*x;
}

float testfunc_uv_der_y(float x, float y, float (*u)(float,float), float (*v)(float,float)){
    return cos(x)*cos(y)*(*v)(x,y)+(*u)(x,y)*2*y;
}