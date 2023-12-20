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
 * @paragraph free memory allocated from set
 * @param set - pointer to SET struct
*/
void freemem(SETS *set);
/** msdRadixSort
 * @paragraph Sort both matrix and matrix_ufp6 in alphabetical order (ASC and DESC)
 * using MSD algorithm
 * Time complexity: O(2 W(N+R))
 * R = Radix, N number of strings,
 * W max number of chars in single word
 * Extra Space: O(2N + DR)
 * 2N = both aux arrays of size N, R = count array with size R to store char cumulative
 * frequencies and D is the number of function-call stack depth
 * (length of longest prefix match)
 * @param set - pointer to SET struct
 * @param lo -  lower bound of matrix
 * @param hi - higher bound of matrix
 * @param flag - boolean, if set to 1 sort in ASC order , if set to 0 sort in DESC order
 */
void msdRadixSort(SETS *set,const int *array_sizes_ufp6, int lo, int hi, bool flag);
/**
 * @paragraph MSD algorithm , partition array into R pieces according to first char
 * (use Key_indexed countin) and after recursively sort all strings that start with
 * each char .
 * @param set - pointer to SET struct
 * @param aux - char pointers array to store sorted strings
 * @param array_sizes_ufp6 - int pointers array to store sorted ufp6 and
 * @param lo -  lower bound of matrix
 * @param hi - higher bound of matrix
 * @param d - depth of
 * @param flag - boolean, if set to 1 sort in ASC order , if set to 0 sort in DESC order
 */
void msdRadixSort_r(SETS *set,char **aux,int **aux_ufp6,const int *array_sizes_ufp6, int lo, int hi, int d, bool flag);
/**
 * @paragraph Sort both matrix and matrix_ufp6 by words size (in ASC and DESC order)
 * using quicksort algorithm
 * @param set - pointer to set struct
 * @param flag -boolean, if set to 1 sort in ASC order, if set to 0 sort in DESC order
 */
void sort_size(SETS *set,bool flag);
/**
 * @paragraphThis Quick sort algorithm to sort both matrix and matrix_ufp6,
 * it uses divide and conquer strategy like merge sort,
 * we first shuffle the array using Knuth-Shuffle algorithm
 * then we partition the array so that for pivot,
 * entry a[pivot] is in place , no larger entry to the left of pivot
 * and no smaller entry to the right of pivot
 * and then sort each subarray recursively
 * For tiny sub-arrays use insertion sort (CUTOFF = 10) , because qsort
 * has too much overhead for tiny sub-arrays
 * Time Complexity: worst O(1/2N^2)
 * Extra Space: O(log(N))
 * Not stable
 * @param set - pointer to set struct
 * @param arr - pointer to array with words size
 * @param lo - start pos of low = 0
 * @param hi - start pos of hi =  number of rows - 1
 */
void q_sort(SETS *set,int *arr, int lo , int hi, bool flag);
/**
 * @paragraph This function is used in quicksort algorithm,
 * to partition the array in half , so when pivot is changed
 * on his left are the numbers lower than him and at his left are the number greater
 * than pivot so pivot is already sorted
 * @param set - pointer to set struct
 * @param arr - pointer to array with words size
 * @param lo - start pos of low = 0
 * @param hi - start pos of hi =  number of rows - 1
 */
int partition(SETS *set,int *arr, int lo, int hi, bool flag);
/**
 * @paragraph Find median between arr[lo], arr[mid] and arr[hi]
 * to improve qsort
 * @param arr - pointer to array with words size
 * @param lo - lower bound = 0
 * @param mid - middle index of array
 * @param hi -  higher bound
 * @return return index of median
 */
int findMedian(const int *arr, int lo, int mid, int hi);
/**
 * @paragraph This function implements the Knuth-shuffle algoritm,
 * it shuffles the array generating random indexes and swap elements between those index
 * , for better performance in qsort algorithm
 * @param arr - pointer to array with words size
 * @param N - size of array
 */
void knuth_shuffle(int *arr, int N);
/**
 * @paragraph Exchange items between arr[i] and arr[j]
 * @param arr - pointer to int array
 * @param i - index of item to be swapped with item j
 * @param j - index of item to be swapped with item i
 */
void exch(int *arr, int i, int j);
/**
 * @paragraph Function to pre-compute dictionary with ufp6 representations of
 * each char
 * @param ufp6_dict - Matrix to store ufp6 representations of each char
 * @param size_ufp6 - pointer to int array to store ufp6
 * representation sizes of each char
 */
