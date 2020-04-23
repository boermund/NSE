//Function for allocating the field 
#include <stdlib.h>
#include <stdio.h>



cell *fieldalloc(int i, int j){
    cell *field;
    field = calloc(i*j,sizeof(cell));
    return field;
    
}
