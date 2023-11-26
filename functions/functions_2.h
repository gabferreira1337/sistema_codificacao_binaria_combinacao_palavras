#ifndef PROJETO_AED1_LP1_FUNCTIONS_2_H
#define PROJETO_AED1_LP1_FUNCTIONS_2_H

#include <time.h>
#include "functions_1.h"

/**
 * sets struct
 */
typedef struct{
    SETS s1;
    SETS s2;

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
void print_AD(const AD_WORDS_HOLDER *ad);
void insert_element_to_AD_in_order(AD_WORDS_HOLDER *ad_holder,SETS s1 , SETS s2, char *last_date);
//void insert_element_to_index_AD(AD_WORDS_HOLDER *ad_holder,VAL_AD_WORDS_HOLDER *val_words_holder, char *last_date, int index);
void insert_element_to_index_AD(AD_WORDS_HOLDER *ad_holder, SETS *set1, SETS *set2,char*last_date, int index);

void merge_sort(AD_WORDS_HOLDER ad);
void sort(VAL_AD_WORDS_HOLDER *arr,char **result, int lo, int hi);
void merge(VAL_AD_WORDS_HOLDER *arr,char **result, int lo, int mid, int hi);
void insert_to_VAL_AD_WORDS_HOLDER(VAL_AD_WORDS_HOLDER *val_ad_words_holder, SETS *set1, SETS *set2);
/**
 * sets struct
 */

char *get_current_date();
int bin_search_insert_pos(const AD_WORDS_HOLDER *arr_din, char *date);


void realloc_AD(AD_WORDS_HOLDER *ad_holder, int size);
/**
 * free
 */
void free_dynamic_array(AD_WORDS_HOLDER *arr);

int main_functions_2(int argc , char **argv);

#endif //PROJETO_AED1_LP1_FUNCTIONS_2_H
