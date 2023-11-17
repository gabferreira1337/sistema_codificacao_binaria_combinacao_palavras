#ifndef PROJETO_AED1_LP1_FUNCTIONS_2_H
#define PROJETO_AED1_LP1_FUNCTIONS_2_H

#include <time.h>

/**
 * sets struct
 */
typedef struct{
    char **matrix1;
    char **matrix2;
    int **matrix_encode1;
    int **matrix_encode2;
    int *arr_word_size1;
    int *arr_word_size2;
    int rowsize;
    int colsize_char;
    int colsize_encode;

}WORDS_HOLDER;


typedef struct{
    WORDS_HOLDER words_holder;
    char *last_update_date;

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
/**
 * sets struct
 */

void create_dynamic_array(AD_WORDS_HOLDER *arr);
/**
 * sets struct
 */

void init_VAL_AD_WORDS_HOLDER(VAL_AD_WORDS_HOLDER *val_holder);

void insert_element_to_ad(VAL_AD_WORDS_HOLDER val_holder, AD_WORDS_HOLDER *ad_holder);
/**
 * sets struct
 */

char *get_current_date();

/**
 * sets struct
 */
void free_dynamic_array(AD_WORDS_HOLDER *arr);


int main_functions_2(int argc , char **argv);

#endif //PROJETO_AED1_LP1_FUNCTIONS_2_H
