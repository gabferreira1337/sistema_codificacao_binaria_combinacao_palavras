#ifndef PROJETO_AED1_LP1_FUNCTIONS_2_H
#define PROJETO_AED1_LP1_FUNCTIONS_2_H

#include <time.h>

/**
 * sets struct
 */
typedef struct{
    char **matrix;
    int **matrix_encode;
    int *arr_word_size;
    int rowsize;
    int colsize_char;
    int colsize_encode;

}WORDS_HOLDER;


typedef struct{
    WORDS_HOLDER words_holder;
    time_t last_update;

}VAL_AD_WORDS_HOLDER;

typedef struct{
    int size;
    int count;
    VAL_AD_WORDS_HOLDER *array_val;

}AD_WORDS_HOLDER;



/**
 * sets struct
 */

AD_WORDS_HOLDER* dynamic_array_init(int size);
/**
 * sets struct
 */

void dynamic_array_realloc(AD_WORDS_HOLDER *arr);


void free_dynamic_array(AD_WORDS_HOLDER *arr);


int main_functions_2(int argc , char **argv);

#endif //PROJETO_AED1_LP1_FUNCTIONS_2_H
