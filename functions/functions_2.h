#ifndef PROJETO_AED1_LP1_FUNCTIONS_2_H
#define PROJETO_AED1_LP1_FUNCTIONS_2_H

#include <time.h>
#include "functions_1.h"


typedef struct{
    SETS s1;        ///Set with matrix of words and their UFP6 representation
    SETS s2;

}WORDS_HOLDER;


typedef struct{
    WORDS_HOLDER words_holder;  ///Copy of WORDS_HOLDER
    char *last_update_date;     ///String containing last update date of WORDS_HOLDER

}VAL_AD_WORDS_HOLDER;

///Dynamic array of VAL_AD_WORDS_HOLDER
typedef struct{
    int size;                   /// Size of Dynamic array
    int count;                  /// Number of elements in Dynamic array
    VAL_AD_WORDS_HOLDER *array_val;     /// array of VAL_AD_WORDS_HOLDER

}AD_WORDS_HOLDER;


typedef struct node_ll_words_holder{
    WORDS_HOLDER words_holder;          ///Copy of WORDS_HOLDER
    char *last_update_date;             ///String containing last update date of WORDS_HOLDER
    struct node_ll_words_holder *pnext; /// Pointer to next node
    struct node_ll_words_holder *pback; /// Pointer to previous node

}NODE_LL_WORDS_HOLDER;

