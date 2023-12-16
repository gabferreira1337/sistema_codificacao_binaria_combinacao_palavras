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

/**
 * @paragraph Inicialize the struct set by calling other functions
 * @param set - pointer to SETS struct
 * @param number_words - number of words
 */
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
/**
 * @paragraph Initialize matrix with random words generated
 * @param set - pointer to SETS struct
 */
void matrix_rnd_char_gen(SETS *set);
/**
 * @paragraph Allocate memory for an int array of pointers (rows) and for each pointer (cols), initialize at 0
 * @param row - amount of rows to allocate
 * @param col - amount of columns to allocate
 */
int **matrix_init_int(int row ,int col);

/**
 * @paragraph Allocate memory for an char array of pointers (rows) and for each pointer (cols)
 * @param row - amount of rows to allocate
 * @param size_cols - amount of columns to allocate
*/
char **matrix_init_char(int row ,int *size_cols);

/**
 * @paragraph Allocates memory to the array arr_word_size
 * @param set - pointer to set which contains both matrix , both arrays with sizes and the number of words
*/
void init_arr_word_size(SETS *set);

/**
 *  @paragraph Prints the UFP6 codification in a set using iteration
 *  @param set - pointer to set which contains both matrix , both arrays with sizes and the number of words
*/
void print_matrix_int(const SETS *set);

/**
 * @paragraph Generates a random word size, in order to auto fill the dynamic array with some words
 * @param arr - array that stores the size of each word
 * @param W - number of words to generate
 */
void rnd_word_size_gen(int *arr, int W);

/**
 * @paragraph
 * @param set - pointer to SETS struct which contains matrix holding words and arr_word_size
 * with the size of each word
 * @param word - pointer to an a givewordindex where the word is located
 * @param index - index where the given word is going to be inserted
 */
void insert_word_char(SETS *set,const char *word,int index);

/**
 * @paragraph
 * @param set - pointer so SETS struct with
 * @param sizes_ufp6_dict -
 * @param word - pointer to given word to encode
 * @param index - index of word
*/
void insert_ufp6(SETS *set, const int sizes_ufp6_dict[], int ufp6_dict[][BITS], const char *word, int index);

/**
 * @paragraph Reallocate memory for an char array of pointers (rows) and for each pointer (cols)
 * @param set - pointer to SETS struct which contains matrix to reallocate
*/
void matrix_realloc(SETS *set);

/**
 * @paragraph Uses iteration to fill the arr_word_size with the stored words size
 * @param set - pointer to SETS struct which contains array to fill
*/
void FillArray_Word_Size(SETS *set);

/**
 * @paragraph Reallocate memory for an int array of pointers (rows) and for each pointer (cols), initialize at 0
 * @param set - pointer to SETS struct which contains array to reallocate
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
/**
 * @paragraph Print the size of all words
 * @param set - pointer to SETS struct that contain the array to print
*/
void print_arr_word_size(const SETS *set);

/**
 * @paragraph Print every single word
 * @param set - pointer to SETS struct that contain the array to print
*/
void print_matrix_char(const SETS *set);

/**
 * @paragraph
 * @param set -
 * @param index -
 * @param word -
 * @param sizes_ufp6 -
*/
void calc_ufp6_size(SETS *set, int index,const char *word, const int *sizes_ufp6);

/**
 * @paragraph
 * @param arr -
 * @param N -
 * @return
*/
int *arr_bits_size_calloc(int *arr, int N);

/**
 * @paragraph free memory allocated
 * @param set -
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

/**
 * @paragraph
 * @param set -
 * @param aux -
 * @param lo -
 * @param hi -
 * @param d -
 * @param flag -
 */
// small columns ///
void msdRadixSort_r(SETS *set,char **aux, int lo, int hi, int d, bool flag);
/**
 * @paragraph
 * @param arr -
 * @param start -
 * @param end -
 */
void reverseArray(char **arr, int start, int end);
/**
 * @paragraph
 * @param bin_dict -
 * @param size_bin -
 */
void ufp6_dictionary(int bin_dict[][BITS], int *size_bin);
/**
 * @paragraph
 * @param bin_dict -
 * @param size_ufp6 -
 */
void print_ufp6_dictionary(int bin_dict[][BITS], int *size_ufp6);
/**
 * @paragraph
 * @param set - pointer SETS struct
 * @param sizes_ufp6_dict -
 * @param ufp6_dict -
 */
void encode_matrix_words(SETS *set, int sizes_ufp6_dict[], int ufp6_dict[][BITS]);
/**
 * @paragraph
 * @param c -
 * @param result -
 * @param size_bin - pointer to an array with pre-computed sizes_uf6
 */
void charToBinary(int c, int *result, int *size_bin);
/**
 * @paragraph Print a message and exit the application
 * @param message - message to print
 */
void fperror(char *message);
/**
 * @paragraph Function to encode a given word using the pre-computed ufp6_dictionary and the sizes_ufp6
 * @param word - pointer to a given word
 * @param encode - pointer to a row in the matrix_ufp6 array
 * @param word_bits_size - pointer to an array of word_ufp6_sizes
 * @param k - index of matrix row
 * @param sizes_ufp6 - pointer to an array with pre-computed sizes_ufp6
 * @param ufp6_dict - pointer to a matrix (dictionary) with each ufp6 representation
 */
void encode_word(const char* word, int *encode, int *word_bits_size, int k, const int sizes_ufp6[], const int ufp6_dict[][BITS]);
/**
 * @paragraph Not implemented
 * @param word -
 * @param arr_bin_sizes -
 * @param words_bin_sizes -
 * @param N -
 * @param w -
 */
