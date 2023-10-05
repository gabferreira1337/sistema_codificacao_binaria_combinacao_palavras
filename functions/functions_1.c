#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions_1.h"


#define R 3
#define C 3

#define RC 27 //8 * 3 store space for each char conversion to binary
#define CC 27


int main_functions_1(int argc , char **argv){

    SET1 set1;
    set1.matrixc1 = matrix_init_int(RC,CC);
    SET2 set2;

    set1.matrix1 = matrix_init_char(R,C);

    set1.matrix1[0][0]='a';
    set1.matrix1[1][0]='b';
    //print_matrix(&set1);
    encode(&set1);


    freemem(&set1, &set2);

    return 0;
}


int **matrix_init_int(int row ,int col){
        // Allocate memory for array of pointers
        int** mat = (int**)calloc(row, sizeof(int*));

        if (mat == NULL) {
            printf("Matrix int row malloc\n");
            exit(1);
        }

        for (int i = 0; i < row; ++i) {
            // Allocate memory for each pointer (cols)
            mat[i] = (int*)calloc(col, sizeof(int));
            if (mat[i] == NULL) {
                printf("Matrix int col malloc\n");
                exit(1);
            }
        }

    return mat;
}
char **matrix_init_char(int row ,int col){
    // Allocate memory for array of pointers
    char** mat = (char**)calloc(row, sizeof(char*));

    if (mat == NULL) {
        printf("Matrix int row malloc\n");
        exit(1);
    }

    for (int i = 0; i < row; ++i) {
        // Allocate memory for each pointer (cols)
        mat[i] = (char*)calloc(col, sizeof(char));
        if (mat[i] == NULL) {
            printf("Matrix int col malloc\n");
            exit(1);
        }
    }

    return mat;
}

void print_matrix_int(SET1 *set1) {

    for (int i = 0; i < RC; ++i) {
        for (int j = 0; j < CC; ++j) {
            printf("%d",set1->matrix1[i][j]);
        }
        putchar('\n');
    }
}


void encode(SET1 *set1){

    int  numCalc =0;

    int j = CC;
    for (int i = 0; i < R; ++i) {
        for (int k = 0; k < C; ++k) {
            numCalc = (int) set1->matrix1[i][k];

            while (numCalc != 0) {
                set1->matrixc1[i][j] = numCalc % 2;
                numCalc /= 2;

                j--;
            }
            j = CC;
        }
    }

    for (int i = 0; i < RC; ++i) {
        for (int k = 0; k < CC; ++k) {
            printf("%d", set1->matrixc1[i][k]);
        }
        putchar('\n');
    }

}

void freemem(SET1 *set1, SET2 *set2) {

    for (int i = 0; i < 3; ++i) {
        free(set1->matrixc1[i]);
        set1->matrixc1[i] =NULL;
        free(set1->matrix1[i]);
        set1->matrix1[i] =NULL;
    }

    for (int i = 0; i < RC; ++i) {
        free(set1->matrixc1[i]);
        set1->matrixc1[i] =NULL;
    }
    free(set1->matrix1);
    set1->matrix1 =NULL;
    free(set1->matrixc1);
    set1->matrixc1 =NULL;
    /*free(set2->matrix2);
    free(set1->matrixc1);
    free(set2->matrixc2);*/
}


