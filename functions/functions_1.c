#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions_1.h"


#define R 7
#define C 7
#define WORD_LENGTH 7


int main_functions_1(int argc , char **argv){

    // seed to generate random numbers
    srand(time(NULL));

    SETS set1;
    set1.matrix_encode = matrix_init_int(R,C);
    SETS set2;

    set1.matrix = matrix_init_char(R,C);

    set1.colsize_char = C;
    set1.colsize_encode =C * 7;
    set1.rowsize = R;

    /*set1.matrix[0][0]='C';
    set1.matrix[0][1]='A';
    set1.matrix[0][2]='O';
    set1.matrix[1][0]='c';*/
    init_arr_word_size(&set1);

    matrix_rnd_char_gen(&set1, WORD_LENGTH);
    print_matrix_char(&set1);
    encode(&set1);
    print_matrix_int(&set1);
    print_arr_word_size(set1);

    insert_word_char(&set1, set1.rowsize, 2);
    print_matrix_char(&set1);
    encode(&set1);
    print_matrix_int(&set1);
    print_arr_word_size(set1);


    freemem(&set1);
    return 0;
}

 int **matrix_init_int(int row ,int col){
        // Allocate memory for array of pointers
        int** mat = (int**)calloc(row, sizeof(int*));

        if (mat == NULL) {
            printf("Matrix_init_short - row malloc\n");
            exit(1);
        }

        for (int i = 0; i < row; ++i) {
            // Allocate memory for each pointer (cols)
            *(mat+i) = (int*)calloc(col * 7, sizeof(int));
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
        exit(0);
    }

    for (int i = 0; i < row; ++i) {
        // Allocate memory for each pointer (cols)
        *(mat +i) = (char*)calloc(col, sizeof(char));
        if (mat[i] == NULL) {
            printf("Matrix int col malloc\n");
            exit(0);
        }
    }
    return mat;
}

void print_matrix_int(SETS *set) {
    for (int i = 0; i < set->rowsize; ++i){
        for (int j = 0; j < *(set->arr_word_size + i) * 7; ++j) {
            if(*(*(set->matrix_encode + i) +j) == -1) continue;
            printf(" %d",*(*(set->matrix_encode + i) +j));
        }
        putchar('\n');
    }
}

void print_matrix_char(SETS *set) {
    for (int i = 0; i < set->rowsize; ++i) {
        for (int j = 0; j < set->arr_word_size[i]; ++j) {  // set->colsize_char se for isto vai dar print a nulls
            printf(" %c",*(*(set->matrix + i) +j));
        }
        putchar('\n');
    }
}

void encode(SETS *set){
    int charCalc = 0;
    int  j =0;
    int p;
    for (int i = 0; i < set->rowsize; ++i) { // Para cada palavra
        //printf("%s\n", set->matrix[i]);
       // printf("--%s",set->matrix[i]);
        j =0;
        int count = 0;
        for (int k = 0;k < *(set->arr_word_size); k++) { // Para cada caracter !
            charCalc = (unsigned char) *(*(set->matrix + i) +k);
           //printf("--%s",set->matrix[i]);
           //printf(" \n%d\n", count++);

            if (charCalc >= '0' && charCalc <= '9') {
                int digit = charCalc - '0';
                for (int l = 6; l >= 0 && j < (set->arr_word_size[i]) * 7 ; l--, j++) {
                    *(*(set->matrix_encode + i) +j) = (digit >> l) & 1;
                }
            } else if (charCalc >= 'a' && charCalc <= 'z') {
               // printf(" %c", charCalc);
                //printf(" %d", count);
                // 10 represents the beginning of letters
                int letter = charCalc - 'a' + 10;
                //printf(" %d", letter);
                for (int l = 6; l >= 0 && j < (set->arr_word_size[i]) * 7; l--, j++) { // Para cada cara
                    // when last digit is 0 break from the loop, so it won't store the left 0's
                    if ((letter >> l) == 0) {
                        *(*(set->matrix_encode + i) + j) = -1;
                    } else {
                        *(*(set->matrix_encode + i) + j) = (letter >> l) & 1;
                        if (i == 8) {
                            printf("+%d+", set->matrix_encode[i - 1][j]);
                            printf("'%d'", set->matrix_encode[i][j]);
                        }
                    }
                }
            } else if (charCalc >= 'A' && charCalc <= 'Z') {
                /* 10 represents the beginning of letters
                 *  'a' is the value 36 (A = 10 a = 10 + 26)
                */
                int letter = charCalc - 'A' + 36;
                for (int l = 6; l >= 0 && j < (set->arr_word_size[i]) * 7; l--, j++) {
                    if((letter >>l) == 0) break;
                    *(*(set->matrix_encode + i) +j) = (letter >> l) & 1;
                }
            }
        }
    }
}