void calculate_bin_sizes(char *word, int *arr_bin_sizes,int *words_bin_sizes, int N, int w);
/**
 * @paragraph KMP Algorithm to build DFA of a patter (word)
 * @param pattern -pointer to pattern (word) to be found
 * @param dfa -pointer to Deterministic Finite State Automaton (abstract string-searching
 * machine)
 */
void KMP(const char pattern[BITS], int dfa[MAX_UFP6][BITS]);
/**
 * @paragraph
 * @param set - pointer SETS struct
 * @param dfa - Deterministic finite state automaton (abstract string-searching
 * machine)
 * @param word_size - size of word
 * @return
 */
int *search_KMP(SETS *set, int dfa[MAX_UFP6][BITS], int word_size);
/**
 * @paragraph Print DFA
 * @param dfa - Deterministic finite state automaton (abstract string-searching
 * machine)
 */
void print_kmp(int dfa[MAX_UFP6][M_KMP]);
/**
 * @paragraph Print all the found words
 * @param set - pointer SETS struct that contains the array with all the words
 * @param array_index - pointer to an array with found words index
 */
void print_found_words_and_ufp6(const SETS *set,const int *array_index);
/**
 * @paragraph Remove specific words from a SETS struct by using KMP
 * @param set - pointer to SETS struct that contains the arrays where the words are stored
 * @param words - pointer to an the array of words which contain the words to be removed
 * @param W - amount of words to remove
 */
void find_Words(SETS *set, const char **words, int W);
/**
 * @paragraph Remove words from set, given array with the indexes of the rows in both matrix, adjusting
 * both matrix .When adjusting rows If prev word size is lesser than the next, reallocate that row
 * @param set - pointer to SETS struct
 * @param arr_index_words_found - pointer to an array of index, pos 0 has the number of words (indexes) found
 */
void remove_Word(SETS *set,const int *arr_index_words_found);
/**
 * @paragraph Remove given words from set, adjusting both matrix and matrix_ufp6 rows from set
 * @param set - pointer to SETS struct
 * @param words - pointer to an array of words
 * @param W - number of words to remove
 */
void remove_Words(SETS *set,const char **words, int W);
/**
 * @paragraph Find all occurrences of given word in set and store indexes in array_index
 * @param set - pointer to SETS struct
 * @param array_index - pointer to a pointer to array_index
 */
void find_Word(SETS *set,const char *word, int **array_index);
/**
 * @paragraph Remove given UFP6 from set, adjusting rows in matrix_ufp6 from set
 * @param set - pointer to SETS struct
 * @param index - index of ufp6 representation to be removed
 */
void remove_UFP6(SETS *set,int index);
/**
 * @paragraph Reallocates the size of row if the new word is greater than the one that we want to remove
 * @param set - pointer to SETS struct that contains all the words and the array with the size of all of them
 * @param row - index of the row to be  removed
*/
void realloc_row_remove(SETS *set, int row);

/**
 * @paragraph Calculates the size of W words and places the result in the array words_index
 * @param words - array with the words
 * @param words_index -pointer to an array that will contain the sizes of words
 * @param W - number of words
 */

void compute_words_size(const char **words,int *words_index, int W);

/**
 * @paragraph Reallocates memory for an array of ints that contains the size of each word
 * @param set - pointer to SETS struct where our array is located so we can realloc
 */
void realloc_arr_words_size(SETS *set);

/**
 * @paragraph Reallocates memory for an array of ints that contains the size of each  UFP6 representation
 * @param set - pointer to SETS struct where our array is located so we can realloc
 */

void realloc_arr_ufp6_size(SETS *set);
/**
 * @paragraph Reallocates memory, called inside insert_words as we need to reallocate in order
 * to have the correct amount of rows in the matrix to the new word(s)
 * @param set - pointer to SETS struct where our matrix is located so we can realloc its rows
 * @param num_words - current amount of words, so we reallocate to the necessary amount of memory
 */
void realloc_rows_matrix(SETS *set, int num_words);
/**
 * @paragraph Reallocates memory, called inside insert_words as we need to reallocate in order
 * to have the correct amount of rows in the matrix to hold new word(s) codification(s)
 * @param set - pointer to SETS struct where our matrix is located so we can realloc it's rows
 * @param num_words - current amount of words, so we reallocate to the necessary amount of memory
 */
void realloc_rows_ufp6(SETS *set, int num_words);
/**
 * @paragraph Reallocates memory for a column where chars are stored, uses the size of the word
 * @param mat_row - pointer to an row to realloc
 * @param col_words_size - size of word, used to realloc
 */
void realloc_col_word(char **mat_row, int col_words_size);
/**
 * @paragraph Reallocate memory for a row in the matrix with UFP6 representation, given the size of a word
 * @param mat_row - pointer to an row to realloc
 * @param col_words_size - size of word, used to realloc
 */
void realloc_col_ufp6(int **mat_row, int col_words_size);

/**
 * @paragraph - Calculate char index in UFP6 codification
 * @param currentChar - char to calculate
 * @return return the calculated index in UFP6 codification
 */
int calculate_index_char(char currentChar);
/**
 * @paragraph Check if word is supported in UFP6
 * @param word -pointer to word to be checked
 * @return return 1 if word is supported or return 0 if word is not supported
 */
int is_ufp6(const char *word);
/**
 * @paragraph Function to create a sed based on processor time
 */
void seed_random();


int main_functions_1(int argc , char **argv);


#endif //PROJETO_AED1_LP1_FUNCTIONS_1_H
