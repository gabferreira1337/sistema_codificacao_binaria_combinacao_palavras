#ifndef PROJETO_AED1_LP1_FUNCTIONS_1_H
#define PROJETO_AED1_LP1_FUNCTIONS_1_H

#include <stdbool.h>

#define BITS 8           /// max size of words + '\0'
#define MAX_UFP6 62     ///Size of UFP6 ASCII
#define RADIX 62
#define M_KMP BITS     ///MAX_SIZE for KMP DFA columns


///sets struct
typedef struct{
    char **matrix;              /// matrix with words
    int **matrix_ufp6;          /// matrix with ufp6 representations
    int *arr_word_size;         /// arr with size of cols from each row on matrix
    int *arr_ufp6_size;         /// arr with size of cols from each row on matrix_ufp6
    int rowsize;                /// size of words in both matrix (size of rows)
}SETS;


///Hash table
typedef struct ufp6{
    char *ufp6_encode;      ///string holding UFP6 representation
    unsigned int size;    /// size of string without leading 0's
    int repeated;        ///boolean to check if equal combination , if so set to 1
    struct ufp6 *pnext;     /// pointer to next node
}UFP6;

///Struct to hold Hash table
typedef struct hashtable {
    int count;        /// number of elements in Hash table
    int size;        /// size of Hash table
    UFP6 **table;   /// Hash table
}HASHTABLE;



/**
 * @paragraph Initialize SETS struct
 * @param set - pointer to SETS struct
 * @param number_words - size of words to hold in set
 */
void sets_struct_init(SETS *set,const int *sizes_ufp6, int number_words);
/**
 * @paragraph generate random char from
 * '0' to '9' , 'a' to 'z' and 'A' to 'Z'
 * @return  generated char
 */
char gen_rnd_char();
/**
 * @paragraph Initialize matrix with random words generated
 * @param set - pointer to SETS struct
 */
void matrix_rnd_word_gen(SETS *set);
/**
 * @paragraph Initialize matrix with UFP6 representation of each word,
 * calculating the size of each representation to allocate exact size of columns
 * @param set - pointer to SETS struct
 * @param sizes_ufp6_char - pointer to pre-computed array with the size
 * of each UFP6 representation of each UFP6 char
 */
void matrix_ufp6_init(SETS *set,const int *sizes_ufp6_char);
/**
 * @paragraph Allocate memory for matrix to store words, given array with pre-generated sizes of each word
 * @param set - pointer to SETS struct
*/
void matrix_init_char(SETS *set);
/**
 * @paragraph Allocate memory to array arr_word_size in SETS struct
 * @param set - pointer to SETS struct
*/
void init_arr_word_size(SETS *set);
/**
 * @paragraph Allocate memory to  array arr_ufp6_size in SETS struct
 * @param set - pointer to SETS struct
*/
void init_arr_ufp6_size(SETS *set);
/**
 *  @paragraph Prints the UFP6 codification in a set using iteration
 *  @param set - pointer to set which contains both matrix , both arrays with sizes and the size of words
*/
void print_matrix_int(const SETS *set);
/**
 * @paragraph Generate random word size to store in arr_word_size
 * @param arr - pointer to array that stores the size of each word
 * @param W - size of words to generate sizes
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
void insert_ufp6(SETS *set, const int sizes_ufp6_dict[],const int ufp6_dict[][BITS - 1], const char *word, int index);
/**
 * @paragraph Reallocate memory for an int array of pointers (rows) and for each pointer (cols), initialize at 0
 * @param set - pointer to SETS struct which contains array to reallocate
*/
void matrix_encode_realloc(SETS *set);
/**
 * @paragraph Insert words and their ufp6 representation at the end of both matrix
 * this function reallocates the memory for both arrays holding the sizes of words and their ufp6
 * representation , calculates the new words size and ufp6 and after reallocates
 * also both matrix (matrix of words and matrix upf6) and then insert to the respective matrix.
 * Time Complexity: O(N * W * M) N = size of words supported to insert
 * W = length of word M = UFP6 size representation
 * Extra Space: O(1)
 * @param set - pointer to set that contains both matrix , both arrays with sizes and the size of words
 * @param words - array of words to be inserted
 * @param sizes_ufp6_dict - array with precomputed sizes of each ufp6 representation
 * @param ufp6_dict - precomputed dictionary with each ufp6 representation
 * @param num_words - size of words to be inserted
 */
