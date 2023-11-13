#ifndef PROJETO_AED1_LP1_FUNCTIONS_1_H
#define PROJETO_AED1_LP1_FUNCTIONS_1_H

#include <stdbool.h>

#define BITS 7

/**
 * sets struct
 */
typedef struct{

    char **matrix;
    int **matrix_encode;
    int *arr_word_size;         /// size of cols from each row
    int *arr_bits_size;
    int rowsize;
    int colsize_encode;

}SETS;



/**  encode a matrix of strings to UFP6 (binary)
 * @params
 *
 */
void encode(SETS *set);
/**  encode a matrix of strings to UFP6 (binary)
 * @params
 *
 */
void int_to_bin(SETS *set);
/**  encode a matrix of strings to UFP6 (binary)
 * @params
 *
 */
void char_to_bin(SETS *set);


/** generate random char
 * @params length - word length
 * @return  word generated
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
void print_matrix_int(SETS set);
/**  random word size generator
 * @params
 *
 */
void rnd_word_size_gen(int *arr, int W);

/**  insert word into matrix char
 * @params
 *
 */
void insert_word_char(SETS *set,int start_row,  int number_words);
/** remove the a word from the matrix
 * @params
 *
 */

void remove_word_matrix(SETS *set, int row);
/** remove the a word from the matrix
 * @params
 *
 */

void remove_word_matrix(SETS *set, int row);

/**  insert word into matrix short
 * @params
 *
 */
void insert_word_short(SETS *set, int start_row , int number_words);

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

/** print the size of the words
 * @params
 *
 */

void print_arr_word_size(SETS set);

/** print matrix
 * @params
 *
 */
void print_matrix_char(SETS set);

int *arr_bits_size(int *arr, int N);

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
 *
 */
int msdRadixSort(SETS *set, int lo, int hi, bool flag);
void msdRadixSort_r(SETS *set,char **aux, int lo, int hi, int d, bool flag);
void reverseArray(char **arr, int start, int end);
/** Create a dictionary of binary conversions of our ASCII table
* @params
*
*/
void binary_dictionary(int bin_dict[62][BITS + 1], int N,int *size_bin);
void print_binary_dictionary(int bin_dict[62][BITS + 1], int *size_bin);
/** Pre process all ASCII conversions
* @params
*
*/
void encode_matrix_words(SETS *set, int sizes_bin[],int bin_dict[62][BITS + 1]);
void charToBinary(int c, int *result, int *size_bin);
int fperror(char *message);
void encode_word( char* word, int *encode,int *word_bits_size,int k, int sizes_bin[],int bin_dict[62][BITS + 1]);
void print_array(int *arr, int N);

int write_matrix_char_txt(char **mat,int r , int *cols, char *filename);

int main_functions_1(int argc , char **argv);

#endif //PROJETO_AED1_LP1_FUNCTIONS_1_H
