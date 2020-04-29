
#include <stdlib.h>
#include <stdio.h>

/* 
function to put txt file into a struct, wich has a form of an big array 
you have to put in 2 files and the struct (two variables) in wich you want to put the data from the two files 
returns a field
*/

cell *read_data(cell *field, FILE* fd, FILE* fd2, int imax, int jmax){

    for(int j=0;j<jmax;j++){
        for(int i=0;i<imax;i++){
        fscanf(fd, "%f", &field[i + imax*j].u);
	fscanf(fd2, "%f", &field[i + imax*j].v);
        }
    }
    return field;
    
}