char gen_rnd_char(int length){
    int random_number;
    // Generate random number between 'a' and 'z'
    random_number = 'a' + rand() % 26;

    return (char) random_number;
}

char **matrix_rnd_char_gen(SETS *set,int word_length) {
    for (int i = 0; i < set->rowsize; ++i) {
        // store word_length in an array
        set->arr_word_size[i] = word_length;
        for (int j = 0; j < word_length; ++j) { // set->colsize_char se fosse isto ia gerar sempre 7 numeros
            *(*(set->matrix + i) +j) = gen_rnd_char(word_length);
        }
    }
    return NULL;
}


void insert_word_char(SETS *set,int start_row, int number_words) {
    // Start_row always max num of lines
    set->rowsize += number_words;
    /*Realloc mem for both matrix */
    matrix_realloc(set);
    matrix_encode_realloc(set);

    char word[7+1] = " ";
    for (int i = start_row; i < set->rowsize; ++i) {

        if (fscanf(stdin, "%s", word) == EOF) {
            printf("Failed to read the word.\n");
            freemem(set);
            return;
        }
        //store size of new word in arr_word_size for delim
        set->arr_word_size[i] = (int) strlen(word);

        for (int j = 0; j < set->arr_word_size[i]; ++j) {
            //printf("%c", word[j]);
            *(*(set->matrix + i) + j) = word[j];
            //if the word is smaller than colsize_char fill the rest with ' '
            if(j >= strlen(word))
                *(*(set->matrix + i) + j) = ' ';
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

    /*for (int i = 0; i < RC; ++i) {
        free(set->matrix[i]);
        set->matrix[i] =NULL;
    }*/
    free(set->matrix);
    set->matrix =NULL;
    free(set->matrix_encode);
    set->matrix_encode =NULL;

    free(set->arr_word_size);
}

void matrix_realloc(SETS *set) {
    /* Realloc memory for arr_word_size */
    set->arr_word_size = (int *) realloc(set->arr_word_size,set->rowsize * sizeof(int));

    if(set->arr_word_size == NULL){
        printf("Realloc arr_word_size failed !\n");
        freemem(set);
        exit(0);
    }

    set->matrix = (char **) realloc(set->matrix,set->rowsize * sizeof(char *));

    if(set->matrix == NULL){
        printf("Realloc set->matrix failed !\n");
        freemem(set);
        exit(0);
    }

    for (int i = 0; i < set->rowsize; ++i) {
        *(set->matrix +i) = (char*) realloc(*(set->matrix + i),set->colsize_char *sizeof(char));
        if(*(set->matrix + i) == NULL){
            printf("Matrix char realloc\n");
            freemem(set);
            exit(0);
        }
    }
}

void init_arr_word_size(SETS *set) {
    set->arr_word_size = (int *) calloc(set->rowsize, sizeof(int));

    if((set->arr_word_size) == NULL){
        printf("Array word size calloc\n");
        freemem(set);
        exit(0);
    }
}

void print_arr_word_size(SETS set) {
    for (int i = 0; i < set.rowsize; ++i) {
        printf("%d - %d\n", i, set.arr_word_size[i]);
    }
}

void matrix_encode_realloc(SETS *set) {

    /* Realloc memory for encode matrix*/
    set->matrix_encode= (int **) realloc(set->matrix_encode,set->rowsize * sizeof(int *)); //allocate for n_words

    if(set->matrix_encode == NULL){
        printf("Matrix encode realloc\n");
        freemem(set);
        exit(0);
    }

//allocate for words_size
    for (int i = 0; i < set->rowsize; ++i) {
        *(set->matrix_encode +i) = (int*) realloc(*(set->matrix_encode + i),(set->arr_word_size[i] * 7) *sizeof(int));
        if(*(set->matrix_encode + i) == NULL){
            printf("Matrix encode realloc\n");
            freemem(set);
            exit(0);
        }
    }
}

