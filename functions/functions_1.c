#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions_1.h"


#define R 3
#define C 3

#define RC 27 //8 * 3 store space for each char conversion to binary
#define CC 27


int main_functions_1(int argc , char **argv){

    // seed to generate random numbers
    srand(time(NULL));

    SET1 set1;
    set1.matrixc1 = matrix_init_int(RC,CC);
    SET2 set2;

    set1.matrix1 = matrix_init_char(R,C);

    set1.matrix1[0][0]='C';
    set1.matrix1[0][1]='A';
    set1.matrix1[0][2]='O';
    set1.matrix1[1][0]='c';
    encode(&set1);
    //print_matrix_int(&set1,NULL);
    //print_matrix_char(&set1,NULL);


    gen_rnd_char(WORD_LENGTH);

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

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            mat[i][j] = gen_rnd_char(7);
        }
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%c",mat[i][j]);
        }
        putchar('\n');
    }



    return mat;
}

void print_matrix_int(SET1 *set1, SET2 *set2) {

    int l=0;
    for (int i = 0; i < R; ++i){
        for (int j = 0; j < CC; ++j) {
            printf("%d",set1->matrixc1[i][j]);
        }
        putchar('-');
        for (int h = 0; h < 3; ++h) {
            printf("%c",set1->matrix1[l][h]);
        }
        putchar('\n');
    }
}


void encode(SET1 *set1){

    int charCalc =0;

    int j = 0;
    for (int i = 0; i < R; ++i) {
        for (int k = 0; k < C; ++k) {
            charCalc = (unsigned char) set1->matrix1[i][k];

            if (charCalc >= '0' && charCalc <= '9') {
                int digit = charCalc - '0';
                for (int l = 0; l <= 4; ++l) {
                    set1->matrixc1[i][j] = (digit >> l) & 1;
                    j--;
                }
            } else if (charCalc >= 'a' && charCalc <= 'z') {
                // 10 represents the beginning of letters
                int letter = charCalc - 'a' + 10;
                for (int l = 0; l <= 8; ++l) {
                    // when last digit is 0 break from the loop so it won't store the left 0's
                    if((letter >>l) == 0) break;
                    set1->matrixc1[i][j] = (letter >> l) & 1;
                    j--;

                }
            } else if (charCalc >= 'A' && charCalc<= 'Z') {
                /* 10 represents the beginning of letters
                 *  'a' is the value 36 (A = 10 a = 10 + 26)
                */
                int letter = charCalc - 'A' + 36;
                for (int l = 0; l <= 8; ++l) {
                    if((letter >>l) == 0) break;
                    set1->matrixc1[i][j] = (letter >> l) & 1;
                    j--;
                }

            }
        }
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
    free(set2->matrixc2);*/
}