void insert_words(SETS *set, const char **words, const int *sizes_ufp6_dict,const int ufp6_dict[][BITS - 1], int num_words);

/**
 * @paragraph Print arr holding words sizes
 * @param set - pointer to SETS struct
*/
void print_arr_word_size(const SETS *set);

/**
 * @paragraph Print matrix of strings
 * @param set - pointer to SETS struct
*/
void print_matrix_char(const SETS *set);

/**
 * @paragraph Function to calculate UFP6 representation of all words and store in
 * set arr_ufp6_size at a given index
 * Time Complexity: O(W) = length of word
 * Extra Space: O(1)
 * @param set - pointer to SETS struct
 * @param index - index of word to store the UFP6 size
 * @param word - pointer to word
 * @param sizes_ufp6 -  pointer to pre-computed array with all sizes of each char supported
 * in UFP6
*/
void calc_ufp6_size(SETS *set, int index,const char *word, const int *sizes_ufp6);
/**
 * @paragraph Free memory allocated in set
 * @param set - pointer to SETS struct
*/
void freemem_set(SETS *set);
/** msdRadixSort
 * @paragraph Sort both matrix and matrix_ufp6 in alphabetical order (ASC and DESC)
 * using MSD algorithm
 * Time complexity: O(2 W(N+R))
 * R = Radix, N size of strings,
 * W max size of chars in single word
 * Extra Space: O(2N + DR)
 * 2N = both aux arrays of size N, R = count array with size R to store char cumulative
 * frequencies and D is the size of function-call stack depth
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
 * we first shuffle the array using Knuth-Shuffle algorithm,
 * after we find median between lo mid and hi and exch with lo,
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
 * @param hi - start pos of hi =  size of rows - 1
 */
void q_sort(SETS *set,int *arr, int lo , int hi, bool flag);
/**
 * @paragraph This function is used in quicksort algorithm,
 * to partition the array in half , so when pivot is changed
 * on his left are the numbers lower than him and at his left are the size greater
 * than pivot so pivot is already sorted
 * @param set - pointer to set struct
 * @param arr - pointer to array with words size
 * @param lo - start pos of low = 0
 * @param hi - start pos of hi =  size of rows - 1
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
 * @paragraph This function implements the Knuth-shuffle algorithm,
 * it shuffles the array generating random indexes and swap elements between those index
 * , for better performance in qsort algorithm
 * @param set - pointer to SETS struct
 */
void knuth_shuffle(SETS *set);
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
 * @param ufp6_dict - pointer to Matrix to store UFP6 representations of each char
 * @param size_ufp6 - pointer to int array to store size of each UFP6 representation
 * representation sizes of each char
 */
void ufp6_dictionary(int ufp6_dict[][BITS - 1], int *size_ufp6);
/**
 * @paragraph Function to print UFP6 pre-computed dictionary
 * @param ufp6_dict - pointer to Matrix of ufp6 representations of each char
 * @param size_ufp6 - pointer to arr holding sizes of each char representation in UFP6
 */
void print_ufp6_dictionary(int bin_dict[][BITS - 1], int *size_ufp6);
/**@paragraph This function encodes a matrix of words from set using
 * encode_word function to encode each word into matrix_ufp6 in set
 * Time complexity: O (N (W * M)) N = size of words W = length of each word
 * M = UFP6 size representation
 * Extra Space: O(1)
 * @param set - pointer SETS struct
 * @param sizes_ufp6_dict - array with ufp6 sizes of each char
 * @param ufp6_dict - pre-computed dictionary with UFP6 representations
 */
void encode_matrix_words(SETS *set, int sizes_ufp6_dict[], int ufp6_dict[][BITS - 1]);
/**
 * @paragraph Convert char into UFP6 filling array in reverse order into Dictionary
 * @param c - char to be converted
 * @param result - pointer to array to store the result of each conversion
 * @param size_bin - pointer to an array with pre-computed sizes_uf6
 */
