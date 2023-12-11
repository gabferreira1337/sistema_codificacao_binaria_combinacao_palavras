#ifndef PROJETO_AED1_LP1_FUNCTIONS_2_H
#define PROJETO_AED1_LP1_FUNCTIONS_2_H

#include <time.h>
#include "functions_1.h"

/**
 * WORDS_HOLDER struct
 *
 */
typedef struct{
    SETS s1;        ///one set with matrix of words and their UFP6 representation
    SETS s2;

}WORDS_HOLDER;

/**
 * VAL_AD_WORDS_HOLDER struct
 */
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
 * @paragraph Initialize dynamic array with given size
 * @param size - size of dynamic array
 * @return pointer to AD_WORDS_HOLDER struct created
 */
AD_WORDS_HOLDER* dynamic_array_init(int size);
/**
 * @paragraph Realloc dynamic array
 * @param arr - pointer to struct dynamic array of words holder
 */
void dynamic_array_realloc(AD_WORDS_HOLDER *arr);
/**
 * @paragraph
 */
void create_dynamic_array(AD_WORDS_HOLDER *arr);
/**
 * sets struct
 */
void init_VAL_AD_WORDS_HOLDER(VAL_AD_WORDS_HOLDER *val_holder);
/**
 * @paragraph print dynamic array
 * @param ad - pointer to AD_WORDS_HOLDER struct
 */
void print_AD(const AD_WORDS_HOLDER *ad);
/**
 * @paragraph Insert element in dynamic array in chronological order by date ASC
 * @param ad_holder - pointer to AD_WORDS_HOLDER struct
 * @param set1 - pointer to set of matrix with words and ufp6
 * @param set2 - pointer to set of matrix with words and ufp6
 * @param last_date - last update date of both sets
 */
void insert_element_to_AD_in_order(AD_WORDS_HOLDER *ad_holder,SETS s1 , SETS s2, char *last_date);
/**
 * @param ad_holder - pointer to AD_WORDS_HOLDER struct
 * @param index_set1 - pointer to array with index of words found in set1 ///in first position of array store the count of indexes to use inside this function
 * @param index_set2 - pointer to array with index of words found in set2 ///in first position of array store the count of indexes to use inside this function
 * @param index_ad - index of ad where we found the words
 */
void print_words_found(AD_WORDS_HOLDER *arr,int *index_set1, int *index_set2, int index_ad);
//int *find_Word_index(&arr->array_val[j].words_holder.s1,words[i], index_set1, 1);
/**
 * @paragraph Insert element in dynamic array in given index , if index >= count of elements realloc 2 * size_ad and insert at that index
 * if ad is full doubles the size of ad
 * @param ad_holder - pointer to AD_WORDS_HOLDER
 * @param set1 - pointer to set of matrix with words and ufp6
 * @param set2 - pointer to set of matrix with words and ufp6
 * @param last_date - last update date of both sets
 */
void insert_element_to_index_AD(AD_WORDS_HOLDER *ad_holder, SETS *set1, SETS *set2,char*last_date, int index);
/**
 * sets struct
 */
 void find_word_ad(AD_WORDS_HOLDER *arr, char **words,int W, int lo, int hi);
/**
 * sets struct
 */
void insert_to_VAL_AD_WORDS_HOLDER(VAL_AD_WORDS_HOLDER *val_ad_words_holder, SETS *set1, SETS *set2, char*last_date);
/**
 * sets struct
 */
char *get_current_date();
/**
 * @paragraph Function to search for the position in AD to insert new element
 * using binary search
 * @param arr_din - pointer to AD_WORDS_HOLDER
 * @param date - new_date of the element we want to insert
 * @return if more than 1 element equal inside ad it returns the position to the right of existing equal elements
 * if find same date returns the exact index
 * if doesn't find same date returns the right position where it should be added
 * example1: index 0 24-11-2023 index 1 26-11-2023 , new_date 25-11-2023 - returns 1
 * exmaple2 :index 0 24-11-2023 , new_date 23-11-2023 return   0
 * exmaple3 :index 0 24-11-2023 , new_date 25-11-2023 return   1
 */
