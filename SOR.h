#include <stdio.h>
#include <math.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////

//presure

// p_it+1 function to calculate the new pressures 
//returns a double
double p_it(double xpi, double x, double xmi, double xpj, double xmj, double RHS, double dx, double dy, double omega){
    //printf("\nxpi: %.6f,  x: %.6f,  xmi: %.6f,  xpj: %.6f,  xmj: %.6f,  RHS: %.6f,  dx: %.6f,  dy: %.6f,  omega: %.6f\n", xpi,  x,  xmi,  xpj,  xmj,  RHS,  dx,  dy,  omega);
    return (1 - omega)*x + omega * (1/ (2*( 1/pow(dx,2) + 1/pow(dy,2)) ) ) * 
            ( (xpi + xmi)/pow(dx,2)  +  (xpj + xmj)/pow(dy,2)  -  RHS);
    }

// p_it+1 struct
// returns a struct with all p_it+1 values
presit * pres_it(presit * pres, rhs_struct * RHS, double dx, double dy, double omega, int imax2, int jmax2){
    // fill boundary cells 
    // we first have to fill the left and upper boundary 
    // than claculate the pressure 
    // and  at last we have to fill the right and under boundary

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

    // print the pressure with bounderaies left and at the top
    /*
    printf("\npressur, boundaries left and at the top:\n");
    for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            printf("%.6f\t", pres[j*imax2 + i].p);
            }
        printf("\n");
        } */

    // calculate pressura values p_it + 1 
        for(int j = 1; j < jmax2 - 1; j++){
        for(int i = 1; i < imax2 - 1; i++){
                pres[j*imax2 + i].p = p_it(pres[j*imax2 + i + 1].p, pres[j*imax2 + i ].p, pres[j*imax2 + i -1].p, pres[(j+1)*imax2 + i].p, pres[(j-1)*imax2 + i].p, RHS[imax2 * j + i].rhs, dx, dy, omega);                     
            }
        } 

    // print the new calculatet pressure with bounderaies left and at the top
    /*
    printf("\nnew pressur, boundaries left and at the top:\n");
    for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            printf("%.6f\t", pres[j*imax2 + i].p);
            }
        printf("\n");
        } */


    // new i boundaries below
    for(int i = 0; i < imax2; i++){
        pres[(jmax2-1)*imax2 + i].p = pbi[i];
        }

    // new j boundaries right
    for(int j = 0; j < jmax2; j++ ){
        pres[imax2 * j + (imax2-1)].p = pbj[j];
        }


    // print the new calculatet pressure with new bounderaies at all sides
    /*
    printf("\nnew pressur, new boundaries:\n");
    for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            printf("%.6f\t", pres[j*imax2 + i].p);
            }
        printf("\n");
        } */

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

    // look that we get the right f and g values
    /*
    printf("\nf and g values:\n");
    for(int j = 0; j < jmax2; j++){
    for(int i = 0; i < imax2; i++){
        printf(" f: %.6f\t",fg[imax2*j + i].fvalue);
        printf(" g: %.6f\t \n",fg[imax2*j + i].gvalue);
    }
    }
    */

    // fill the inner values of the RHS
    for(int j = 1; j < jmax2-1; j++){
    for(int i = 1; i < imax2-1; i++){

            RHS[imax2 * j +i].rhs = 1/dt * ((fg[imax2 * j + i].fvalue - fg[imax2 * j + i-1].fvalue) / dx + (fg[imax2 * j + i].gvalue - fg[imax2 * (j - 1) + i].gvalue) / dy);
        //}
        }
    }

return RHS;
}

////////////////////////////////////////////////////////////
// residuum

//function to caltculate the values of the residuum
double res_func(double ppi, double p, double pmi, double ppj, double pmj, double dx, double dy,  double rhs ){
    return (ppi - 2* p + pmi)/pow(dx,2) + (ppj - 2* p + pmj)/pow(dy,2) - rhs;
}

// returns a struct for the ressiduum 
res *res_struct(res * res_str, rhs_struct * RHS, presit * pres, double dx, double dy, int imax2, int jmax2){

for(int j = 1; j < jmax2-1; j++){
    for(int i = 1; i < imax2-1; i++){
        res_str[(j-1)*(imax2-2) + (i-1)].r = res_func(pres[j*imax2 + i + 1].p, pres[j*imax2 + i ].p, pres[j*imax2 + i -1].p, pres[(j+1)*imax2 + i].p, pres[(j-1)*imax2 + i].p, dx, dy, RHS[imax2 * j + i].rhs);
    }
    }
return res_str;
}

