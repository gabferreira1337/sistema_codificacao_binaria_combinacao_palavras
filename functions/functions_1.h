#ifndef PROJETO_AED1_LP1_FUNCTIONS_1_H
#define PROJETO_AED1_LP1_FUNCTIONS_1_H

#include <stdbool.h>

#define BITS 7
#define MAX_UFP6 63
#define RADIX 63
#define M_KMP 8


/**
 * sets struct
 */
typedef struct{
    char **matrix;              /// matrix with words
    int **matrix_ufp6;          /// matrix with ufp6 representations
    int *arr_word_size;         /// arr with number of cols from each row on matrix
    int *arr_ufp6_size;         /// arr with number of cols from each row on matrix_ufp6
    int rowsize;                /// number of words in both matrix (number of rows)
    int colsize_encode;
}SETS;

void sets_struct_init(SETS *set, int number_words);

/**
 * @paragraph Encode the words from an array located in the set struct
 * @param set - pointer to SETS struct
 */
void encode(SETS *set);

/**
 * @paragraph generates random char
 * @return  generated char
 */
char gen_rnd_char();
/** Initialize matrix with random words generated
 * @params length - word length
 * @return  word generated
 */
void matrix_rnd_char_gen(SETS *set);
/**  initialize matrix of ints to 0
 * @params
 *
 */
int **matrix_init_int(int row ,int col);
/**  initialize matrix of char to 0
 * @params
 *
 */
char **matrix_init_char(int row ,int *size_cols);

/**  initialize the array that contains sizes of words
 * @params
 *
 */

void init_arr_word_size(SETS *set);

/**  print matrix
 * @params
 *
 */
void print_matrix_int(const SETS *set);
/**  random word size generator
 * @params
 *
 */
void rnd_word_size_gen(int *arr, int W);

/**  insert word into matrix char
 * @params
 *
 */
void insert_word_char(SETS *set,char *word,int index);
/** remove the a word from the matrix
 * @params
 *
 */

void remove_word_matrix(SETS *set, int row);
/** remove the a word from the matrix
 * @params
 *
 */
void insert_ufp6(SETS *set, const int sizes_ufp6_dict[], int ufp6_dict[][BITS], const char *word, int index);

/** realloc matrixes
 * @params
 *
 */
void matrix_realloc(SETS *set);
/** free memory allocated
 * @params
 *
 */
void FillArray_Word_Size(SETS *set);

/** Realloc mem on encode when we insert a new word
 * @params
 *
 */

void matrix_encode_realloc(SETS *set);
/**
 * @paragraph insert words and their ufp6 representation at the end of both matrix
 * this function reallocates the memory for both arrays holding the sizes of words and their ufp6
 * representation , calculates the new words size and ufp6 and after reallocates
 * also both matrix (matrix of words and matrix upf6) and then insert to the respective matrix.
 * @param set - pointer to set that contains both matrix , both arrays with sizes and the number of words
 * @param words - array of words to be inserted
 * @param sizes_ufp6_dict - array with precomputed sizes of each ufp6 representation
 * @param ufp6_dict - precomputed dictionary with each ufp6 representation
 * @param num_words - number of words to be inserted
 */
void insert_words(SETS *set, const char **words, const int *sizes_ufp6_dict, int ufp6_dict[][BITS], int num_words);

/** print the size of the words
 * @params
 *
 */

void print_arr_word_size(const SETS *set);

/** print matrix
 * @params
 *
 */
void print_matrix_char(const SETS *set);
void calc_ufp6_size(SETS *set, int index, char *word, const int *sizes_ufp6);
int *arr_bits_size_calloc(int *arr, int N);

/** free memory allocated
 * @params
 *
 */
void freemem(SETS *set);
/** msdRadixSort
 * @param set -
 * @param lo -
 * @param hi -
 * @param flag - flag can only hold
 * @return
 */
int msdRadixSort(SETS *set, int lo, int hi, bool flag);
// small columns ///
void msdRadixSort_r(SETS *set,char **aux, int lo, int hi, int d, bool flag);
void reverseArray(char **arr, int start, int end);
/** Create a dictionary of binary conversions of our ASCII table
* @params
*
*/
void ufp6_dictionary(int bin_dict[][BITS], int *size_bin);
void print_ufp6_dictionary(int bin_dict[][BITS], int *size_ufp6);
/** Pre process all ASCII conversions
* @params
*
*/
void encode_matrix_words(SETS *set, int sizes_ufp6_dict[], int ufp6_dict[][BITS]);

void charToBinary(int c, int *result, int *size_bin);

int fperror(char *message);

void encode_word(const char* word, int *encode,int *word_bits_size,int k,const int sizes_bin[],const int bin_dict[MAX_UFP6][BITS]);

void print_array(int *arr, int N);

void calculate_bin_sizes(char *word, int *arr_bin_sizes,int *words_bin_sizes, int N, int w);

int write_matrix_char_txt(char **mat,int r , int *cols, char *filename);


void KMP(char pattern[BITS], int dfa[MAX_UFP6][BITS]);

int *search_KMP(SETS *set, int dfa[MAX_UFP6][BITS], int word_size);

void print_kmp(int dfa[MAX_UFP6][M_KMP]);

void print_found_words_and_ufp6(SETS *set, int *array_index);


int *find_Word(SETS *set,const char **words,const int *array_found_words_index, int W);

void remove_Word(SETS *set, int *arr_words);

void realloc_row_delete(SETS *set, int row);
void realloc_row_add(SETS *set, int row);
void compute_words_size(const char **words,int *words_index, int W);
void realloc_arr_words_size(SETS *set);
void realloc_arr_ufp6_size(SETS *set);
void realloc_rows_matrix(SETS *set, int num_words);
void realloc_rows_ufp6(SETS *set, int num_words);

void realloc_col_word(char **mat_row, int col_words_size);
void realloc_col_ufp6(int **mat_row, int col_words_size);

int calculate_index_char(char currentChar);
/**
 * @paragraph Check if word is supported in UFP6
 * @param word -pointer to word to be checked
 * @return return 1 if word is supported or return 0 if word is not supported
 */
int is_ufp6(char *word);

void seed_random();


int main_functions_1(int argc , char **argv);


#endif //PROJETO_AED1_LP1_FUNCTIONS_1_H