void charToUFP6(int c, int *result, int numBits_ufp6_char);
/**
 * @paragraph Print a message and exit the application
 * @param message - message to print
 */
void fperror(char *message);
 /**@paragraph This function encodes a word into an array , using pre-computed UFP6 dictionary and
 * word_ufp6_size array eith the sizes of each char representation
 * Time complexity: O (W * M) W = length of each word M = UFP6 size representation
 * Extra Space: O(1)
 * @param word - pointer to a given word
 * @param encode - pointer to a array (can be a row from matrix)
 * @param word_ufp6_size - pointer to an array of pre-computed word_ufp6_sizes
 * @param k - index of matrix row
 * @param sizes_ufp6 - pointer to an array with pre-computed sizes_ufp6
 * @param ufp6_dict - pointer to a matrix (dictionary) with each ufp6 representation pre-computed
 * @param W - word length
 */
void encode_word(const char* word, int *encode, int *word_ufp6_size, int k, const int sizes_ufp6[], const int ufp6_dict[][BITS - 1], int W);
/**
 * @paragraph Find equal combinations of UFP6 representations from 2 sets using
 * Backtracking method and a dynamic Hash Table to store and check equal combinations
 * by holding a flag (repeated) if greater than 1 and has a odd value
 * it means that combination appeared in both sets
 * Time Complexity: O (M + 2( R * BITS - 1 ) + (p!) + N) M = init Hash table
 * (R * Bits - 1) parse matrix to string p! = size of permutations
 * N = Reashing hash table
 * Extra Space: O (M + L + S) M = size of hash table L = length of string1
 * S = length of string2
 * @param set1 - pointer to SETS struct
 * @param set2 - pointer to SETS struct
 * @param size  - size of combination
 */
void combination_ufp6_in_both_sets(const SETS *set1,const SETS *set2, int size);
/**
 * @paragraph Generate permutations using Backtracking method and insert
 * into hash table to check if a permutation from a set was already generated from another set
 * if repeated from set 1 set value of repeated to 1 , if repeated in both sets , set value to an odd number greater than 1,
 * if only appear in set2 set to a even number
 * Time Complexity: O(n!) n! = size of permutations
 * Extra Space O(N + H) H = hash table N = length of string a
 * @param hash_table - pointer to HASHTABLE struct
 * @param a - pointer to array containing string with UFP6 representation
 * @param l - start index
 * @param r - end index
 * @param flag - to check is generating for set 1 or 2
 */
void generate_permutations_ufp6(HASHTABLE *hash_table,char *a, int l, int r, int flag);
/**
 * @paragraph Initialize HASHTABLE struct , initializing hash table pointers to NULL
 * @param hash_table - pointer to pointer to HASHTABLE struct
 * @param size - size of hash table
 * @param count - size of elements in Hash table
 */
void init_hash_table(HASHTABLE **hash_table, int size, int count);
/**
 * @paragraph Print hash table
 * @param hash_table - pointer to array of pointers of type UFP6 (hash table)
 */
void print_table(UFP6 **hash_table);
/**
 * @paragraph Generate Hash value using Jenkins One-at-a-Time hash algorithm to minimize collisions.
 * This function iterates over each byte of the input data (ufp6_encode). For each byte:
 * hash is updated by adding the current byte value.
 * hash is left-shifted by 10 bits.
 * The result is XORed with the right-shifted value of hash by 6 bits.
 * After processing each byte, additional mixing is performed:
 *hash is left-shifted by 3 bits.
 *hash is XORed with the right-shifted value of hash by 11 bits.
 *hash is left-shifted by 15 bits.
 * Time Complexity : O(S) S = string length
 * @param ufp6_encode - pointer to string containing the UFP6 representation
 * @param size - size of hash table
 * @return hash value
 */
unsigned int hash(const char *ufp6_encode, int size);
/**
 * @paragraph Insert new node to Hash table , If there are collisions create Linked List of nodes in Bucket
 * Time Complexity: O(1) S
 * @param hash_table - pointer to struct HASHTABLE
 * @param new - pointer to new UFP6 node
 */
