#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// fpr die Interationen von p werde ich meine eigene Struct entwerfen

// p_it+1 function 
//returns a float
float p_it(float xpi, float x, float xmi, float xpj, float xmimj, float RHS, float dx, float dy, float omega){

printf("xpi: %.6f, x:  %.6f, xmi: %.6f,xpj: %.6f,xmimj %.6f, RHS %.6f, dx; %.6f, dy: %.6f, omega: %.6f\n", xpi,  x, xmi,  xpj, xmimj, RHS,  dx, dy,  omega);

return (1 - omega)*x + omega * (1/ (2*( 1/pow(dx,2) + 1/pow(dy,2)) ) ) * 
        ( (xpi + xmi)/pow(dx,2)  +  (xpj + xmimj)/pow(dy,2)  -  RHS);
}

// p_it+1 struct
// returns a struct with all p_it+1 values

presit * pres_it(presit * pres, rhs_struct * RHS, float dx, float dy, float omega, float (*p_it)(float,float, float, float,float, float, float,float, float), int imax2, int jmax2){


// fill boundary cells
// imax2: values + boundary values 
float pbi[imax2], pbj[jmax2];

    // new i boundaries left
for(int i = 0; i < imax2; i++){
        pres[i].p = pres[imax2 + i].p;
        pbi[i] = pres[(jmax2-2)*imax2 + i].p;
    }

   //printf("\n") ;

// new j boundaries up
for(int j = 0; j < jmax2; j++ ){
        pres[imax2*j].p = pres[j*imax2 + 1].p;
        pbj[j] = pres[imax2 * j + (imax2-2)].p;
    }

for(int j = 0; j < jmax2; j++){
    for(int i = 0; i < imax2; i++){
           printf("%.6f\t", pres[j*imax2 + i].p);
        }
    printf("\n");
    } 

// calculate pressura values p_it + 1 
    for(int j = 1; j < jmax2 - 1; j++){
    for(int i = 1; i < imax2 - 1; i++){
            pres[j*imax2 + i].p = (*p_it)(pres[j*imax2 + i + 1].p, pres[j*imax2 + i ].p, pres[j*imax2 + i -1].p, pres[(j+1)*imax2 + i].p, pres[(j-1)*imax2 + i - 1].p, RHS[imax2 * j + i].rhs, dx, dy, omega);                     
        }
    } 

    // new i boundaries right 
for(int i = 0; i < imax2; i++){
      pres[(jmax2-1)*imax2 + i].p = pbi[i];
    }

   //printf("\n") ;

// new j boundaries down
for(int j = 0; j < jmax2; j++ ){
       pres[imax2 * j + (imax2-1)].p = pbj[j];
    }


    return pres;}

// RHS
//returns a struct
rhs_struct *rhs_func( rhs_struct * RHS, cell_fg * fg, float dx, float dy, float dt, int imax2, int jmax2){

    /*for(int j = 0; j < jmax2; j++){
    for(int i = 0; i < imax2; i++){
        printf(" f: %.6f\t",fg[imax2*j + i].f);
        printf(" g: %.6f\t \n",fg[imax2*j + i].g);
    }
    }*/

    /*for(int j = 0; j < jmax2; j++){
    for(int i = 0; i < imax2; i++){
        printf(" %.6f\t",RHS[imax2*j + i].rhs);
        
    }
    printf("\n");
    }*/

    //printf("imax2: %d and jmax2: %d\n", imax2, jmax2);
    //printf(" %.6f %.6f %.6f\n", dx,dy,dt);

    for(int j = 1; j < jmax2-1; j++){
    for(int i = 1; i < imax2-1; i++){

        /*if(i == 0 || i == (imax2 -1) || j == 0 || j == jmax2-1 )
        {
            continue;
        }*/
       /* if(i == 0 || j == 0){
            if( i == 0 && j == 0){
            RHS[imax * j +i].rhs = 1/dt * ( ( fg[imax * j + i].f - f1)/dx + (fg[imax * j + i].g - g1)/dy);
            }
            else if (i == 0 && j != 0)
            {
                RHS[imax * j +i].rhs = 1/dt * ( ( fg[imax * j + i].f - f1)/dx + (fg[imax * j + i].g - fg[imax * (j - 1) + i].g ) /dy);
            }
           else{ // wenn was nicht funktionieren hier mal  else if(j == 0 && i != 0) einfügen
                 RHS[imax * j +i].rhs = 1/dt * ( ( fg[imax * j + i].f - fg[imax * j + i-1].f)/dx + (fg[imax * j + i].g - g1)/dy);
                 }
            }*/
        //else{
        RHS[imax2 * j +i].rhs = 1/dt * ((fg[imax2 * j + i].f - fg[imax2 * j + i-1].f) / dx + (fg[imax2 * j + i].g - fg[imax2 * (j - 1) + i].g) / dy);
          //}
        }
    }
    
    // fill the boundaries
    for(int i = 0; i < imax2; i++){
            RHS[i].rhs = RHS[imax2 + i].rhs;
            RHS[(jmax2-1)*imax2 + i].rhs = RHS[(jmax2-2)*imax2 + i].rhs;
        }

    for(int j = 0; j < jmax2; j++ ){
        RHS[imax2*j].rhs = RHS[j*imax2 + 1].rhs;
        RHS[imax2 * j + (imax2-1)].rhs = RHS[imax2 * j + (imax2-2)].rhs;
    }
    return RHS; 
}