///Linked List of NODE_LL_WORDS_HOLDER
typedef struct ll_words_holder{
   int nnodes;                          /// Number of nodes in Linked List
   NODE_LL_WORDS_HOLDER *phead;         /// Pointer to head of Linked List
   NODE_LL_WORDS_HOLDER *ptail;         /// Pointer to tail of Linked List

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
 * @paragraph Print dynamic array
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
void insert_element_to_AD_in_order(AD_WORDS_HOLDER *ad_holder,const SETS *s1 ,const SETS *s2,const char *last_date);
/**
 * @param ad_holder - pointer to AD_WORDS_HOLDER struct
 * @param index_set1 - pointer to array with index of words found in set1 ///in first position of array store the count of indexes to use inside this function
 * @param index_set2 - pointer to array with index of words found in set2 ///in first position of array store the count of indexes to use inside this function
 * @param index_ad - index of ad where we found the words
 */
void print_words_found(AD_WORDS_HOLDER *arr,int *index_set1, int *index_set2, int index_ad);
//int *find_Word_index(&arr->array_val[j].words_holder.s1,words[i], index_set1, 1);
/**
 * @paragraph Insert element in dynamic array at given index , if dynamic array if full or if want to
 * insert at position equal or greater than DA size, double the size of array
 * if ad is full doubles the size of ad
 * @paragraph This function shifts elements to insert new element at the given index and fill VAl_AD_WORDS_HOLDER
 * with the values passed to the function
 * @paragraph Time complexity : O(2N + D)) ,
 * Shifting elements O(N) , realloc O(N) , insertion O(1), strcpy date O(D)
 * D = date size N = size of elements in dynamic array
 * Extra space : O(1) (inplace)
 * @param ad_holder - pointer to AD_WORDS_HOLDER
 * @param set1 - pointer to set of matrix with words and ufp6
 * @param set2 - pointer to set of matrix with words and ufp6
 * @param last_date - last update date of both sets
 * @param index - index where new element should be added in the Dynamic array
 */
void insert_element_to_index_AD(AD_WORDS_HOLDER *ad_holder,const SETS *set1,const SETS *set2,const char *last_date, int index);
/**
 * @paragraph Find words and respective UFP6 ,only at given indexes of Dynamic array,
 * and write to a txt file the output
 * Time Complexity: O(W * A * N + M)
 * W = size of words to search for in dynamic array A = size of elements in da to search for words
 * N = size of words in set1 , M =  size of words in set2
 * Extra Space: O(N + M)
 * N = size of words in set1 , M =  size of words in set2
 * @param arr - pointer to AD_WORDS_HOLDER
 * @param words - pointer to an array of pointers to strings containing the words to be found
 * @param W - size of words to find
 * @param start_index - first index of Dynamic array to search for each word
 * @param end_index - last index of Dynamic array to search for each word
 * @param fn - pointer to string containing filename
 * @param flag - if set to 1 output to a txt file words found and their respective UFP6 representations
 */
void find_words_ad(const AD_WORDS_HOLDER *arr, const char **words, int W, int start_index, int end_index, const char *fn, bool flag);
/**
 * @paragraph Find word and respective UFP6 ,only at given indexes of Dynamic array
 * Time Complexity: O(N)
 * Extra Space: O(N)
 * N = size of words in set
 * @param set - pointer to SETS struct
 * @param word - pointer to a string containing the word to be found
 * @return if word is found in set return a pointer to an array containing the index of rows containing each word from given set and index
 * of Dynamic array and at pos 0 it stores the size of indexes stored in array
 * If the word is not found, return a pointer to NULL
 */
int *search_word(const SETS *set,const char *word);
/**
 * @paragraph Check if is a valid date
 * @param date_str - pointer to string holding date
 * @return  -
 */
int is_valid_date(const char *date_str);

/**
 * @paragraph Insert data to VAL_AD_WORDS_HOLDER
 * @param val_ad_words_holder -
 * @param set1 -
 * @param set2 -
 * @param last_date -
 */
void insert_to_VAL_AD_WORDS_HOLDER(VAL_AD_WORDS_HOLDER *val_ad_words_holder,const SETS *set1,const SETS *set2,const char *last_date);
/**
 * @paragraph Function to get current date and return the date
 * @return current date ex: "21/09/2023"
 */
char *get_current_date();
/**
 * @paragraph Function to search for the position in AD to insert new element
 * using binary search
 * @param arr_din - pointer to AD_WORDS_HOLDER
 * @param date - new_date of the element we want to insert
 * @return lo - if found target it returns the position of target in dynamic array
 * if target is not found returns the position where should be added
 * example1: index 0 24-11-2023 index 1 26-11-2023 , new_date 25-11-2023 - returns 1
 * example2: index 0 24-11-2023 , new_date 23-11-2023 return   0
 * example3: index 0 24-11-2023 , new_date 25-11-2023 return   1
 */
int bin_search_insert_pos(const AD_WORDS_HOLDER *arr_din,const char *date);
/**
 * @paragraph Delete element from Dynamic array by shifting the elements,
 * if dynamic array is one-quarter full halve the size
 * @param ad - pointer to AD_WORDS_HOLDER
 * @param index - index of Dynamic Array to remove element
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
 * @paragraph Initialize and return LL_WORDS_HOLDER struct
 * @return pointer to dynamically allocated LL_WORDS_HOLDER struct
 */
LL_WORDS_HOLDER *ll_init();
/**
 * @paragraph Free Linked List
 * @param arr - pointer to LL_WORDS_HOLDER
 */
void free_ll_words_holder(LL_WORDS_HOLDER *ll);
/**
 * @paragraph Create new node given 2 SETS and last update date and return it
 * @param set1 - pointer to SETS struct
 * @param set2 - pointer to SETS struct
 * @param last_date - pointer to string containing the last update date
 * @return pointer to new node
 */
NODE_LL_WORDS_HOLDER *create_words_holder_node(const SETS *set1,const SETS *set2,const char *last_date);
/**
 * @paragraph Insert node into LL in chronological order by last modified date
 * in DESC order
 * Time Complexity: O(N) N = size of nodes in LL
 * Extra space: O(1)
 * @param ll - pointer to LL_WORDS_HOLDER
 * @param set1 - pointer to SETS struct
 * @param set2 - pointer to SETS struct
 * @param last_date - pointer to string containing the last update date
 */
void insert_node_ll_sorted(LL_WORDS_HOLDER *ll,const SETS *set1,const SETS *set2,const char *last_date);
/**
 * @paragraph Insert node into LL at given index
 * Time Complexity: O(N - 1) N = size of nodes in LL
 * Extra space: O(1)
 * @param ll - pointer to LL_WORDS_HOLDER
 * @param set1 - pointer to SETS struct
 * @param set2 - pointer to SETS struct
 * @param last_date - pointer to string containing the last update date
 * @param index - index to insert new node
*/
void insert_node_ll_index(LL_WORDS_HOLDER *ll,const SETS *set1,const SETS *set2,const char *last_date, int index);
/**
 * @paragraph Print Linked List
 * @param ll - pointer to Linked List LL_Words_Holder
 */
void print_ll_words_holder(LL_WORDS_HOLDER *ll);
/**
 * @paragraph Insert to LL new node given pointer to curr and prev nodes
 * @param ll - pointer to Linked List Words Holder
 * @param set1 - pointer to SETS struct
 * @param set2 - pointer to SETS struct
 * @param last_date - pointer to string containing
 * @param curr - pointer to current node
 * @param prev - pointer to previous node
 */
void insert_to_ll_given_pointers_node(LL_WORDS_HOLDER *ll, const SETS *set1, const SETS *set2, const char *last_date, NODE_LL_WORDS_HOLDER *curr, NODE_LL_WORDS_HOLDER *prev);
/**
 * @paragraph Find midpoint of Linked List using fast_ptr and slow_ptr
 * @param lo - pointer to lower node
 * @param hi - pointer to higher node
 * @return pointer to middle node
 */
NODE_LL_WORDS_HOLDER *find_mid_ll(NODE_LL_WORDS_HOLDER *lo, NODE_LL_WORDS_HOLDER *hi);
/**
 * @paragraph Delete node at a given position/index
 * Time Complexity: O(N - 1) N = size of nodes in LL
 * Extra Space: O(1)
 * @param ll - pointer to Linked List Words Holder
 * @param index - index of node in Linked List to be deleted
 */
void delete_ll_node_index(LL_WORDS_HOLDER *ll, int index);
/**
 * @paragraph search words and their respective ufp6 at given node using KMP algorithm
 * @param ll - pointer to Linked List Words Holder
 * @param words - array of words to search in LL
 * @param W - size of words array
 * @param lo - start index node
 * @param hi - end index node
 * @param fn - file name
 * @param flag - if set to 1 write output to a txt file
 */
void find_word_ll(const LL_WORDS_HOLDER *ll, char **words, int W, int lo, int hi,const char *fn, bool flag);
/**
 * @paragraph search words and their respective UFP6 representation
 * between given indexes of nodes
 * Time Complexity: O(W * L * N + M)
 * W = size of words to search for in dynamic array L = size of nodes in LL to search for words
 * N = size of words in set1 M = size of words in set2
 * Extra Space: O(N + M)
 * N = size of words in set1 , M =  size of words in set2
 * @param ll - pointer to Linked List Words Holder
 * @param words - array of words to search in LL
 * @param W - size of words array
 * @param start_index_node - start index node
 * @param end_index_node - end index node
 * @param fn - file name
 * @param flag - if set to 1 write output to a txt file
 */
void find_words_ll(const LL_WORDS_HOLDER *ll, const char **words, const char *fn, int W, int start_index_node, int end_index_node, bool flag);
/**
 * @paragraph Print words found in Linked List
 * @param ll - pointer to Linked List Words Holder
 * @param index_set1 - pointer to array holding the indices of rows from set1
 * and at pos 0 of array store the size of indices
 * @param index_set2 - pointer to array holding the indices of rows from set2
 * and at pos 0 of array store the size of indices
 * @param j - index of node
 */
void print_words_found_ll(NODE_LL_WORDS_HOLDER *ll, int  *index_set1, int *index_set2, int j);
/**
 * @paragraph Write set to txt file
 * Words set:
 * number_words = 5
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
void write_set_to_txt(const SETS *set,FILE *fp);
/**
 * @paragraph Write UFP6 representations to txt file
 *Format:
 *UFP6:
 *25 1 1 0 1 1 1 1 0 1 0 1 0 1 1 0 1 1 1 0 1 1 1 1 1 1
 *5 1 0 1 1 1
 *27 1 1 1 0 1 0 0 0 1 0 1 0 0 0 0 0 1 0 0 0 0 0 1 1 1 1 1
 *20 1 0 1 0 1 1 0 0 1 0 1 1 1 1 0 1 0 1 0 0
 *19 1 1 1 1 1 1 0 0 0 1 0 1 1 0 1 1 1 0 0
 * @param set - pointer to SETS struct
 * @param fp - file pointer to the file where data will be inserted
 */
void write_set_ufp6_to_txt(const SETS *set, FILE *fp);
/**
 * @paragraph Save set to txt file
 * @param s1 - pointer to SETS struct
 * @param filename - pointer to string containing the file name
 */
int save_set_txt(const SETS *set, char *filename);
/**
 * @paragraph Save 2 SETS to txt file
 * @param s1 - pointer to SETS struct
 * @param s2 - pointer to SETS struct
 * @param fp - file pointer to the file where data will be inserted
 */
void save_both_sets_to_txt(const SETS *s1, const SETS *s2, char *filename);
/**
 * @paragraph Write to a txt file words found in Linked list ,
 * with given arrays holding the indexes of all words found in each set at a given node,
 * and at pos 0 of both arrays store the count of words to use in this function
 * @param current - pointer to current NODE_LL_WORDS_HOLDER
 * @param index_set1 - pointer to array containing the indices of words found in set1 at given node from LL
 * and at pos 0 of array the size of indices
 * @param index_set2 - pointer to array containing the indices of words found in set2 at given node from LL
 * and at pos 0 of array the size of indices
 * @param filename - pointer to string containing filename
 * @param index_ll - index of LL (node) where words were found
 */
int write_words_found_in_ll_to_txt(const NODE_LL_WORDS_HOLDER *current, const int *index_set1, const int *index_set2, const char *filename, int index_ll);
/**
 * @paragraph Write to a txt file words found in dynamic array ,
 * with given arrays holding the indexes of all words found in each set at a given index
 * and at pos 0 of both arrays store the count of words to use in this function
 * @param val_ad - pointer to VAL_AD_WORDS_HOLDER
 * @param index_set1 - pointer to array containing the indices of words found in set1 at given index of dynamic array
 * @param index_set2 - pointer to array containing the indices of words found in set2 at given index of dynamic array
 * @param filename - pointer to string containing filename
 * @param index_ad - index of dynamic array where words were found
 */
int write_words_found_in_da_to_txt(const VAL_AD_WORDS_HOLDER *val_ad, const int *index_set1, const int *index_set2, const char *filename, int index_ad);
/**
 * @paragraph Write words found and UFP6 representation to txt file
 * given array holding indices of words
 * @param set - pointer to SETS struct
 * @param fp - file pointer
 * @param index_set1 - pointer to array containing the indices of words found in set at given index
 * and at pos 0 store the size of indices in array
 */
void write_index_array_words_to_file(const SETS *set,FILE *fp,const int *index_array);
/**
 * @paragraph Write to txt file UFP6 representation of words given array holding correspondent indices
 * of words in matrix
 * @param set - pointer to SETS struct
 * @param fp - file pointer
 * @param index_set1 - pointer to array containing the indices of words found in set at given index
 * and at pos 0 store the size of indices in array
 * @param r - row index of word in matrix from SETS struct
 */
void write_index_array_ufp6_to_file(const SETS *set,FILE *fp,const int *index_array, int r);
/**
 * @paragraph Read from txt file to set
 * @param set - pointer to SETS struct
 * @param fp - file pointer
 */
void read_txt_to_set(SETS *set, FILE *fp);
/**
 * @paragraph Read from txt file a set of words and their respective size
 * to SETS struct
 * @param set - pointer to SETS struct
 * @param fp - file pointer
 */
void read_txt_words(SETS *set, FILE *fp);
/**
 * @paragraph Initialise set while reading data from file
 * @param set - pointer to SETS struct
 * @param num_words - size of words in both matrix
 */
void sets_struct_init_v2(SETS *set, int num_words);
/**
 * @paragraph Allocate memory for n columns in a matrix row and initialize to NULL / 0
 * @param mat_row - pointer to row from matrix to allocate memory to store word
 * @param col_words_size - size of columns to be allocated
 */
void calloc_col_word(char **mat_row, int col_words_size);
void free_index_arrays(int *arr1, int *arr2);
/**
 * @paragraph Allocate memory for n columns in a matrix row and initialize to NULL / 0
 * @param mat_row - pointer to row from matrix UFP6 to allocate memory to store UFP6 representation
 * @param col_words_size - size of columns to be allocated
 */
void calloc_col_ufp6(int **mat_row, int col_words_size);
/**
 * @paragraph Read ufp6 from a txt file and insert to a given set
 * @param set - pointer to SETS struct
 * @param fp - file pointer
 */
void read_ufp6_file_to_set(SETS *set, FILE *fp);
/**
 * @paragraph Write Dynamic Array of VAL_AD_WORDS_HOLDER to txt file
 * File format:
 *Number of elements: 1
 *Index 0
 *Last Update Date: 2022-11-24
 *Words set: 1
 *number_words = 5
 *3-f o G
 *2-R Q
 *5-V U c f T
 *2-p Z
 *6-E a 5 0 D j
 *UFP6:
 *15-1 1 1 1 1 1 0 0 0 1 0 1 0 1 0
 *12-1 1 0 1 0 1 1 1 0 1 0 0
 *26-1 1 1 0 0 1 1 1 1 0 0 0 1 1 0 0 1 1 1 1 1 1 0 1 1 1
 *11-1 1 0 0 1 1 1 1 1 0 1
 *25-1 0 1 0 0 0 1 0 1 0 1 0 1 0 1 0 0 1 1 1 1 0 0 1 1
 * @param ad - pointer to AD_WORDS_HOLDER
 * @param fn - file name
 */
void write_ad_to_txt(const AD_WORDS_HOLDER *ad,const char *fn);
/**
 * @paragraph Write both sets from WORDS_HOLDER to txt file
 * @param wordsHolder - pointer to WORDS_HOLDER
 * @param fp - file pointer
 */
void write_both_sets_to_txt(const WORDS_HOLDER *wordsHolder, FILE *fp);
/**
 * @paragraph Read from txt file to Dynamic array AD_WORDS_HOLDER
 * File format:
 *Number of elements: 1
 *Index 0
 *Last Update Date: 2022-11-24
 *Words set: 1
 *number_words = 5
 *3-f o G
 *2-R Q
 *5-V U c f T
 *2-p Z
 *6-E a 5 0 D j
 *UFP6:
 *15-1 1 1 1 1 1 0 0 0 1 0 1 0 1 0
 *12-1 1 0 1 0 1 1 1 0 1 0 0
 *26-1 1 1 0 0 1 1 1 1 0 0 0 1 1 0 0 1 1 1 1 1 1 0 1 1 1
 *11-1 1 0 0 1 1 1 1 1 0 1
 *25-1 0 1 0 0 0 1 0 1 0 1 0 1 0 1 0 0 1 1 1 1 0 0 1 1
 * @param ad - address of a pointer to AD_WORDS_HOLDER
 * @param fp - file pointer
 * @param flag - if set to 1 read in chronological order ASC
 */
void read_from_txt_to_ad(AD_WORDS_HOLDER **ad,const char *fn, bool flag);
/**
 * @paragraph Write Linked List of NODE_LL_WORDS_HOLDER to txt file
 * File format:
 *Number of nodes: 1
 *Node 0
 *Last Update Date: 2024-01-15
 *Words set: 1
 *number_words = 5
 *3-n h m
 *2-p x
 *2-S 4
 *4-Y G 6 F
 *4-Z V Q d
 *UFP6:
 *15-1 0 1 1 1 1 0 0 0 1 1 0 1 1 0
 *11-1 1 0 0 1 1 0 0 0 0 1
 *9-1 1 0 1 1 0 1 0 0
 *21-1 1 1 1 0 0 1 0 1 0 1 0 1 1 0 1 0 1 0 0 1
 *22-1 1 1 1 0 1 1 1 1 0 0 1 1 1 0 1 0 0 1 1 0 1
 * @param ll - pointer to LL_WORDS_HOLDER struct
 * @param fn - file name
 */
void write_ll_to_txt(const LL_WORDS_HOLDER *ll,const char *fn);
/**
* @paragraph Write set of words and UFP6 representations to bin file
* @param set - pointer to SETS struct
* @param fp - file pointer
*/
void write_set_to_binfile(const SETS *set,FILE *fp);
/**
* @paragraph Write UFP6 representations to bin file
* @param set - pointer to SETS struct
* @param fp - file pointer
*/
void write_set_ufp6_to_binfile(const SETS *set, FILE *fp);
/**
 * @paragraph Write both sets from WORDS_HOLDER to bin file
 * @param wordsHolder - pointer to WORDS_HOLDER
 * @param fp - file pointer
 */
void write_both_sets_to_binfile(const WORDS_HOLDER *wordsHolder, FILE *fp);
/**
* @paragraph Write words found with given patter in set to txt
* @param set - pointer to SETS struct
* @param filename - pointer to string containing file name
* @param array_index_words_found_set - array holding indexes of words from set with
* pattern , in first pos of array it stores the size of words found
*/
void write_words_found_to_txt_set_with_pattern(const SETS *set, const int *array_index_words_found_set, const char *filename, const char *pattern);
/**
 * @paragraph Read from txt file to Linked List of NODE_LL_WORDS_HOLDER
 * File format:
 *Number of nodes: 1
 *Node 0
 *Last Update Date: 2024-01-15
 *Words set: 1
 *number_words = 5
 *3-n h m
 *2-p x
 *2-S 4
 *4-Y G 6 F
 *4-Z V Q d
 *UFP6:
 *15-1 0 1 1 1 1 0 0 0 1 1 0 1 1 0
 *11-1 1 0 0 1 1 0 0 0 0 1
 *9-1 1 0 1 1 0 1 0 0
 *21-1 1 1 1 0 0 1 0 1 0 1 0 1 1 0 1 0 1 0 0 1
 *22-1 1 1 1 0 1 1 1 1 0 0 1 1 1 0 1 0 0 1 1 0 1
 * @param ll - pointer to LL_WORDS_HOLDER
 * @param fp - file pointer
 * @param flag - if set to 1 read in chronological order DESC
 */
void read_from_txt_to_ll(LL_WORDS_HOLDER *ll,const char *fn, bool flag);
/**
 * @paragraph Read UFP6 and their respective size from .bin file to SETS struct
 * @param set - pointer to SETS struct
 * @param fp - file pointer
 */
void read_ufp6_binfile_to_set(SETS *set, FILE *fp);
/**
 * @paragraph Read from .bin file to Dynamic array AD_WORDS_HOLDER
 * @param ad - pointer to AD_WORDS_HOLDER
 * @param fp - file pointer
 * @param flag - if set to 1 read in chronological order ASC
 */
void read_from_bin_to_ad(AD_WORDS_HOLDER **ad,const char *fn, bool flag);
/**
 * @paragraph Write Dynamic array  to .bin file
 * @param ll - pointer to LL_WORDS_HOLDER struct
 * @param fn - file name
 */
void write_ad_to_bin(const AD_WORDS_HOLDER *ad,const char *fn);
/**
 * @paragraph Read data from .bin file to SETS struct
 * @param set - pointer to SETS struct
 * @param fp - file pointer
 */
void read_binfile_to_set(SETS *set, FILE *fp);
/**
 * @paragraph Read words and their respective size from .bin file to SETS struct
 * @param set - pointer to SETS struct
 * @param fp - file pointer
 */
void read_binfile_words(SETS *set, FILE *fp);
/**
 * @paragraph Write Linked List of NODE_LL_WORDS_HOLDER to .bin file
 * @param ll - pointer to LL_WORDS_HOLDER struct
 * @param fn - file name
 */
void write_ll_to_binfile(const LL_WORDS_HOLDER *ll,const char *fn);
/**
 * @paragraph Read data from .bin file and store in Linked List of NODE_LL_WORDS_HOLDER
 * @param ll - pointer to LL_WORDS_HOLDER
 * @param fpn- file name
 * @param flag - if set to 1 read in chronological order DESC
 */
void read_from_binfile_to_ll(LL_WORDS_HOLDER *ll,const char *fn, bool flag);



int main_functions_2(int argc , char **argv);

#endif //PROJETO_AED1_LP1_FUNCTIONS_2_H