void hash_table_insert(HASHTABLE *hash_table, UFP6 *new);
/**
 * @paragraph Rehash elements from Hash table
 * Time Complexity: O (N)  N = size of elements in hash table
 * @param hash_table - pointer to array of pointers of type UFP6 (hash table)
 * @param size - new size of hash table
 */
void rehash(HASHTABLE **hash_table, int size);
void swapc(char *x,char *y);
/**
 * @paragraph Lookup for a given string in hash table
 * Time Complexity: O(N) N = size of nodes in bucket
 * Extra Space: O(1)
 * @param hash_table - pointer to HASHTABLE struct
 * @param ufp6 - pointer to string containing the UFP6 representation
 * @return pointer to node containing the string
 */
UFP6 *hash_table_lookup(HASHTABLE *hash_table, char *ufp6);
/**
 * @paragraph Convert matrix of UFP6 representations to string
 * Time Complexity: O (R * BITS - 1) R = size of rows Bits - 1 : Max size of columns
 * Extra Space: O(S) S = sum of all bits in matrix
 * @param set - pointer to SETS struct
 * @return pointer to string containing all the UFP6 representations concatenated
 */
char *matrix_to_string(const SETS *set);
/**
 * @paragraph Create and Insert node in Hash table
 * @param str - pointer to string containing UFP6 representation
 * @param size - size of string without leading 0's
 */
void insert_new_UFP6_node(HASHTABLE *hash_table, const char *str, int size, int flag);
int calculate_decimal_size(int num);
void print_combinations_found(HASHTABLE *hash_table, int size);
void free_hash_table(UFP6 **hash_table);
/**
 * @paragraph This function compares two strings starting from position D
 * @param str1 - pointer to string1
 * @param str2 - pointer to string2
 * @param d - start at dth character
 * @param flag - boolean, if set to 1 compare to ASC order , if set to 0 compare to DESC order
 * @return if str1 < str2 returns a non-zero size, if str1 > str2 it returns 0
 */
int less(char *str1, char *str2, int d, bool flag);
/**
 * @paragraph This function sorts a set of words using insertion sort algorithm
 * Time Complexity: O(N^2) N = size of words
 * Extra Space: O(1)
 * @param set - pointer to SETS struct
 * @param lo - lower bound
 * @param hi - higher bound
 * @param d - start at dth character
 * @param flag - boolean, if set to 1 sort in ASC order , if set to 0 sort in DESC order
 */
void insertion_sort(SETS *set, int lo, int hi, int d, bool flag);
/**
 * @paragraph This function sorts a set of words by their size using insertion sort algorithm
 * Time Complexity: O(N^2) N = size of words
 * Extra Space: O(1)
 * @param set - pointer to SETS struct
 * @param lo - lower bound
 * @param hi - higher bound
 * @param d - start at dth character
 * @param flag - boolean, if set to 1 sort in ASC order , if set to 0 sort in DESC order
 */
void insertion_sort_int(SETS *set, int lo, int hi, bool flag);
/**
 * @paragraph Sort matrix of words and UFP6 representations in chronological order (ASC or DESC)
 * using mergesort algorithm
 * Time Complexity: O(NlogN)
 * Extra Space: O(2M) M = size of words
 * @param set - pointer to SETS struct
 * @param sizes_ufp6 - pointer to array with pre-computed sizes of UFP6 of each char
 * @param flag - boolean, if set to 1 sort in ASC order , if set to 0 sort in DESC order
 */
