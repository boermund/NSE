#include <stdio.h>

int main(void){
    int pos[] = {
        1,3,3,5,6,
        7,0,37,8,34,
        5,3,5,6,3,
        1,7,8
    };

    FILE * myfile;
    myfile = fopen("colums in file.txt", "w+");

    int len = sizeof(pos)/sizeof(*pos);
    printf("%d\n", len);

    int col_len = 5;
    for(int i = 0; i < col_len; ++i){
        for(int j = i; j < len; j += col_len){
            printf("%2d ", pos[j]);
            fprintf(myfile, "%2d\n", pos[j]);
        }
        puts("");
    }
}