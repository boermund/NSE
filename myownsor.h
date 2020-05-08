#include <math.h>

float eq_newp(float x,float xmi,float xpi,float xmj, float xpj, int imax, int jmax, float dx,float dy, float rhs)
{
    float newpressure = (1-OMEGA) * x 
                        + OMEGA /
                        (2 *
                        (
                        1/pow( dx , 2 ) + 
                        1/pow( dy , 2 )
                        )
                        ) *
                        (
                        (xpi+xmi)/pow(dx, 2) +
                        (xpj+xmj)/pow(dy, 2) -
                        rhs
                        );  
    //printf("prescalc:%.3f\t%.3f\t%.3f\n",x,rhs,newpressure); 
    return newpressure; 
}

cell * p_it_plus(cell* old,float* rhs, int imax, int jmax, float dx, float  dy){
    //printf("\nneuer druck:\n");
    for(int i=0;i < imax * jmax; i++){
        if(i>imax && i<(jmax*(imax-1))){
            if(i%imax != 0 && (i+1)%imax != 0){
                old[i].p = eq_newp(old[i].p,old[i-1].p,old[i+1].p,old[i+imax].p,old[i-imax].p,imax,jmax,dx,dy,rhs[i]);
                //printf("%.2f\t",rhs[i]);
                //if((i-1)%(imax-2)==0)
                //    printf("\n");
            }
        
        }
    }
    printf("\n");
    return old;

}

cell *update_ghostcells(cell *old, int imax, int jmax){
    for(int i = 0; i < imax; i++){
        old[i+imax].p               = old[i+2*imax].p;
        old[(jmax-1)*(imax)+i].p = old[(jmax-2)*(imax)+i].p;
    }
    
    for(int j = 0; j < jmax; j++){
        old[j*imax].p     = old[j*imax+1].p;
        old[(j+1)*imax-1].p   = old[((j+1)*imax)-2].p;
    }
    return old;
}


cell *newpressure(cell* field,f_and_g *newfg,int imax,int jmax,float dx,float dy,float dt){
    float pressure_res = 0;
    
    for(int i = 1; i < imax - 1 ; i++){
        for(int j = 1; j< jmax - 1; j++){
            pressure_res = pressure_res + pow(field[j*imax+i].p,2);
        }
    }
    pressure_res = sqrt(pressure_res/((imax-2)*(jmax-2)));

    float *rhs; 
    printf("\nrhs:\n");
    rhs = calloc(imax*jmax,sizeof(float));
    for(int i = 0;i < (imax*jmax);i++){
        if(i>imax && i<(jmax*(imax-1))){
            if(i%imax != 0 && (i+1)%imax != 0){
                rhs[i] = 
                (newfg[i].fvalue-newfg[i-1].fvalue)/dx+(newfg[i].gvalue-newfg[i-imax].gvalue)/dy
                /dt;
                //printf("%.3f\t",rhs[i]);
                
            
            }
        //if((i)%(imax)==0)
                    //printf("\n");
        }

    }
    printf("\n");
    
    //printf("\nhello\n");
    
    //printf("%f\n",pressure_res);
    if (pressure_res==0){
        pressure_res=1;
    }
    float residum = 0;
    int i = 0;
    while((residum>EPSILON*pressure_res || i<10)&&(i<200000)){
        i++;
        residum = 0;
        field = update_ghostcells(field,imax,jmax);
        field = p_it_plus(field,rhs,imax,jmax,dx,dy);
        for(int i = 1; i < imax - 1 ; i++)
        {
            for(int j = 1; j< jmax - 1; j++){
                residum = residum + pow(field[j*imax+i].p,2);
            }
        }
        printf("\nMein Druck:%f\n",field[45].p);
        residum = residum/((imax-2)*(jmax-2));
        residum = sqrt(residum);
        printf("%d:%f,%f\n",i,residum,pressure_res);

    }

    return field;

}