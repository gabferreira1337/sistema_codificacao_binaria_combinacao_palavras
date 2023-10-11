#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions_1.h"


#define R 6
#define C 7

#define RC 56 //8 * 3 store space for each char conversion to binary
#define CC 48
#define WORD_LENGTH 7


int main_functions_1(int argc , char **argv){

    // seed to generate random numbers
    srand(time(NULL));

    SETS set1;
    set1.matrix_encode = matrix_init_short(RC,CC);
    SETS set2;

    set1.matrix = matrix_init_char(R,C);

    set1.matrix[0][0]='C';
    set1.matrix[0][1]='A';
    set1.matrix[0][2]='O';
    set1.matrix[1][0]='c';
    encode(&set1);
    //print_matrix_int(&set1,NULL);
    //print_matrix_char(&set1,NULL);


    gen_rnd_char(WORD_LENGTH);

    freemem(&set1);

    return 0;
}


short **matrix_init_short(int row ,int col){
        // Allocate memory for array of pointers
        short** mat = (short**)calloc(row, sizeof(short*));

        if (mat == NULL) {
            printf("Matrix int row malloc\n");
            exit(1);
        }

        for (int i = 0; i < row; ++i) {
            // Allocate memory for each pointer (cols)
            mat[i] = (short*)calloc(col, sizeof(short));
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

void print_matrix_int(SETS *set) {

    int l=0;
    for (int i = 0; i < R; ++i){
        for (int j = 0; j < CC; ++j) {
            printf("%d",set->matrix_encode[i][j]);
        }
        putchar('-');
        for (int h = 0; h < 3; ++h) {
            printf("%c",set->matrix[l][h]);
        }
        putchar('\n');
        l++;
    }
}

void print_matrix_char(SETS *set) {

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            printf("%c",set->matrix_encode[i][j]);
        }
        putchar('\n');
    }

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {


        }
    }
}


void encode(SETS *set){

    int charCalc =0;

    int j = 0;
    for (int i = 0; i < R; ++i) {
        j = CC - 1;
        for (int k = 0; k < C; ++k) {
            charCalc = (unsigned char) set->matrix_encode[i][k];

            if (charCalc >= '0' && charCalc <= '9') {
                int digit = charCalc - '0';
                for (int l = 0; l <= 4; ++l) {
                    set->matrix_encode[i][j] = (digit >> l) & 1;
                    j--;
                }
            } else if (charCalc >= 'a' && charCalc <= 'z') {
                // 10 represents the beginning of letters
                int letter = charCalc - 'a' + 10;
                for (int l = 0; l <= 8; ++l) {
                    // when last digit is 0 break from the loop, so it won't store the left 0's
                    if((letter >>l) == 0) break;
                    set->matrix_encode[i][j] = (letter >> l) & 1;
                    j--;

                }
            } else if (charCalc >= 'A' && charCalc<= 'Z') {
                /* 10 represents the beginning of letters
                 *  'a' is the value 36 (A = 10 a = 10 + 26)
                */
                int letter = charCalc - 'A' + 36;
                for (int l = 0; l <= 8; ++l) {
                    if((letter >>l) == 0) break;
                    set->matrix_encode[i][j] = (letter >> l) & 1;
                    j--;
                }
            }
        }
    }
}

void freemem(SETS *set) {

    for (int i = 0; i < 3; ++i) {
        free(set->matrix_encode[i]);
        set->matrix_encode[i] =NULL;
        free(set->matrix[i]);
        set->matrix[i] =NULL;
    }

    for (int i = 0; i < RC; ++i) {
        free(set->matrix[i]);
        set->matrix_encode[i] =NULL;
    }
    free(set->matrix);
    set->matrix =NULL;
    free(set->matrix_encode);
    set->matrix_encode =NULL;
    /*free(set2->matrix2);
    free(set2->matrixc2);*/
}

char gen_rnd_char(int length){
    int random_number;
    // Generate random number between 'a' and 'z'
    random_number = 'a' + rand() % 26;

    return (char) random_number;
}

