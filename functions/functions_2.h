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


typedef struct node_ll_words_holder{
    WORDS_HOLDER words_holder;
    char *last_update_date;
    struct node_ll_words_holder *pnext;
    struct node_ll_words_holder *pback;
}NODE_LL_WORDS_HOLDER;


typedef struct ll_words_holder{
   int nnodes;
   NODE_LL_WORDS_HOLDER *phead;
   NODE_LL_WORDS_HOLDER *ptail;
}LL_WORDS_HOLDER;



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
/**
 * sets struct
 */
void print_AD(const AD_WORDS_HOLDER *ad);
/**
 * sets struct
 */
void insert_element_to_AD_in_order(AD_WORDS_HOLDER *ad_holder,SETS s1 , SETS s2, char *last_date);
/**
 * sets struct
 */
//void insert_element_to_index_AD(AD_WORDS_HOLDER *ad_holder,VAL_AD_WORDS_HOLDER *val_words_holder, char *last_date, int index);
/**
 * sets struct
 */
void print_words_found(AD_WORDS_HOLDER *arr     ,int *index_set1, int *index_set2, int index_ad);
//int *find_Word_index(&arr->array_val[j].words_holder.s1,words[i], index_set1, 1);
void insert_element_to_index_AD(AD_WORDS_HOLDER *ad_holder, SETS *set1, SETS *set2,char*last_date, int index);
/**
 * sets struct
 */
void merge_sort(AD_WORDS_HOLDER ad);
/**
 * sets struct
 */
void sort(VAL_AD_WORDS_HOLDER *arr,char **result, int lo, int hi);
/**
 * sets struct
 */
void merge(VAL_AD_WORDS_HOLDER *arr,char **result, int lo, int mid, int hi);
/**
 * sets struct
 */void find_word_ad(AD_WORDS_HOLDER *arr, char **words,int W, int lo, int hi);
/**
 * sets struct
 */
void insert_to_VAL_AD_WORDS_HOLDER(VAL_AD_WORDS_HOLDER *val_ad_words_holder, SETS *set1, SETS *set2);
/**
 * sets struct
 */
char *get_current_date();
/**
 * sets struct
 */
int bin_search_insert_pos(const AD_WORDS_HOLDER *arr_din, char *date);
/**
 * sets struct
 */
void delete_element_index(AD_WORDS_HOLDER *ad,int index);
/**
 * sets struct
 */
void realloc_AD(AD_WORDS_HOLDER *ad_holder, int size);
/**
 * free
 */
void free_dynamic_array(AD_WORDS_HOLDER *arr);
void free_ll_words_holder(LL_WORDS_HOLDER *ll);
NODE_LL_WORDS_HOLDER *create_words_holder_node(LL_WORDS_HOLDER *ll,NODE_LL_WORDS_HOLDER *pos, SETS *set1, SETS *s2, char *last_date);
//perguntar
void insert_node_ll_sorted(LL_WORDS_HOLDER *ll, SETS *set1, SETS *set2, char *last_date);
void insert_node_ll_index(LL_WORDS_HOLDER *ll, SETS *set1, SETS *set2, char *last_date, int index);
void print_ll_words_holder(LL_WORDS_HOLDER *ll);
NODE_LL_WORDS_HOLDER *create_words_holder_node_index(LL_WORDS_HOLDER *ll,NODE_LL_WORDS_HOLDER *pos, SETS *set1, SETS *set2, char *last_date);
NODE_LL_WORDS_HOLDER *bin_search_insert_ll(LL_WORDS_HOLDER *ll, char *date);

int main_functions_2(int argc , char **argv);

#endif //PROJETO_AED1_LP1_FUNCTIONS_2_H