void sort_by_alphabetical_order(SETS *set,const int *sizes_ufp6, bool flag);
/**
* @paragraph Merge function used in mergesort algorithm
* Time Complexity: O(N)
* Extra Space: O(1)
* @param set - pointer to SETS struct
* @param aux_matrix - pointer to an array of char pointers (auxiliary matrix_words)
* @param aux_matrix_ufp6 - pointer to an array of int pointers (auxiliary matrix_ufp6)
* @param lo - start index of array
* @param mid - middle index of array
* @param hi - end index of array
* @param flag - boolean, if set to 1 sort in ASC order , if set to 0 sort in DESC order
*/
void merge(SETS *set, char **aux_matrix, int **aux_matrix_ufp6, int lo, int mid, int hi, bool flag);
/**
* @paragraph Mergesort recursive function , using "divide and conquer" strategy
* With 2 improvements implemented : Cutoff to small subarrays (CUTOFF = 10)
* and stop if already sorted
* Time Complexity: O(NlogN)
* Extra Space: O(2N) M = size of words
* @param set - pointer to SETS struct
* @param aux_matrix - pointer to an array of char pointers (auxiliary matrix_words)
* @param aux_matrix_ufp6 - pointer to an array of int pointers (auxiliary matrix_ufp6)
* @param lo - start index of array
* @param hi - end index of array
* @param flag - boolean, if set to 1 sort in ASC order , if set to 0 sort in DESC order
*/
void sort(SETS *set, char **aux_matrix, int **aux_matrix_ufp6, int lo, int hi, bool flag);
/**
 * @paragraph KMP Algorithm to build DFA of a patter (word)
 * Time Complexity: O(M) M = length of pattern
 * Extra Space: O(MAX_UFP6 * BITS - 1) MAX_UFP6 * BITS - 1 for DFA
 * @param pattern -pointer to pattern (word) to be found
 * @param dfa -pointer to Deterministic Finite State Automaton (abstract string-searching
 * machine)
 */
void KMP(const char pattern[BITS - 1], int dfa[MAX_UFP6][BITS - 1]);
/**
 * @paragraph Function to search for a pattern in matrix of words in SETS struct usind KMP algorithm
 * Time complexity: O(N * M) N = total size of words in set
 * M = length of pattern N = size of words in set
 * Extra Space: O(P) P = size of array to store indexes of words with pattern
 * @param set - pointer to SETS struct
 * @param dfa - Deterministic finite state automaton (abstract string-searching
 * machine)
 * @param pattern_length - size of word to be searched
 * @return returns an array with indexes of words found in matrix containing the pattern,
 * in the first pos of array it's stored the size of words (indexes) found
 */
int *search_KMP(const SETS *set, int dfa[MAX_UFP6][BITS - 1], int pattern_length);
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
 * store the size of words
 */
void print_found_words_and_ufp6(const SETS *set,const int *array_index);
/**
 * Find patterns in a given set using KMP Algorithm
 * Time Complexity of O(P (M + N * M))
 * M = length of longest pattern N = size of rows (words in set) P = size of patterns to search for
 * Extra Space: O(MAX_UFP6 * BITS - 1 + P) MAX_UFP6 * BITS - 1 for DFA
 * and P = array to store indexes of words with given pattern
 * @param set - pointer to SETS struct
 * @param patterns - pointer to an array of pointers to characters (array of strings with patterns)
 * @param W - size of patterns to search
 * @param fn - file name
 * @param flag - boolean,if set to 1 write to a txt file words found with given pattern
 */
void find_words_with_pattern(const SETS *set, const char **patterns, int W, const char *fn, bool flag);
/**
 * @paragraph Remove word from set, given array with the indexes of the rows in both matrix, adjusting
 * both matrix .When adjusting rows If prev word size is lesser than the next, reallocate that row
 * @param set - pointer to SETS struct
 * @param arr_index_words_found - pointer to an array of index, pos 0 has the size of words (indexes) found
 */
void remove_word_from_set(SETS *set, int index_remove);
/**
 * Function to find given word in set comparing each word in set with given word
 * and after remove and shift all rows in both matrix and matrix_ufp6
 * Time Complexity: O(N) N = size of words in set //strcmp has a really low time complexity that's why it will have a little cost
 * because UFP6 words have MAX 7 bits
 * @param set - pointer to SETS struct
 * @param word - pointer to word
 */
void find_word_in_set_and_remove(SETS *set,const char *word);
/**
 * Function remove given Words and UFP6 representation from set
 * Time Complexity: O(W * N)
 * N = size of words in set W = size of words to remove
 * Extra Space: O(1)
 * @param set - pointer to SETS struct
 * @param words - pointer to an array of strings (words to be removed)
 * @param W - size of words to be removed
 */
