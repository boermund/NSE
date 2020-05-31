#include <stdio.h>
#include <math.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////

//presure

// p_it+1 function to calculate the new pressures 
//returns a double
double p_it(double xpi, double x, double xmi, double xpj, double xmj, double RHS, double dx, double dy, double omega){
    return (1 - omega)*x + omega * (1/ (2*( 1/pow(dx,2) + 1/pow(dy,2)) ) ) * 
            ( (xpi + xmi)/pow(dx,2)  +  (xpj + xmj)/pow(dy,2)  -  RHS);
    }

// p_it+1 struct
// returns a struct with all p_it+1 values
presit * pres_it(presit * pres, rhs_struct * RHS, double dx, double dy, double omega, int imax2, int jmax2){

    // define a array to the values for the right and under boundary
    double pbi[imax2], pbj[jmax2];

    // new i boundaries left and saving of the rigth boundaries
    // the left boundaries have the same values like the one right next to them
    for(int i = 0; i < imax2; i++){
            pres[i].p = pres[imax2 + i].p;
            pbi[i] = pres[(jmax2-2)*imax2 + i].p;
        }

    // new j upper boundaries and saving the under one
    // the upper boundaries have the same values like the one under them
    for(int j = 0; j < jmax2; j++ ){
            pres[imax2*j].p = pres[j*imax2 + 1].p;
            pbj[j] = pres[imax2 * j + (imax2-2)].p;
        }

    // calculate pressura values p_it + 1 
        for(int j = 1; j < jmax2 - 1; j++){
        for(int i = 1; i < imax2 - 1; i++){
                pres[j*imax2 + i].p = p_it(pres[j*imax2 + i + 1].p, pres[j*imax2 + i ].p, pres[j*imax2 + i -1].p, pres[(j+1)*imax2 + i].p, pres[(j-1)*imax2 + i].p, RHS[imax2 * j + i].rhs, dx, dy, omega);                     
            }
        } 

    // new i boundaries below
    for(int i = 0; i < imax2; i++){
        pres[(jmax2-1)*imax2 + i].p = pbi[i];
        }

    // new j boundaries right
    for(int j = 0; j < jmax2; j++ ){
        pres[imax2 * j + (imax2-1)].p = pbj[j];
        }

    return pres;
}

// abs(pres_it = 0) as L_2 norm
// returns a double
double abs_pres(presit * pres, int imax2, int jmax2){

    double abs_pres = 0;

    for(int j = 1; j < jmax2-1; j++){
        for(int i = 1; i < imax2-1; i++){
        abs_pres += pow(pres[imax2*j+i].p,2);
        }
    }
    abs_pres = sqrt(abs_pres / ((imax2-2) * (jmax2-2)));
    return abs_pres; 
}

////////////////////////////////////////////////////////////////////////////////////////

// RHS
//returns a struct with the values of the RHS of equation (41)
rhs_struct *rhs_func( rhs_struct * RHS, f_and_g * fg, double dx, double dy, double dt, int imax2, int jmax2){

    // fill the inner values of the RHS
    for(int j = 1; j < jmax2; j++){
    for(int i = 1; i < imax2; i++){
            RHS[imax2 * j +i].rhs = ((fg[imax2 * j + i].fvalue - fg[imax2 * j + i-1].fvalue) / dx + (fg[imax2 * j + i].gvalue - fg[imax2 * (j - 1) + i].gvalue) / dy)/dt;
        }
    }

return RHS;
}

////////////////////////////////////////////////////////////
// residuum

//function to caltculate the values of the residuum
double res_func(double ppi, double p, double pmi, double ppj, double pmj, double dx, double dy,  double rhs ){
    return ((ppi - 2* p + pmi)/pow(dx,2) + (ppj - 2* p + pmj)/pow(dy,2) - rhs);
}

// returns a struct for the ressiduum 
res *res_struct(res * res_str, rhs_struct * RHS, presit * pres, double dx, double dy, int imax2, int jmax2){

for(int j = 1; j < jmax2-1; j++){
    for(int i = 1; i < imax2-1; i++){
        res_str[(j)*(imax2) + (i)].r = res_func(pres[j*imax2 + i + 1].p, pres[j*imax2 + i ].p, pres[j*imax2 + i -1].p, pres[(j+1)*imax2 + i].p, pres[(j-1)*imax2 + i].p, dx, dy, RHS[imax2 * j + i].rhs);
        
    }
    //printf("resstr:\t%.2f\t",res_str[1000].r);
    }
return res_str;
}

// abs(residuum) as L_2 norm
// returns a double
double abs_res(res * resi, int imax2, int jmax2){
    
    double residuum = 0;

    for(int j = 0; j < jmax2-2; j++){
        for(int i = 0; i < imax2-2; i++){
        residuum += pow(resi[(imax2)*j+i].r,2);
        }
    }
    residuum = sqrt(residuum / ((imax2-2) * (jmax2-2)));
    return residuum; 
}

////////////////////////////////////////////////////////////////////////

//SOR
// put everything for one it-step togehter:

cell *new_p(cell * newp, rhs_struct *RHS, double dx, double dy, double omega,  double epsilon, int imax2, int jmax2){
    
    // define the pressure in wich I can put the values of the bigger cell struct
    presit * pres; 
    pres = calloc((imax2)*(jmax2),sizeof(presit)); 

    res * res_str; 
    res_str = calloc((imax2)*(jmax2), sizeof(res)); 

    // get p_it from the big struct
    for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            pres[imax2*j+i].p = newp[imax2*j+i].p; 
        }
        }

    //calculate abs(p_it)
    double abs_pres0;
    abs_pres0 = abs_pres(pres, imax2, jmax2);

    // choose a barrier for the end of the do-loop
    double barrier; 

    if(abs_pres0<0.000001 || epsilon*abs_pres0 < 0.0000001){
        barrier = abs_pres0 + epsilon;
    }
    else
    {
        barrier = epsilon * abs_pres0;
    }

    //verry high ressidumm to start the while loop
    res_str = res_struct(res_str, RHS, pres, dx, dy, imax2, jmax2);
    double absres  =  abs_res(res_str, imax2, jmax2); 

    // to test wether the SOR works for the first two iterations
    // or number of iterations
    int i = 0;

    do{
        
        // calculate the new pessure
        pres = pres_it(pres,  RHS, dx,  dy,  omega,  imax2, jmax2);

        // calculate the residuum
        res_str = res_struct(res_str, RHS, pres,  dx, dy, imax2, jmax2);

        // abs of residuum 
        absres = abs_res(res_str, imax2, jmax2);

        
        if(i%100==0){
        printf(" abs_pres0: %.9f, absres: %f \t", barrier, absres);
        printf("%d\n", i);
        }
        //test the first two iterations
        i+=1;
        
        // end of while loop

    }while(absres > barrier);

    //}while(i<10000);

    // put the new pressure values into the cell
    for(int j = 0; j < jmax2; j++){
            for(int i = 0; i < imax2; i++){
            newp[imax2*j+i].p = pres[imax2*j+i].p; 
            }
            }
    free(pres);
    free(res_str);
    return newp;
}






