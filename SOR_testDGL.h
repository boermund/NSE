// SOR for the test-DGL

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

    // calculate pressura values p_it + 1 
    // leave the boundaries constant (analytical solution)
        for(int j = 1; j < jmax2 - 1; j++){
        for(int i = 1; i < imax2 - 1; i++){
                pres[j*imax2 + i].p = p_it(pres[j*imax2 + i + 1].p, pres[j*imax2 + i ].p, pres[j*imax2 + i -1].p, pres[(j+1)*imax2 + i].p, pres[(j-1)*imax2 + i].p, RHS[imax2 * j + i].rhs, dx, dy, omega);                     
            }
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
    for(int j = 1; j < jmax2-1; j++){
    for(int i = 1; i < imax2-1; i++){

            RHS[imax2 * j +i].rhs = 1/dt * ((fg[imax2 * j + i].fvalue - fg[imax2 * j + i-1].fvalue) / dx + (fg[imax2 * j + i].gvalue - fg[imax2 * (j - 1) + i].gvalue) / dy);
        }
    }

return RHS;
}

////////////////////////////////////////////////////////////
// residuum

//function to caltculate the values of the residuum
double res_func(double ppi, double p, double pmi, double ppj, double pmj, double dx, double dy,  double rhs ){
    return (ppi - 2.0* p + pmi)/pow(dx,2.0) + (ppj - 2.0* p + pmj)/pow(dy,2) - rhs;
}

// returns a struct for the ressiduum 
res *res_struct(res * res_str, rhs_struct * RHS2, presit * pres, double dx, double dy, int imax2, int jmax2){

//printf("\nresstruct\n");
for(int j = 1; j < jmax2-1; j++){
    for(int i = 1; i < imax2-1; i++){
        res_str[(j-1)*(imax2-2) + (i-1)].r = res_func(pres[j*imax2 + i + 1].p, pres[j*imax2 + i ].p, pres[j*imax2 + i - 1].p, pres[(j+1)*imax2 + i].p, pres[(j-1)*imax2 + i].p, dx, dy, RHS2[imax2 * j + i].rhs);
    }
    }
return res_str;
}

// abs(residuum) as L_2 norm
// returns a double
double abs_res(res * resi, int imax2, int jmax2){
    
    double residuum = 0;
    for(int j = 0; j < jmax2-2; j++){
        for(int i = 0; i < imax2-2; i++){
        residuum += pow(resi[(imax2-2)*j+i].r,2.0);
        }
    }
    residuum = sqrt(residuum / ((imax2-2) * (jmax2-2)));
    return residuum; 
}

////////////////////////////////////////////////////////////////////////

//SOR
// put everything for one it-step togehter:

cell *new_p(cell * newp, rhs_struct *RHS, double dx, double dy, double omega,  double epsilon, int imax2, int jmax2, rhs_struct *RHS2){

    // define the pressure in wich I can put the values of the bigger cell struct
    presit * pres; 
    pres = calloc((imax2)*(jmax2),sizeof(presit)); 

    res * res_str; 
    res_str = calloc((imax2 - 2)*(jmax2 - 2), sizeof(res)); 

    // get p_it from the big struct
    for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            pres[imax2*j+i].p = newp[imax2*j+i].p; 
        }
        }

    double abs_pres0 = 0;
    abs_pres0 = abs_pres(pres, imax2, jmax2);
    printf("\nabspres0: %.6f\n", abs_pres0);

    // choose a barrier for the end of the do-loop
    double barrier;
        barrier = 0; 

    if(abs_pres0<0.000001 || epsilon*abs_pres0 < 0.0000001){
        barrier = abs_pres0 + epsilon;
    }
    else
    {
        barrier = epsilon * abs_pres0;
    }

    //calculate the first residuum 
    res_str = res_struct(res_str, RHS2, pres, dx, dy, imax2, jmax2);
    double absres  =  abs_res(res_str, imax2, jmax2); 

    // to test wether the SOR works for the first iterations
    // or number of iterations
    int i = 0;
   
    do{

        // calculate the new pressure
        pres = pres_it(pres,  RHS, dx,  dy,  omega,  imax2, jmax2);

        //for the DGL test: fill RHS with the new pressure values multiplcated with -2
        for(int j = 1; j < jmax2-1; j++){
            for(int i = 1; i < imax2-1; i++){ 
                RHS[j*imax2 + i].rhs = -2 * pres[imax2*j+i].p;
            }
            }

        // calculate the residuum // to take the actuall RHS you have to change RHS2 to RHS
        res_str = res_struct(res_str, RHS2, pres,  dx, dy, imax2, jmax2);

        // abs of residuum 
        absres = abs_res(res_str, imax2, jmax2);
        printf(" \nabsres: %.6f\n", absres);
        
        //test the first two iterations
        i+=1;
        printf("%d\n", i);
        // end of while loop
    }while(absres > barrier);

    //}while(i<10000);

 printf("abs_pres0: %.14f", abs_pres0);
 printf(" \nabsres: %.6f\n", absres);
    // put the new pressure values into the cell
    for(int j = 0; j < jmax2; j++){
            for(int i = 0; i < imax2; i++){
            newp[imax2*j+i].p = pres[imax2*j+i].p; 
            }
            }

    return newp;
}






