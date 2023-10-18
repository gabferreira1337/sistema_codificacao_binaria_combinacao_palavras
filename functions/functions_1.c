#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions_1.h"


#define R 7
#define C 7
#define RC 27 //8 * 3 store space for each char conversion to binary
#define CC 27
#define WORD_LENGTH 7


int main_functions_1(int argc , char **argv){

    // seed to generate random numbers
    srand(time(NULL));

    SETS set1;
    set1.matrix_encode = matrix_init_int(RC,CC);
    SETS set2;

    set1.matrix = matrix_init_char(R,C);

    set1.colsize_char = C;
    set1.colsize_encode =CC;
    set1.rowsize = R;

    /*set1.matrix[0][0]='C';
    set1.matrix[0][1]='A';
    set1.matrix[0][2]='O';
    set1.matrix[1][0]='c';*/
    //encode(&set1);
    //print_matrix_int(&set1);
   // print_matrix_char(&set1);

    matrix_rnd_char_gen(&set1, WORD_LENGTH);
    /*print_matrix_char(&set1);
    print_matrix_char(&set1);*/

    encode(&set1);
    print_matrix_int(&set1);
    print_matrix_char(&set1);


    //insert_word_char(&set1, R, 5);

    freemem(&set1);

    return 0;
}


unsigned int **matrix_init_int(int row ,int col){
        // Allocate memory for array of pointers
        unsigned int** mat = (unsigned int**)calloc(row, sizeof(unsigned int*));

        if (mat == NULL) {
            printf("Matrix_init_short - row malloc\n");
            exit(1);
        }

        for (int i = 0; i < row; ++i) {
            // Allocate memory for each pointer (cols)
            *(mat+i) = (unsigned int*)calloc(col, sizeof(unsigned int));
            if (*(mat+i) == NULL) {
                printf("Matrix int col malloc\n");
                free(mat);
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
        *(mat +i) = (char*)calloc(col, sizeof(char));
        if (mat[i] == NULL) {
            printf("Matrix int col malloc\n");
            exit(1);
        }
    }

    return mat;
}

void print_matrix_int(SETS *set) {
    int l=0;
    for (int i = 0; i < set->rowsize; ++i){
        for (int j = 0; j < CC; ++j) {
            printf("%d",*(*(set->matrix_encode + i) +j));
        }
        putchar('\n');
    }

}

void print_matrix_char(SETS *set) {
    for (int i = 0; i < set->rowsize; ++i) {
        for (int j = 0; j < set->colsize_char; ++j) {
            printf(" %c",*(*(set->matrix + i) +j));
        }
        putchar('\n');
    }
}

void encode(SETS *set){
    int charCalc =0;
    int j = 0;
    for (int i = 0; i < set->rowsize; ++i) {
        j = CC - 1;
        for (int k = 0; k < set->colsize_encode; ++k) {
            charCalc = (unsigned char) set->matrix[i][k];

            if (charCalc >= '0' && charCalc <= '9') {
                int digit = charCalc - '0';
                for (int l = 0; l < 8; ++l) {
                    *(*(set->matrix_encode + i) +j) = (digit >> l) & 1;
                    j--;
                }
            } else if (charCalc >= 'a' && charCalc <= 'z') {
                // 10 represents the beginning of letters
                int letter = charCalc - 'a' + 10;
                for (int l = 0; l < 8; ++l) {
                    // when last digit is 0 break from the loop, so it won't store the left 0's
                    if((letter >>l) == 0) break;
                    *(*(set->matrix_encode + i) +j) = (letter >> l) & 1;
                    j--;

                }
            } else if (charCalc >= 'A' && charCalc<= 'Z') {
                /* 10 represents the beginning of letters
                 *  'a' is the value 36 (A = 10 a = 10 + 26)
                */
                int letter = charCalc - 'A' + 36;
                for (int l = 0; l < 8; ++l) {
                    if((letter >>l) == 0) break;
                    *(*(set->matrix_encode + i) +j) = (letter >> l) & 1;
                    j--;
                }
            }
        }
    }
}


/*
void encode(SETS *set){
    char charCalc ='\0';
    unsigned int numbin = 0;

    for (int i = 0; i < set->rowsize; ++i) {
        j = CC - 1;
        for (int k = 0; k < set->colsize_encode; ++k) {
            charCalc = (unsigned char) set->matrix_encode[i][k];

            if (charCalc >= '0' && charCalc <= '9') {
                int digit = charCalc - '0';
                for (int l = 0; l <= 4; ++l) {
                    str[l] =(char) ((digit >> l) & 1) ;
                    j--;
                }
            } else if (charCalc >= 'a' && charCalc <= 'z') {
                // 10 represents the beginning of letters 0-9 a-z
                unsigned int letter = charCalc - 'a' + 10;
                numbin = int_to_bin(letter);
                *(*(set->matrix_encode + i) +k) = numbin;

            } else if (charCalc >= 'A' && charCalc<= 'Z') {
                int letter = charCalc - 'A' + 36;
                numbin = int_to_bin(letter);
                *(*(set->matrix_encode + i) +k) = numbin;
            }

        }

    }
}*/


unsigned int int_to_bin(unsigned int k) {
    if (k == 0) return 0;
    if (k == 1) return 1;
    return (k % 2) + 10 * int_to_bin(k / 2);
}


char gen_rnd_char(int length){
    int random_number;
    // Generate random number between 'a' and 'z'
    random_number = 'a' + rand() % 26;
    return (char) random_number;
}

char **matrix_rnd_char_gen(SETS *set,int word_length) {

    for (int i = 0; i < set->rowsize; ++i) {
        for (int j = 0; j < set->colsize_char; ++j) {
            *(*(set->matrix + i) +j) = gen_rnd_char(word_length);
        }
    }

    return NULL;
}



void insert_word_char(SETS *set,int start_row, int number_words) {
    // Start_row é sempre o valor maximo no de linhas

    set->rowsize += number_words;
    /*Realloc mem for both matrix */
    matrix_realloc(set);


    for (int i = 0; i < set->rowsize; ++i) {
        for (int j = 0; j < set->colsize_char; ++j) {
           /// *(*(set->matrix + i) +j) = ;
            // 1 palavra por linha - cada palavra max 7 caracteres
        }

    }

}

void insert_word_short(SETS *set,int start_row, int number_words) {
    // Start_row é sempre o valor maximo no de linhas

}



void freemem(SETS *set) {

    for (int i = 0; i < set->rowsize; ++i) {
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

}

void matrix_realloc(SETS *set) {

    /* Realloc memory for char matrix */

    set->matrix = (char **) realloc(set->matrix,set->rowsize * sizeof(char *));

    if(set->matrix == NULL){
        freemem(set);
        exit(1);
    }

    for (int i = 0; i < set->rowsize; ++i) {
        *(set->matrix +i) = (char*) realloc(*(set->matrix + i),set->colsize_char *sizeof(char));
        if(*(set->matrix + i) == NULL){
            printf("Matrix char realloc\n");
            freemem(set);
            exit(1);
        }
    }

    /* Realloc memory for encode matrix*/

    set->matrix = (short **) realloc(set->matrix,set->rowsize * sizeof(short *));

    if(set->matrix == NULL){
        printf("Matrix encode realloc\n");
        freemem(set);
        exit(1);
    }

    for (int i = 0; i < set->rowsize; ++i) {
        *(set->matrix +i) = (short*) realloc(*(set->matrix + i),set->colsize_char *sizeof(short *));
        if(*(set->matrix + i) == NULL){
            printf("Matrix encode realloc\n");
            freemem(set);
            exit(1);
        }

    }


}