int bin_search_insert_pos(const AD_WORDS_HOLDER *arr_din, char *date);
/**
 * sets struct
 */
void delete_element_index(AD_WORDS_HOLDER *ad,int index);
/**
 * @paragraph Realloc dynamic array with given size
 * @param ad_holder - pointer to AD_WORDS_HOLDER
 * @param size - size to reallocate the dynamic array
 */
void realloc_AD(AD_WORDS_HOLDER *ad_holder, int size);
/**
 * @paragraph Free dynamic array
 * @param arr - pointer to AD_WORDS_HOLDER
 */
void free_dynamic_array(AD_WORDS_HOLDER *arr);
/**
 * @paragraph Free Linked List
 * @param arr - pointer to LL_WORDS_HOLDER
 */
void free_ll_words_holder(LL_WORDS_HOLDER *ll);
/**
 * @paragraph Free Linked List
 * @param arr - pointer to LL_WORDS_HOLDER
 */
NODE_LL_WORDS_HOLDER *create_words_holder_node(LL_WORDS_HOLDER *ll,NODE_LL_WORDS_HOLDER *pos, SETS *set1, SETS *s2, char *last_date);
/**
 * @paragraph Free Linked List
 * @param arr - pointer to LL_WORDS_HOLDER
 */
void insert_node_ll_sorted(LL_WORDS_HOLDER *ll, SETS *set1, SETS *set2, char *last_date);
/**
 * @paragraph Free Linked List
 * @param arr - pointer to LL_WORDS_HOLDER
 */
void insert_node_ll_index(LL_WORDS_HOLDER *ll, SETS *set1, SETS *set2, char *last_date, int index);
/**
 * @paragraph Print Linked List
 * @param ll - pointer to Linked List LL_Words_Holder
 */
void print_ll_words_holder(LL_WORDS_HOLDER *ll);
/**
 * @paragraph
 * @param ll - pointer to Linked List LL_Words_Holder
 * @param index - node of Linked List to be deleted
 */
NODE_LL_WORDS_HOLDER *create_words_holder_node_index(LL_WORDS_HOLDER *ll,NODE_LL_WORDS_HOLDER *pos, SETS *set1, SETS *set2, char *last_date);
/**
 * @paragraph Search position in Linked List to add new node in chronological order DESC using binary search
 * @param ll - pointer to Linked List Words Holder
 * @param date - node of Linked List to be deleted
 * @return when new date > all nodes this function returns NULL ,
 * when new date < all nodes this function returns a pointer to the first node
 * and when new date between two nodes returns pointer to the left node
 */
NODE_LL_WORDS_HOLDER *bin_search_pos_ll(LL_WORDS_HOLDER *ll, char *date);
/**
 * @paragraph Find midpoint of Linked List using fast_ptr and slow_ptr
 * @param lo - pointer to lower node
 * @param hi - pointer to higher node
 * @return pointer to middle node
 */
NODE_LL_WORDS_HOLDER *find_mid_ll(NODE_LL_WORDS_HOLDER *lo, NODE_LL_WORDS_HOLDER *hi);
/**
 * @paragraph Delete node in a given position/index
 * @param ll - pointer to Linked List Words Holder
 * @param index - node of Linked List to be deleted
 */
void delete_ll_node_index(LL_WORDS_HOLDER *ll, int index);
/**
 * @paragraph search words and their respective ufp6 in given node
 * @param ll - pointer to Linked List Words Holder
 * @param words - array of words to search in LL
 * @param W - size of words array
 * @param lo - start index node
 * @param hi - end index node
 */
void find_word_ll(LL_WORDS_HOLDER *ll, char **words, int W, int lo, int hi);
/**
 * @paragraph Print words found in Linked List
 * @param ll - pointer to Linked List Words Holder
 * @param index_set1 - node of Linked List to be deleted
 * @param index_set1 - node of Linked List to be deleted

 */