void remove_Words(SETS *set,const char **words, int W);
/**
 * @paragraph Find all occurrences of given pattern in set and store indexes of occurrences in array_index
 * and the size of occurrences in first position of that array
 * Time Complexity of O(M + N * M)
 * M = length of longest pattern N = size of rows (words in set)
 * Extra Space: O(MAX_UFP6 * BITS - 1 + P) MAX_UFP6 * BITS - 1 for DFA
 * and P = array to store indexes of words with given pattern
 * @param set - pointer to SETS struct
 * @param patterns - pointer to an array of pointers to characters (array of strings with patterns)
 * @param array_index - pointer to a pointer to an array to store indexes of words found with pattern
 */
void find_word_with_pattern(const SETS *set, const char *pattern, int **array_index);
/**
 * Function to remove UFP6 representation of given word adjusting rows from matrix_ufp6
 * Time Complexity: O(N) N = size of words in UFP6 matrix
 * Extra Space: O(1)
 * @param set - pointer to SETS struct
 * @param index - index of UFP6 representation to be removed
 */
void remove_UFP6(SETS *set,int index);
/**
 * @paragraph Reallocate memory for pointer to string (word) if next word from matrix is greater than the current word to shift
 * @param set - pointer to SETS struct
 * @param row - index of current row to shift from next to current
*/
void realloc_row_remove(SETS *set, int row);
/**
 * @paragraph Calculates the size of W words and places the result in the array words_index
 * @param words - array with the words
 * @param words_index -pointer to an array that will contain the sizes of words
 * @param W - size of words
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
void calloc_matrix_words_and_ufp6(SETS *set, int num_words);
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
 * @param W - length of word to be checked
 * @return return 1 if word is supported or return 0 if word is not supported
 */
int is_ufp6(const char *word, int W);
/**
 * @paragraph Function to create a seed based on processor time
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
/**
 * @paragraph This function checks if words are supported in UFP6
 * if not supported in UFP6 set to NULL pointer to word and update prev_num_words supported
 * if supported update row size of both  matrix to after reallocate them
 * Time Complexity: O(W)
 * Extra Space: O(1)
 * @param set - pointer to SETS struct
 * @param words - pointer to array of strings (words)
 * @param W - size of words
 * @param prev_num_words - variable to store the size of strings supported in UFP6
*/
void check_words_supported_UFP6(SETS *set, char **words, int W, int *prev_num_words);
/**
 * @paragraph This function calculates the words and UFP6 sizes from a set of words and it stores
 * in arr_word_size and arr_ufp6_size from SETS struct
 * Time Complexity: O(N) N = number of rows in matrix
 * @param set - pointer to SETS struct
 * @param sizes_ufp6 - pointer to array holding sizes of pre-computed UFP6 representations of each char
*/
void calculate_sizes_words_and_ufp6_from_set(SETS *set, const int *sizes_ufp6);
/**
 * @paragraph This function writes to a txt file the benchmark of 2 sorting algorithms implemented to better understand their
 * Time Complexity
 * @param set - pointer to SETS struct
 * @param words - pointer to array holding sizes of UFP6 of each char
*/
void write_to_txt_benchmark_sorting(char *fn, float time_delta_merge_s, float time_delta_msd, unsigned long number_words);
/**
 * @paragraph Read words from .txt file to set
 * File format
 *number_words = 5
 *6-e 2 D b A h
 *5-Z f z 0 h
 *7-6 U 2 z S m 0
 *2-U H
 *5-h 7 e Q q
 * @param set - pointer to SETS struct
 * @param fp - pointer to file
*/
void read_words_from_txt_to_set(SETS *set, FILE *fp, const int *sizes_ufp6);
/**
 * @paragraph Read words from txt file to set
 * @param set - pointer to SETS struct
 * @param fn - pointer to string containing file name
*/
void read_words_from_txt(SETS *set, const char *fn, const int *sizes_ufp6);



#endif //PROJETO_AED1_LP1_FUNCTIONS_1_H