// abs(residuum) as L_2 norm
// returns a double
double abs_res(res * resi, int imax2, int jmax2){
    
    double residuum = 0;

    /*printf("\nresiduum struct\n");
    for(int j = 0; j < JMAX; j++){
        for(int i = 0; i < IMAX; i++){
            printf("%.6f\t",resi[(imax2-2)*j+i].r);
    }
    printf("\n");
    }
    */

    for(int j = 0; j < jmax2-2; j++){
        for(int i = 0; i < imax2-2; i++){
        residuum += pow(resi[(imax2-2)*j+i].r,2.0);
        //printf("res: %.6f und res.r: %.6f\n",residuum, resi[(imax2-2)*j+i].r);
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
    res_str = calloc((imax2 - 2)*(jmax2 - 2), sizeof(res)); 

    // get p_it from the big struct
    for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){
            pres[imax2*j+i].p = newp[imax2*j+i].p; 
        }
        }

    // print the new pressure (it = 0)
    
    /*
    printf("\nDruckwerte0-SOR:\n");
    for(int j = 0; j < jmax2; j++){
        for(int i = 0; i < imax2; i++){ 
            printf(" %.6f\t", pres[imax2*j+i].p);
        }
        printf("\n");
        }
    */

    // look that I get the right RHS
    /*
        printf("\nRHS-SOR\n");
        for(int j = 0; j < JMAX + 2; j++){
        for(int i = 0; i < IMAX + 2; i++){
            printf(" %.6f\t",RHS[(IMAX+2)*j +i].rhs);
        }
        printf("\n");
    }
    */

    //calculate abs(p_it)
    // as I understand I have only to calculate only the abs(presure) once: for p_(it = 0)
    // in this case I get the problem that if I choose pressur p=0 for all values of the strcuct the abs is zero and the loop will never end
    double abs_pres0 = 0;
    abs_pres0 = abs_pres(pres, imax2, jmax2);
    printf("\nabspres0: %.6f\n", abs_pres0);

    //verry high ressidumm to start the while loop
    res_str = res_struct(res_str, RHS, pres, dx, dy, imax2, jmax2);
    double absres  =  abs_res(res_str, imax2, jmax2); 

    // chose the maximum of small or abs_pres0 to avoid that the loop never ends (abs_pres0 = 0)
    double small = 0.001;

    if(small>abs_pres0){
        abs_pres0 = small;
    }

    // print the abs_pres0
    //printf("abs_pres0: %.6f", abs_pres0);
    
    //whileloop
    double res_i = INFINITY ;

    // to test wether the SOR works for the first two iterations
    int i = 0;
    //while(((absres < res_i || (i<10)))){

    do{
        
    

        // calculate the new pessure
        pres = pres_it(pres,  RHS, dx,  dy,  omega,  imax2, jmax2);


        // print it
        /*
        printf("\npres:\n");
        for(int j = 0; j < jmax2; j++){
            for(int i = 0; i < imax2; i++){ 
                printf(" %.6f\t", pres[imax2*j+i].p);
            }
            printf("\n");
            }
        */

    // calculate the residuum
        res_str = res_struct(res_str, RHS, pres,  dx, dy, imax2, jmax2);

    // print the residuum
    /*
    printf("\nres:\n");
        for(int j = 0; j < jmax2-2; j++){
            for(int i = 0; i < imax2-2; i++){ 
                printf(" %.6f\t", res_str[(imax2-2)*j+i].r);
            }
            printf("\n");
            }
    */
    
        res_i = absres;
        // abs of residuum 
        absres = abs_res(res_str, imax2, jmax2);
        //if(i%100==0){
        if(i%100==0){
        printf("abs_pres0: %.10f", abs_pres0);
        printf(" \nabsres: %.10f\n", absres);
        printf("%d\n", i);
        }
        //}
        //for the DGL test: fill RHS with the new pressure values multiplcated with -2
        /* for(int j = 0; j < jmax2; j++){
            for(int i = 0; i < imax2; i++){ 
                RHS[j*imax2 + i].rhs = -2 * pres[imax2*j+i].p;
            }
            }
        */
        // print RHS   
         /*   
        printf("\nRHS\n");
        for(int j = 0; j < jmax2; j++){
                for(int i = 0; i < imax2; i++){
                
                    printf(" %.6f\t", RHS[imax2*j+i].rhs);
                }
                printf("\n");
                }
        */
        
        //test the first two iterations
        i+=1;
        
        // end of while loop

    }while((absres > epsilon * abs_pres0));

    // put the new pressure values into the cell
    for(int j = 0; j < jmax2; j++){
            for(int i = 0; i < imax2; i++){
            newp[imax2*j+i].p = pres[imax2*j+i].p; 
            }
            }

    return newp;
}