void print_words_found_ll(NODE_LL_WORDS_HOLDER *ll, int  *index_set1, int *index_set2, int j);
/**
 * @paragraph Write one set to txt file
 * Words set: number_words = 5
 *5 r q m t v
 *1 n
 *5 e y w w v
 *4 l i u k
 *4 f o m s
 *UFP6:
 *25 1 1 0 1 1 1 1 0 1 0 1 0 1 1 0 1 1 1 0 1 1 1 1 1 1
 *5 1 0 1 1 1
 *27 1 1 1 0 1 0 0 0 1 0 1 0 0 0 0 0 1 0 0 0 0 0 1 1 1 1 1
 *20 1 0 1 0 1 1 0 0 1 0 1 1 1 1 0 1 0 1 0 0
 *19 1 1 1 1 1 1 0 0 0 1 0 1 1 0 1 1 1 0 0
 * @param set - pointer to set
 * @param fp - file pointer to the file where data will be inserted
 */
int write_set_to_txt(const SETS *set,FILE *fp);
/**
 * @paragraph Free Linked List
 * @param arr - pointer to LL_WORDS_HOLDER
 */
void write_set_ufp6_to_txt(const SETS *set, FILE *fp);
/**
 * @paragraph Free Linked List
 * @param arr - pointer to LL_WORDS_HOLDER
 */
int save_set_txt(const SETS *set, char *filename);

/**
 * @paragraph Delete node in a given position/index
 * @param ll - pointer to Linked List Words Holder
 * @param index - node of Linked List to be deleted
 */
void save_both_sets_to_txt(const SETS *s1, const SETS *s2, char *filename);
/**
 * @paragraph Delete node in a given position/index
 * @param ll - pointer to Linked List Words Holder
 * @param index - node of Linked List to be deleted
 */
int write_words_found_to_txt(NODE_LL_WORDS_HOLDER *current,const int *index_set1,const int *index_set2, char *filename, int index_ll);
/**
 * @paragraph Delete node in a given position/index
 * @param ll - pointer to Linked List Words Holder
 * @param index - node of Linked List to be deleted
 */
void write_index_array_words_to_file(SETS *set,FILE *fp,const int *index_array);
/**
 * @paragraph Delete node in a given position/index
 * @param ll - pointer to Linked List Words Holder
 * @param index - node of Linked List to be deleted
 */
void write_index_array_ufp6_to_file(SETS *set,FILE *fp,const int *index_array, int r);
/**
 * @paragraph Free Linked List
 * @param arr - pointer to LL_WORDS_HOLDER
 */
void read_txt_to_set(SETS *set, char *filename);
/**
 * @paragraph Free Linked List
 * @param arr - pointer to LL_WORDS_HOLDER
 */
void read_txt_words(SETS *set, FILE *fp);
/**
 * @paragraph Free Linked List
 * @param arr - pointer to LL_WORDS_HOLDER
 */
void read_txt_ufp6(SETS *set, FILE *fp);
/**
 * @paragraph Free Linked List
 * @param arr - pointer to LL_WORDS_HOLDER
 */
void sets_struct_init_v2(SETS *set, int num_words);
/**
 * @paragraph Free Linked List
 * @param arr - pointer to LL_WORDS_HOLDER
 */
void calloc_col_word(char **mat_row, int col_words_size);
/**
 * @paragraph Free Linked List
 * @param arr - pointer to LL_WORDS_HOLDER
 */
void calloc_col_ufp6(int **mat_row, int col_words_size);
/**
 * @paragraph Free Linked List
 * @param arr - pointer to LL_WORDS_HOLDER
 */
void read_ufp6_file_to_set(SETS *set, FILE *fp);

int main_functions_2(int argc , char **argv);

#endif //PROJETO_AED1_LP1_FUNCTIONS_2_H