void ufp6_dictionary(int ufp6_dict[][BITS], int *size_ufp6);
/**
 * @paragraph Function to print UFP6 pre-computed dictionary
 * @param ufp6_dict - Matrix to store ufp6 representations of each char
 * @param size_ufp6 - pointer to int array with sizes of each char in ufp6
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
 * @paragraph Search function to search for a pattern in matrix of words in SETS
 * @param set - pointer SETS struct
 * @param dfa - Deterministic finite state automaton (abstract string-searching
 * machine)
 * @param word_size - size of word to be searched
 * @return returns an array with indexes of words found in matrix,
 * in the first pos of array it's stored the number of words (indexes) found
 */
int *search_KMP(SETS *set, int dfa[MAX_UFP6][BITS], int word_size);
/**
 * @paragraph Print DFA
 * @param dfa - Deterministic finite state automaton (abstract string-searching
 * machine)
 */
void print_kmp(int dfa[MAX_UFP6][M_KMP]);
/**
 * @paragraph Print all found words with pattern given an array with the indexes of rows that contain that pattern
 * @param set - pointer SETS struct that contains the array with all the words
 * @param array_index - pointer to an array with found words indexes (rows indexes) in first pos of array
 * store the number of words
 */
void print_found_words_and_ufp6(const SETS *set,const int *array_index);
/**
 * @paragraph Search for words with given pattern from a SETS struct by using KMP algorithm
 * This function has Time Complexity of O(W (M + N))
 * M = length of longest pattern N = number of rows (words in set) W = number of words to search for
 * @param set - pointer to SETS struct
 * @param words - pointer to an array of patterns to be searched
 * @param W - number of patterns to search
 * @param fn - file name
 * @param flag - if set to 1 write to a txt file words found with given pattern
 */
void find_Words(const SETS *set, const char **words, int W,const char *fn, bool flag);
/**
 * @paragraph Remove word from set, given array with the indexes of the rows in both matrix, adjusting
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
 * @paragraph Find all occurrences of given pattern in set and store indexes in array_index
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
 * @param flag -boolean, if set to 1 calculate in ASC order , if set to 0 calculate in DESC order
 * @return return the calculated index in UFP6 codification
 */
int calculate_index_char(char currentChar, bool flag);
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
/**
 * @paragraph Exchange the pointer to row i with the pointer to row j in matrix_words
 * @param set - pointer to SETS struct
 * @param i - index of a row to swap
 * @param j - index of a row to swap
*/
void exch_rows_matrix_char(SETS *set, int i, int j);
/**
 * @paragraph Exchange the pointer to row i with the pointer to row j in matrix_ufp6, and exchange sizes store in arr_ufp6_size
 * @param set - pointer to SETS struct
 * @param i - index of a row to swap
 * @param j - index of a row to swap
*/
void exch_rows_matrix_ufp6(SETS *set, int i, int j);
/**
 * @paragraph Exchange the pointer to row i with the pointer to row j in both matrix,
 * and exchange sizes stored in arr_ufp6_size,(no realloc needed)
 * @param set - pointer to SETS struct
 * @param i - index of a row to swap
 * @param j - index of a row to swap
*/
void exch_rows_from_both_matrix(SETS *set, int i, int j);
/**
 * @paragraph This function sorts matrix of words and ufp6 in SETS struct,
 * using insertion sort
 * Time complexity: O(N^2)
 * Extra Space: O(1)
 * @param set - pointer to SETS struct
 * @param N - size of rows
 * @param flag -boolean, if set to 1 sort in ASC order, if set to 0 sort in DESC order
*/
void insertion_sort_char(SETS *set, int N,bool flag);
/**
 * @paragraph This function checks if matrix_words is sorted
 * by alphabetical order
 * @param set - pointer to SETS struct
 * @param N - size of rows
 * @param flag - boolean, if set to 1 check if sorted ASC, if set to 0 check if DESC
*/
void is_sorted_matrix(const SETS *set, int N, bool flag);
/**
 * @paragraph This function checks if matrix_words is sorted
 * by words size
 * @param set - pointer to SETS struct
 * @param N - size of rows
 * @param flag -boolean,  if set to 1 check if sorted ASC, if set to 0 check if DESC
*/
void is_sorted_sizes(const SETS *set, int N, bool flag);



int main_functions_1(int argc , char **argv);


#endif //PROJETO_AED1_LP1_FUNCTIONS_1_H