// residuum

//function

float res_func(float ppi, float p, float pmi, float ppj, float pmj, float dx, float dy,  float rhs ){
    return (ppi - 2* p + pmi)/pow(dx,2) + (ppj - 2* p + pmj)/pow(dy,2) - rhs;
}

// returns a struct

res *res_struct(res * res_str, rhs_struct * RHS, presit * pres, float (*res_func)(float,float, float, float,float, float, float,float), float dx, float dy, int imax2, int jmax2){

for(int j = 1; j < jmax2-1; j++){
    for(int i = 1; i < imax2-1; i++){
        res_str[(j-1)*(imax2-2) + (i-1)].r = (*res_func)(pres[j*imax2 + i + 1].p, pres[j*imax2 + i ].p, pres[j*imax2 + i -1].p, pres[(j+1)*imax2 + i].p, pres[(j-1)*imax2 + i].p, dx, dy, RHS[imax2 * j + i].rhs);
    }
    }
return res_str;
}

// abs(residuum) as L_2 norm
// returns a float
float abs_res(res * resi, int imax, int jmax){

    float residuum = 0;

    for(int j = 0; j < jmax; j++){
        for(int i = 0; i < imax; i++){
        residuum += pow(resi[imax*j+i].r,2);
        }
    }

    residuum = sqrt(residuum / (imax * jmax));

    return residuum; 

// abs(pres_it = 0) as L_2 norm
}

float abs_pres(presit * pres, int imax2, int jmax2){

    float abs_pres = 0;

    for(int j = 1; j < jmax2-1; j++){
        for(int i = 1; i < imax2-1; i++){
        abs_pres += pow(pres[imax2*j+i].p,2);
        }
    }

    abs_pres = sqrt(abs_pres / ((imax2-2) * (jmax2-2)));

    return abs_pres; 
}


// put everything for one it-step togehter:

cell *new_p(cell * newp, rhs_struct *RHS, res * res_str,
float (*abs_pres)(presit*, int,int),  float (*p_it)(float, float, float, float, float, float, float, float, float), 
presit * (*pres_it)(presit *, rhs_struct *, float, float, float, float (*p_it)(float,float, float, float,float, float, float,float, float), int, int),
float (*res_func)(float, float, float, float, float, float, float,  float),
res * (*res_struct)(res * , rhs_struct *, presit *, float (*res_func)(float,float, float, float,float, float, float,float), float, float, int, int),
float (*abs_res)(res *, int, int),
float dx, float dy, float omega,  float epsilon, int imax2, int jmax2){

    presit * pres; 
    pres = calloc((imax2)*(jmax2),sizeof(presit)); 

    // get p_it from the big struct
    for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            pres[imax2*j+i].p = newp[imax2*j+i].p; 
            printf(" %.6f\t", pres[imax2*j+i].p);
        }
        printf("\n");
        }
    
    printf("\nRHS\n");
    for(int j = 0; j < JMAX + 2; j++){
    for(int i = 0; i < IMAX + 2; i++){
        
        printf(" %.6f\t",RHS[(IMAX+2)*j +i].rhs);
    }
    printf("\n");
}

printf("\n\n");

//calculate abs(p_it)
    float abs_pres0 = 0;
    abs_pres0 = abs_pres(pres, imax2, jmax2);
    printf("abspres0: %.6f", abs_pres0);

// calculate the new pressure p_it + 1

float absres  = 1000;

while(absres >= epsilon * abs_pres0){
    pres = pres_it(pres,  RHS, dx,  dy,  omega, p_it, imax2, jmax2);

    for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){ 
            printf(" %.6f\t", pres[imax2*j+i].p);
        }
        printf("\n");
        }
    
// calculate the residuum
    res_str = res_struct(res_str, RHS, pres, res_func, dx, dy, imax2, jmax2);
    for(int j = 0; j < jmax2-2; j++){
        for(int i = 0; i < imax2-2; i++){ 
            printf(" %.6f\t", res_str[(imax2-2)*j+i].r);
        }
        printf("\n");
        }

// abs of residuum (evtl noch in die struct funktion verpacken bzw. die struchtfunktion in die)

        absres = abs_res(res_str, imax2-2, jmax2-2);
        printf(" absres: %.6f", absres);

}

for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
           newp[imax2*j+i].p =pres[imax2*j+i].p; 
            printf(" %.6f\t", newp[imax2*j+i].p);
        }
        printf("\n");
        }



// überprüfen ob while schleife funktionier 
        // hier muss kein abs gewählt werden, das epsilon wahrscheinlich kleiner 1 gewählt wird 
        // ansonsten hier auch noch Residuum
    
    // p_werte wieder in das struct einordnen
    // return des dreiwertigen structs
return newp;
}

// test elliptische DGL

// statt rhs f und g einfach wieder p einsetzen und mal 2 und dann pij it + 1 ausrechnen lassen (Gleichung umstellen)
// druckwerte mit analytischen werden des ergebnissees der gleichung vergleichen
// startwert aber nicht bei null durchführen wenn möglichen, denn dann wird alles null
// anfansvetor schaffen der nahe an den alten liegt !!!





