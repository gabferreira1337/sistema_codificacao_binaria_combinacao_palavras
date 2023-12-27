#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include "functions_1.h"
#include "functions_2.h"

#define CUTOFF 10


int main_functions_1(int argc , char **argv){
    return 0;
}

void matrix_ufp6_init(SETS *set,const int *sizes_ufp6_char){
    /// Allocate memory for array of pointers
    set->matrix_ufp6 = (int**)calloc(set->rowsize, sizeof(int*));
    if (set->matrix_ufp6 == NULL) {
        fperror("matrix_ufp6 malloc in matrix_ufp6_init");
    }
    ///Allocate memory for each pointer to arrays
    for (int i = 0; i < set->rowsize; ++i) {
        ///Calculate each UFP6 representation to allocate exact number of columns
        calc_ufp6_size(set, i, *(set->matrix + i), sizes_ufp6_char);
        *(set->matrix_ufp6 + i) = (int*)calloc(*(set->arr_ufp6_size + i), sizeof(int));
        if (*(set->matrix_ufp6 + i) == NULL) {
            fperror("matrix_ufp6 row malloc in matrix_ufp6_init");
        }
    }
}

void matrix_init_char(SETS *set){
    /// Allocate memory for array of pointers
    set->matrix = (char**) malloc(set->rowsize * sizeof(char*));
    if (set->matrix == NULL) {
        fperror("Matrix init malloc in matrix_init_char");
    }

    for (int i = 0; i < set->rowsize; ++i) {
        /// Allocate memory for each pointer to arrays (cols) // + 1 for '\0'
        *(set->matrix + i) = (char*)calloc(*(set->arr_word_size + i) +  1, sizeof(char));
        if (*(set->matrix + i) == NULL) {
            fperror("Matrix char calloc pointers to arrays (cols) in matrix_init_char");
        }
    }
}

void print_matrix_int(const SETS *set) {
    printf("Matrix of UFP6:\n");
    for (int i = 0; i < set->rowsize; ++i){
        for (int j = 0; j < *(set->arr_ufp6_size + i); ++j) {
            printf("%d ",*(*(set->matrix_ufp6 + i) + j));
        }
        putchar('\n');
    }
}

void print_matrix_char(const SETS *set) {
    printf("Matrix of strings:\n");
    for (int i = 0; i < set->rowsize; ++i) {
        for (int j = 0; j < *(set->arr_word_size + i); ++j) {
            printf(" %c", *(*(set->matrix + i) + j));
        }
        putchar('\n');
    }
}

void encode(SETS *set){
    int charCalc = 0;
    int  j=0;
    for (int i = 0; i < set->rowsize; ++i) {
        j =0;
        //calculate_ufp6_sizes ( *(*(set->));
        for (int k = 0;k < *(set->arr_word_size + i); k++) {
            charCalc = (unsigned char) *(*(set->matrix + i) + k) ;
            if (charCalc >= '0' && charCalc <= '9') {
                int digit = charCalc - '0';
                for (int l = BITS - 1; l >= 0 && j < set->arr_ufp6_size[i] ; l--, j++) {
                    *(*(set->matrix_ufp6 + i) + j) = (digit >> l) & 1;
                }
            } else if (charCalc >= 'a' && charCalc <= 'z') {
                /* 10 represents the beginning of letters */
                int letter = charCalc - 'a' + 10;
                for (int l = BITS -1; l >= 0 && j < set->arr_ufp6_size[i]; l--, j++) {
                    /* when last digit is 0 break from the loop, so it won't store the left 0's */
                    if ((letter >> l) == 0) {
                        *(*(set->matrix_ufp6 + i) + j) = -1;
                    } else {
                        *(*(set->matrix_ufp6 + i) + j) = (letter >> l) & 1;
                    }
                }
            } else if (charCalc >= 'A' && charCalc <= 'Z') {
                /* 'a' is the value 36 (A = 10 a = 10 + 26) */
                int letter = charCalc - 'A' + 36;
                for (int l = BITS -1; l >= 0 && j < set->arr_ufp6_size[i]; l--, j++) {
                    if((letter >>l) == 0) break;
                    *(*(set->matrix_ufp6 + i) + j) = (letter >> l) & 1;
                }
            }
        }
    }
}

void rnd_word_size_gen(int *word_length_arr, int W) {
    /* seed to generate random numbers */
    seed_random();
    for (int i = 0; i < W; ++i) {
        /* Generate numbers from 1 to BITS - 1 // sum + 1 to the result so never generates 0 */
        /* And store in word_length */
        word_length_arr[i] = (rand() % (BITS - 1)) + 1;
    }
}

char gen_rnd_char(){
    int random_number;
    ///Generate random number between 0 and MAX_UFP6
    random_number =  rand() % MAX_UFP6;
    /// '0' to '9' (digits)
    if (random_number < 10) {
        return (char) ('0' + random_number);
        /// 'a' to 'z' (lowercase letters)
    } else if (random_number < 36 ) {
        /// 'a' + (random_number - 10 ) because in ASCII table
        /// 'a' = 97 dec but in UFP6 'a' = 10 so for example
        /// if random number = 10 we need to get char 'a'
        ///so  subtract 10 because from '0' to '9' it has digits
        ///and need to get the ASCII code from 'a' starting in '0' and sum the first char ('a')
        ///for example: 'a' + 10 - 10 = 'a'
        return (char) ('a' + (random_number - 10));
        /// 'A' to 'Z' (uppercase letters)
    } else if(random_number < RADIX){
        ///In here subtract 36 because  '0' to 'z' = 36 and the random number will be from 36 to RADIX
        ///and to get ASCII from 'A' to 'Z' start from '0' and sum 'A'
        return (char) ('A' + (random_number - 36));
    }
}

void matrix_rnd_word_gen(SETS *set) {
    /// seed to generate random numbers
    seed_random();
    //srand((unsigned int)time(NULL));
    int j = 0;
    for (int i = 0; i < set->rowsize; ++i) {
        ///generate random char to fill word
        for (j = 0; j < *(set->arr_word_size + i); ++j) {
            *(*(set->matrix + i) +j) = gen_rnd_char();
        }
        ///terminate each word with '\0'
        *(*(set->matrix + i) +j) = '\0';
    }
}



void insert_word_char(SETS *set,const char *word,int index) {
        for (int j = 0; j < set->arr_word_size[index]; ++j) {
            //printf("%c", word[j]);
            *(*(set->matrix + index) + j) = word[j];
            /* if the word is smaller than colsize_char fill the rest with ' ' */
            /*if (j >= strlen(words[k]))
                *(*(set->matrix + i) + j) = ' ';*/
        }
}


void freemem_set(SETS *set){
    //Free each row from matrix of words and ufp6
    for (int i = 0; i < set->rowsize; ++i) {
        free(set->matrix_ufp6[i]);
        set->matrix_ufp6[i] =NULL;

        free(set->matrix[i]);
        set->matrix[i] =NULL;
    }
    //Free pointer to matrix
    free(set->matrix);
    set->matrix =NULL;
    //Free pointer to matrix_ufp6
    free(set->matrix_ufp6);
    set->matrix_ufp6 =NULL;
    //Free pointer to array with words size
    free(set->arr_word_size);
    set->arr_word_size = NULL;
    //Free pointer to array with ufp6 size
    free(set->arr_ufp6_size);
    set->arr_ufp6_size = NULL;
}

void matrix_realloc(SETS *set){
    print_arr_word_size(set);
        set->matrix = (char **) realloc(set->matrix,set->rowsize * sizeof(char *));

        if(set->matrix == NULL){
            printf("Realloc set->matrix failed !\n");
            freemem_set(set);
            exit(0);
        }

        for (int i = 0; i < set->rowsize; ++i) {
            realloc_col_word(&*(set->matrix +i),*(set->arr_word_size + i));
        }
}

void init_arr_word_size(SETS *set){
    set->arr_word_size = (int *) calloc(set->rowsize, sizeof(int));
    if((set->arr_word_size) == NULL){
        fperror("arr_word_size calloc in init_arr_word_size");
    }
}


void print_arr_word_size(const SETS *set){
    for (int i = 0; i < set->rowsize; ++i) {
        printf("pos: %d - size: %d\n", i, set->arr_word_size[i]);
    }
}


void matrix_encode_realloc(SETS *set) {
    set->matrix_ufp6 = (int **) realloc(set->matrix_ufp6, set->rowsize * sizeof(int *));

    if (set->matrix_ufp6 == NULL) {
        printf("ERROR encode realloc\n");
        exit(0);
    }
        //allocate for words_size
        for (int i = 0; i < set->rowsize; ++i) {
            *(set->matrix_ufp6 + i) = (int *) realloc(*(set->matrix_ufp6 + i), *(set->arr_ufp6_size + i) * sizeof(int));
            if (*(set->matrix_ufp6 + i) == NULL) {
                printf("Matrix encode realloc\n");
                freemem_set(set);
                exit(0);
            }
        }
}
/*void char_to_bin(SETS *set) {
    for (int l = 6; l >= 0 && j < (set->arr_word_size[i]) * 7;l--, j++) {
        // when last digit is 0 break from the loop, so it won't store the left 0's
        if ((letter >> l) == 0) {
            *(*(set->matrix_ufp6 + i) + j) = -1;
        } else {
            *(*(set->matrix_ufp6 + i) + j) = (letter >> l) & 1;
        }
    }
}*/

void fperror(char *message) {
    fprintf(stderr, "ERROR: %s\n", message);
    exit(0);
}

int less(char *str1, char *str2, int d, bool flag) {
    int result = strcmp(str1 + d, str2 + d);
    return flag ? result < 0 : result > 0;
}

void insertion_sort(SETS *set, int lo, int hi, int d, bool flag){
    for (int i = lo; i <= hi; i++){
        for (int j = i; j > lo && less(set->matrix[j], set->matrix[j-1], d, flag); j--) {
            exch_rows_matrix_char(set, j, j - 1);
            exch_rows_matrix_ufp6(set, j, j - 1);
        }
    }
}


void msdRadixSort_r(SETS *set, char **aux,int **aux_ufp6,const int *arr_sizes_ufp6, int lo, int hi, int d, bool flag) {
    if (hi <= lo) return;
    /// For small arrays, use Insertion Sort because msd has too much overhead for small arrays
    if (hi - lo + 1 <= CUTOFF) {
        insertion_sort(set, lo, hi, d, flag);
        return;
    }
    ///Store frequencies of each char
    int count[RADIX + 2] = {0};

    ///Add frequencies of each char to count array
    for (int i = lo; i <= hi; i++) {
        char currentChar = *(*(set->matrix + i) + d);
        ///calculate Index to insert into count
        int charIndex = calculate_index_char(currentChar, flag);
        /// + 2 for after store cumulative frequencies
        count[charIndex + 2]++;
    }
  
    ///Update cumulative frequencies of each char
    for (int r = 0; r < RADIX + 1; ++r) {
        count[r + 1] += count[r];
    }

    /// Insert words into aux array in the right order //
    for (int i = lo; i <= hi; ++i) {
        /// Get char from row i col d
        char currentChar = *(*(set->matrix + i) + d);
        /// find right index in RADIX
        int charIndex = calculate_index_char(currentChar, flag);
        int index = *(count + charIndex + 1);
        /// insert into aux to aux and aux_ufp6 pointers to rows in sorted positions
        *(aux_ufp6 + index) = *(set->matrix_ufp6 + i);
        *(aux + index) = *(set->matrix + i);
        ///increment in count array to insert in next pos
        count[charIndex + 1]++;
    }

    /// Copy values from aux to arr
    for (int i = lo; i <= hi; ++i) {
        /// aux is the sorted array, so change *(set->matrix + i) to point to sorted row from aux
        *(set->matrix + i) = *(aux + i - lo);
        *(set->matrix_ufp6 + i) = *(aux_ufp6 + i - lo);
        /// calculate size of ufp6 representation moved to ufp6_matrix and store into arr_sizes_ufp6
        //calc_ufp6_size(set, i, *(set->matrix + i), arr_sizes_ufp6);
        /// calculate size of word moved to matrix and store into arr_word_sizes
        //*(set->arr_word_size + i) = (int)strlen(*(set->matrix + i));
    }

    for (int r = 0; r < RADIX; ++r) {
        ///Calculate lower bound of a set of words
        int low = lo + count[r];
        ///Calculate higher bound of a set of words
        int high = lo + count[r + 1] - 1;
        ///recursive call to sort sets between low and hi
        ///d + 1 to go to next column from left to right
        msdRadixSort_r(set, aux, aux_ufp6,arr_sizes_ufp6, low, high, d + 1, flag);
    }
}

void msdRadixSort(SETS *set,const int *array_sizes_ufp6 ,int lo, int hi, bool flag) {
    ///Temp array of char pointers
    char **aux = (char **)malloc((hi - lo + 1) * sizeof(char *));
    if (aux == NULL) {
        fperror("aux in msdRadixSort Memory Allocation");
    }
    ///Temp array of int pointers
    int **aux_ufp6 = (int **)malloc((hi - lo + 1) * sizeof(int *));
    if (aux_ufp6 == NULL) {
        fperror("aux_ufp6 in msdRadixSort Memory Allocation");
    }

    msdRadixSort_r(set, aux,aux_ufp6,array_sizes_ufp6, lo, hi - 1, 0,flag);

    calculate_sizes_words_and_ufp6_from_set(set, array_sizes_ufp6);


    free(aux);
}


void ufp6_dictionary(int ufp6_dict[][BITS - 1], int *size_ufp6) {
    int index = 0;
    /// Convert '0' to '9' to UFP6
    for (char digit = '0'; digit <= '9'; digit++) {
        ///Calculate size of each UFP6 representation based on binary
        ///Edge cases when '0' because log2(0) = undefined but we need one bit to represent '0'
        if(digit - '0' == 0){
            size_ufp6[index] = 1;
        }else{
            /// We know the number of bits to represent a given value by doing
            /// log2((digit)) + 1
            size_ufp6[index] = (int) log2((digit - '0')) + 1;
        }
        ///Convert each char to ufp6
        charToUFP6(digit - '0', ufp6_dict[index], size_ufp6[index]);
        index++;
    }
    /// Convert 'a' to 'z' to UFP6
    for (char letter = 'a'; letter <= 'z'; letter++) {
        size_ufp6[index] = log2((letter - 'a' + 10)) + 1;
        charToUFP6(letter - 'a' + 10, ufp6_dict[index], size_ufp6[index]);
        index++;
    }
    /// Convert 'A' to 'Z' to UFP6
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        size_ufp6[index] = log2((letter - 'A' + 36)) + 1;
        charToUFP6(letter - 'A' + 36, ufp6_dict[index], size_ufp6[index]);
        index++;
    }
}


void charToUFP6(int c, int *result, int numBits_ufp6_char) {
    /// Use numBits_ufp6_char to only store the right number of bits of each value
    ///Convert filling array in reverse order
    for (int i = numBits_ufp6_char - 1; i >= 0; i--) {
       /// c >> i =  right-shifts the bits of c by i times
       /// Moving the bit at position i to the least significant bit (LSB).
       /// (c >> i) & 1 = bitwise AND with 1. Extracting the least significant bit (LSB)
       /// after the right shift, checking whether the bit at position i is 0 or 1.
        result[numBits_ufp6_char - 1 - i] = (c >> i) & 1;
    }
}

void print_ufp6_dictionary(int (*bin_d)[BITS - 1], int *size_ufp6) {
    for (int i = 0; i < 62; i++) {
        if( i < 10){
            printf("Binary for %c: ",  ('0' + i) );
        }else if(i >= 10 && i <= 36){
            printf("Binary for %c: ", ('a' + i - 10));
        }else{
            printf("Binary for %c: ",  ('A' + i - 36));
        }
        //printf("Binary for %c: ", (i < 10) ? ('0' + i) : ('a' + i - 10));
        for (int j = 0; j < size_ufp6[i]; j++) {
            printf("%d", bin_d[i][j]);
        }
        printf("\n");
    }
}

/**@paragraph This function encodes a word into an array , using pre-computed UFP6 dictionary and
 * word_ufp6_size array eith the sizes of each char representation
 * Time complexity: O (W * M) W = length of word M = UFP6 size representation
 * Extra Space: O(1)
 */
void encode_word(const char* word, int *encoded, int *word_ufp6_size, int k, const int sizes_ufp6[], const int ufp6_dict[][BITS - 1], int W) {
    if(ufp6_dict[0][0] != 0) fperror("Bin_dict not precomputed encode_matrix_words");
    int index = 0;
    word_ufp6_size[k] = 0; ///initialize to 0 the array with ufp6 size
    ///Check if word is supported in ufp6 to encode
    if(is_ufp6(word, W) == - 1){
        printf("Word %s not supported in UFP6", word);
        exit(0);
    }
    for (int i = 0; i < W; i++) {
        char currentChar = word[i];
        ///get index in UFP6 Table
        int charIndex = calculate_index_char(currentChar, 1);

        /// Store the size of ufp6 representation of each char encoded
        word_ufp6_size[k] += sizes_ufp6[charIndex];

        /// Copy the ufp6 representation to the encoded array (row in matrix_ufp6)
        for (int j = 0; j < sizes_ufp6[charIndex]; j++) {
            encoded[index++] = ufp6_dict[charIndex][j];
        }
    }
}

/**@paragraph This function encodes a matrix of words from set using
 * encode_word function to encode each word into matrix_ufp6 in set
 * Time complexity: O (N (W * M)) N = number of words W = length of each word
 * M = UFP6 size representation
 * Extra Space: O(1)
 */
void encode_matrix_words(SETS *set, int *sizes_ufp6_dict, int ufp6_dict[][BITS - 1]) {
    for (int i = 0; i < set->rowsize; ++i) {
        encode_word(set->matrix[i], set->matrix_ufp6[i], set->arr_ufp6_size, i, sizes_ufp6_dict, ufp6_dict, set->arr_word_size[i]);
    }
}

/**
 * Function to build a DFA from a given pattern
 */
void KMP (const char pattern[BITS - 1], int dfa[MAX_UFP6][BITS - 1]) {
    int indexChar = 0;
    int pattern_size =(int) strlen(pattern);

    ///Initialize DFA to 0
    for (int i = 0; i < MAX_UFP6; ++i) {
        ///Until pattern_size
        for (int j = 0; j < pattern_size; ++j) {
            dfa[i][j] = 0;
        }
    }

    ///Calculate index of char in UFP6 ASCII table in ASC order
    indexChar = calculate_index_char(pattern[0], 1);
    ///Initialize first col of given row to 1
    dfa[indexChar][0] = 1;

    for (int X = 0, j = 1; j < pattern_size; ++j){
        for (int c = 0; c < MAX_UFP6 ; ++c) {
            ///Calculate index char in ufp6 ASCII table in ASC order
           indexChar = calculate_index_char(pattern[j], 1);
          
           dfa[c][j] = dfa[c][X];       ///copy mismatch cases
        }
        dfa[indexChar][j] = j + 1;      ///set match case
        X = dfa[indexChar][X];          ///update restart state
    }
}

int calculate_index_char(char currentChar, bool flag) {
    int charIndex = 0;
    ///if char is supported in UFP6
    if ((currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= '0' && currentChar <= '9') ||
        (currentChar >= 'a' && currentChar <= 'z')) {
        ///Calculate in ASC order
        if (flag == 1) {
            if (currentChar >= 'A' && currentChar <= 'Z') {
                charIndex = (currentChar - 'A' + 36);
            } else if (currentChar >= '0' && currentChar <= '9') {
                charIndex = (currentChar - '0');
            } else {
                charIndex = (currentChar - 'a' + 10);
            }
        } else {
            ///Reverse subtraction to calculate index in DESC order
            if (currentChar >= 'A' && currentChar <= 'Z') {
                charIndex = ('Z' - currentChar);
            } else if (currentChar >= '0' && currentChar <= '9') {
                charIndex = ('9' - currentChar + 36);
            } else {
                charIndex = ('z' - currentChar + 10);
            }
        }
        return charIndex;
    }
    ///If char is not supported return -1
    return -1;
}

/**
 * Function to search for a given word given size and pre-computed DFA
 */
int *search_KMP(const SETS *set, int dfa[MAX_UFP6][BITS - 1], int pattern_length){
    int i , j;
    int indexChar = 0;
    int *arr_index = (int*) calloc(set->rowsize,sizeof(int));
    if(arr_index == NULL){
        fperror("Calloc arr_index in search_KMP");
    }
    ///Start pos of arr_index where we want to insert all index that contains the given word
    ///Start to 1 to store in pos 0 the count of indexes
    int l = 1;
    for (int k = 0; k < set->rowsize; ++k) {
        for (i = 0, j = 0; i < strlen(*(set->matrix + k)) && j < pattern_length ; ++i) {
            ///Calculate index char in ufp6 ASCII table in ASC order
            indexChar = calculate_index_char(*(*(set->matrix + k ) + i), 1);
            ///Go through DFA
            j = dfa[indexChar][j];          ///no backup
        }
        /// If found word in a row (if j gets to last state in DFA) store index in arr_index
        if (j == pattern_length){
            arr_index[l++] = k;
        }
    }
    ///Store in pos 0 of array the count of words found with pattern
    *(arr_index + 0) = l-1;
    ///if found words return pointer to array
    if(*(arr_index + 0) != 0)
        return arr_index;
    return NULL;
}


void print_kmp(int dfa[MAX_UFP6][M_KMP]) {
    for (int i = 0; i < MAX_UFP6; ++i) {
        for (int j = 0; j < M_KMP; ++j) {
            printf(" %d", dfa[i][j]);
        }
        putchar('\n');
    }
}

void print_found_words_and_ufp6(const SETS *set,const int *array_index) {
    /// Starts in 1 because storing in index 0 the count of words found // if *array_index == 0 , no words found
    for (int k = 1; k <= *array_index; ++k) {
        printf("Index -> %d\n", *(array_index + k));
        printf("Word = %s |", *(set->matrix + (*(array_index + k))));
        printf(" UFP6 = ");
        for (int i = 0; i < *(set->arr_ufp6_size + (*(array_index + k))); i++) {
            printf("%d", set->matrix_ufp6[array_index[k]][i]);
        }
        putchar('\n');
    }
}

/**
 * Find patterns in a given set using KMP Algorithm
 * Time Complexity of O(P (M + N * M))
 * M = length of longest pattern N = number of rows (words in set) P = number of patterns to search for
 * Extra Space: O(MAX_UFP6 * BITS - 1 + P) MAX_UFP6 * BITS - 1 for DFA
 * and P = array to store indexes of words with given pattern
 */
void find_words_with_pattern(const SETS *set, const char **patterns, int W, const char *fn, bool flag) {
    if (W <= 0) {
        fperror("Incorrect number patterns (less or equal to 0) in find_words_with_pattern");
    }

    ///Array to store the indexes of the patterns found in set
    int *array_index = NULL;
    /// For each pattern
    for (int i = 0; i <W; ++i) {
        find_word_with_pattern(set, patterns[i], &array_index);
        ///If flag == 1 and if found patterns with pattern write patterns found and their respective ufp6 representation to a txt file
        if(flag == 1 && array_index != NULL){
            write_words_found_to_txt_set_with_pattern(set, array_index, fn, patterns[i]);
        }
    }
}
/**
 * Function to remove word and UFP6 representation of given word and adjust rows from both matrix in set
 * Time Complexity: O(N) N = number of words in UFP6 matrix
 * Extra Space: O(1)
 * @param set - pointer to SETS struct
 * @param index - index of word (row) to be removed
 */
void remove_word_from_set (SETS *set, int index_remove) {
        ///adjust rows of matrix and matrix_ufp6 moving next row to previous
        for (int i = index_remove; i < set->rowsize - 1; ++i) {
            ///Reallocate mem for row size if current row has lesser size than the next row
            realloc_row_remove(set, i);
            ///Copy values from next to current
            *(set->arr_word_size + i) = *(set->arr_word_size + i + 1);
            *(set->arr_ufp6_size + i) = *(set->arr_ufp6_size + i + 1);
            strcpy(set->matrix[i], set->matrix[i + 1]);
            ///Remove UFP6 representation from matrix_ufp6 in set by shifting rows
            remove_UFP6(set, i);
        }

        ///adjust number of rows of both matrix after deleting
        set->rowsize--;

        ///free row and clear stored size
        free(set->matrix[set->rowsize]);
        free(set->matrix_ufp6[set->rowsize]);
        set->arr_word_size[set->rowsize] = 0;
        set->arr_ufp6_size[set->rowsize] = 0;
}


void  realloc_row_remove(SETS *set, int row) {
    ///Realloc row size if current row has lesser size than the next row
    if(set->arr_word_size[row] < set->arr_word_size[row + 1] ){
        set->matrix[row] =  realloc(set->matrix[row], sizeof(char) * set->arr_word_size[row + 1]);
        if(set->matrix[row] == NULL){
            fperror("REALLOC in realloc_row_remove");
        }
    }
}

void compute_words_size(const char **words, int *words_index ,int W) {
    for (int i = 0; i < W; ++i) {
        words_index[i] = (int) strlen(words[i]);
    }
}

void sets_struct_init(SETS *set,const int *sizes_ufp6, int num_words) {
    ///Store number of words (rows) of both matrix in set
    set->rowsize = num_words;
    ///Initialize arrays to store words size and UFP6 words representation
    init_arr_word_size(set);
    init_arr_ufp6_size(set);
    ///Generate random words size and store in arr_word_size array in set
    rnd_word_size_gen(set->arr_word_size, set->rowsize);
    ///Initialize matrix to hold words given sizes generated and stored in arr_word_size
    matrix_init_char(set);
    ///Generate words given sizes stored in arr_word_size and store in matrix
    matrix_rnd_word_gen(set);
    ///Initialize matrix_ufp6 calculating size of each ufp6 representation of words
    ///to allocate for each pointer to row
    matrix_ufp6_init(set, sizes_ufp6);
}

void init_arr_ufp6_size(SETS *set){
    set->arr_ufp6_size = (int*) calloc(set->rowsize, sizeof(int));
    if(set->arr_ufp6_size == NULL){
        fperror("Calloc arr_ufp6_size in init_array_ufp6_size");
    }
}

/// clock function to measure processor time and use as a seed
void seed_random() {
    unsigned  int seed = (unsigned int)time(NULL) + (unsigned  int) clock();
    srand(seed);
}

int is_ufp6(const char *word, int W) {
    char currentChar = '\0';
    for (int i = 0; i < W; ++i) {
        currentChar = *(word + i);
        if ((currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= '0' && currentChar <= '9') ||(currentChar >= 'a' && currentChar <= 'z')) {
            continue;
        }else{
            return -1;
        }
    }
    return 1;
}

void realloc_arr_words_size(SETS *set) {
    /* Realloc memory for arr_word_size */
    set->arr_word_size = (int *) realloc(set->arr_word_size,set->rowsize * sizeof(int));

    if(set->arr_word_size == NULL){
        fperror("Realloc arr_word_size failed in realloc_arr_words_size !");
    }
}

void realloc_arr_ufp6_size(SETS *set) {
    /// Realloc memory for arr_ufp6_size
    set->arr_ufp6_size = (int *) realloc(set->arr_ufp6_size, set->rowsize * sizeof(int));

    if(set->arr_word_size == NULL){
        fperror("Realloc arr_ufp6_size failed in realloc_arr_ufp6_size !");
    }
}

void insert_ufp6(SETS *set, const int sizes_ufp6_dict[],const int ufp6_dict[][BITS - 1], const char *word, int index) {
    encode_word(word, set->matrix_ufp6[index], set->arr_ufp6_size, index, sizes_ufp6_dict, ufp6_dict, set->arr_word_size[index]);
}

void calc_ufp6_size(SETS *set, int index,const char *word, const int *sizes_ufp6){
    set->arr_ufp6_size[index] =0;
    for (int i = 0; i < strlen(word); ++i) {
        char currentChar = word[i];
        int charIndex = calculate_index_char(currentChar, 1);
        /// Check if the character is a valid key in dictionary
        if (charIndex == -1){
            printf("char %c not supported in UFP6\n", word[i]);
            fperror("in calculate_ufp6_sizes");
        }
        /// Store the size of each word
        set->arr_ufp6_size[index] += sizes_ufp6[charIndex];
    }
}


void insert_words(SETS *set, const char **words, const int *sizes_ufp6_dict,const int ufp6_dict[][BITS - 1], int num_words) {
    /// Store number of words supported
    int num_words_supported = num_words;
    /// Check if words to be inserted are supported in UFP6
    check_words_supported_UFP6(set,words,num_words, &num_words_supported);

    /// Realloc memory for arr_word_size and arr_ufp6_size
    /// Time complexity: O(N) N = number of rows in set
    realloc_arr_words_size(set);
    realloc_arr_ufp6_size(set);

    /// Realloc mem for both matrix
    /// Time complexity: O(1)
    realloc_rows_matrix(set,set->rowsize);
    realloc_rows_ufp6(set, set->rowsize);

    int start_index = set->rowsize - num_words_supported;
    int k = 0;
    for (int i = start_index; i < set->rowsize && k < num_words && i >= 0; ++i,k++) {
        ///If Word Supported insert into set
        if(words[k] != NULL) {
            ///Store word size and ufp6 size calculated ,of new word to be inserted
            set->arr_word_size[i] = (int) strlen(words[k]);
            calc_ufp6_size(set, i, words[k], sizes_ufp6_dict);
            ///reallocate memory for both matrix
            realloc_col_ufp6(&set->matrix_ufp6[i], set->arr_ufp6_size[i]);
            realloc_col_word(&set->matrix[i], set->arr_word_size[i]);
            ///Insert word into both matrix
            insert_word_char(set, words[k], i);
            insert_ufp6(set, sizes_ufp6_dict, ufp6_dict, words[k], i);
        }else{
            i--;
        }
    }
}

void check_words_supported_UFP6(SETS *set,char **words, int W, int *prev_num_words){
    ///Check if words to be inserted are supported in UFP6
    for (int i = 0; i < W; ++i) {
        if (is_ufp6(words[i], (int) strlen(words[i])) == -1) {
            printf("Word %s not supported in UFP6 !!!\n", words[i]);
            words[i] = NULL;
            (*prev_num_words)--;
        } else {
            set->rowsize++;
        }
    }
}

void realloc_col_word(char **mat_row, int col_words_size) {
        *mat_row = (char*) realloc(*mat_row,col_words_size *sizeof(char));
        if(*mat_row == NULL){
            fperror("Realloc mat_row in realloc_col_word");
        }
}

void realloc_col_ufp6(int **mat_row, int col_words_size) {
    *mat_row = (int*) realloc(*mat_row,col_words_size * sizeof(int));
    if(*mat_row == NULL){
        fperror("Realloc mat_row in realloc_col_ufp6");
    }
}

void realloc_rows_matrix(SETS *set, int num_words) {
    set->matrix = (char **)realloc(set->matrix,num_words * sizeof(char*));

    if(set->matrix == NULL){
        fperror("Realloc matrix in realloc_rows_ufp6");
    }
}

void realloc_rows_ufp6(SETS *set, int num_words) {
    set->matrix_ufp6 = (int **)realloc(set->matrix_ufp6, num_words * sizeof(int*));
    if(set->matrix_ufp6 == NULL){
        fperror("Realloc matrix in realloc_rows_ufp6");
    }
}

void find_word_with_pattern(const SETS *set, const char *pattern, int **array_index) {
    int length_pattern =(int) strlen(pattern);
    ///Check If the current pattern is in UFP6 notation, 0-9 a-z A-Z
    if (is_ufp6(pattern, length_pattern) == -1){
        printf("Pattern \"%s\" not supported in UFP6 in find_words_with_pattern\n", pattern);
        return;
    }
    int dfa[MAX_UFP6][BITS - 1];
    /// Pre-process the pattern into dfa
    KMP (pattern, dfa);
    /// Search for words with given pattern
    /// And return address to array with indexes of words found in set with pattern
    *array_index = search_KMP(set, dfa, length_pattern);
    ///If found pattern in set
    if(*array_index != NULL){
        printf("\nWords found in set and UFP6 with pattern \"%s\" !!!\n", pattern);
        print_found_words_and_ufp6(set, *array_index);
    }else{
        printf("Pattern %s not found in set\n", pattern);
    }
}

/**
 * Function remove given Words and UFP6 representation from set
 * Time Complexity: O(W * N)
 * N = number of words in set W = number of words to remove
 * Extra Space: O(1)
 * @param set - pointer to SETS struct
 * @param words - pointer to an array of strings (words to be removed)
 * @param W - number of words to be removed
 */
void remove_Words(SETS *set, const char **words, int W) {;
    for (int i = 0; i < W; ++i) {
        find_word_in_set_and_remove(set, words[i]);
    }
}

/**
 * Function to find all occurrences given word in set comparing each word with given word
 * and remove all and shift all rows in both matrix and matrix_ufp6
 * Time Complexity: O(N) N = number of words in set //strcmp has a really low time complexity
 * because UFP6 words have MAX 7 bits
 * Extra Space: O(1)
 * @param set - pointer to SETS struct
 * @param word - pointer to word
 */
void find_word_in_set_and_remove(SETS *set,const char *word){
    if (word != NULL) {
        for (int i = 0; i < set->rowsize; i++){
            if (strcmp(word, set->matrix[i]) == 0 ){
               remove_word_from_set(set, i);
            }
        }
     }
}

/**
 * Function to remove UFP6 representation of given word adjusting rows from matrix_ufp6
 * Time Complexity: O(N) N = number of words in UFP6 matrix
 * Extra Space: O(1)
 * @param set - pointer to SETS struct
 * @param index - index of UFP6 representation to be removed
 */
void remove_UFP6(SETS *set, int index) {
    /// Check if the next row exists
    if (index + 1 < set->rowsize) {
        /// If current row size is lesser than the next row, reallocate memory
        if (set->arr_ufp6_size[index] < set->arr_ufp6_size[index + 1]) {
            realloc_col_ufp6(&set->matrix_ufp6[index], set->arr_ufp6_size[index + 1]);
        }
    }
    ///Copy from next row to current
    for (int i = 0; i < set->arr_ufp6_size[index + 1]; ++i) {
        set->matrix_ufp6[index][i] = set->matrix_ufp6[index + 1][i];
    }
}

int partition(SETS *set,int *arr, int lo, int hi, bool flag) {
    int i = lo;
    int j = hi + 1;

    int pivot = arr[lo];

    while (1){
        ///Scan from left to right as long as (arr[++i] < pivot)
        ///If flag set to 1 sort in asc order
        if (flag == 1){
            while(arr[++i] < pivot){
                if(i == hi) break;
            }

            ///Scan from right to left as long as (arr[--j] > pivot)
            while(arr[--j] > pivot){
                if(j == lo) break;
            }

        }else {
            ///Scan from left to right as long as (arr[++i] > pivot)
            ///In desc order
            while(arr[++i] > pivot){
                if(i == hi) break;
            }
            ///Scan from right to left as long as (arr[--j] < pivot)
            while(arr[--j] < pivot){
                if(j == lo) break;
            }
        }
        ///If pointers cross switch j with pivot and return pivot index
        if (i >= j){
            exch_rows_from_both_matrix(set,lo, j);
            exch(arr, lo, j);
            return j;
        }
        ///Swap rows in both matrix
        exch_rows_from_both_matrix(set, i, j);
        ///Swap with partitioning item arr_size
        exch(arr, i, j);
    }
}

void exch(int *arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void insertion_sort_int(SETS *set, int lo, int hi, bool flag){
    for (int i = lo; i <= hi; i++){
        for (int j = i; j > lo && ((flag && set->arr_word_size[j] < set->arr_word_size[j-1]) || (!flag && set->arr_word_size[j] > set->arr_word_size[j-1])); j--) {
            exch(set->arr_word_size, j, j - 1);
            exch_rows_from_both_matrix(set, j, j - 1);
        }
    }
}

void q_sort(SETS *set, int *arr, int lo, int hi, bool flag) {
    if(hi <= lo) return;
    ///Cutoff to small subarrays // CUTOFF = 10
    if (hi <= lo + CUTOFF - 1){
        insertion_sort_int(set, lo, hi,flag);
        return;
    }

    ///Improvement median of 3
    int median = findMedian(arr, lo, lo + (hi - lo) / 2, hi);
    ///Exchange arr[lo] with arr[median]
    exch(arr, lo, median);
    ///Exchange matrix[lo] with matrix[median], arr_size[lo] with arr_size[median],
    ///matrix_ufp6[lo] with matrix_ufp6[lo] and matrix_ufp6_size[lo] with matrix_ufp6_size[median]
    exch_rows_from_both_matrix(set, lo, median);

    int p = partition(set, arr, lo, hi, flag);
    q_sort(set, arr, lo, p - 1, flag);
    q_sort(set, arr, p + 1, hi, flag);
}

void knuth_shuffle(SETS *set) {
    srand(time(NULL));
    int index = 0;

    for (int i = set->rowsize - 1; i > 0; i--) {
        ///Generate random index
        index = rand() % i + 1;
        ///Exchange rows and indexes from both matrix
        ///and arrays holding the sizes in SETS struct
        exch(set->arr_word_size, index, i);
        exch_rows_from_both_matrix(set, index, i);
    }
}

int findMedian(const int *arr, int lo, int mid, int hi) {
    if(arr[lo] < arr[mid] && arr[mid] < arr[hi] || arr[hi] < arr[mid] && arr[lo] > arr[mid]){
        return  mid;
    }else if(arr[mid] < arr[lo] && arr[lo] > arr[hi] || arr[lo] < arr[mid] && arr[lo] > arr[hi]){
        return lo;
    }else{
        return hi;
    }
}

void sort_size(SETS *set, bool flag) {
    knuth_shuffle(set);
    q_sort(set,set->arr_word_size, 0, set->rowsize - 1, flag);
}

void exch_rows_matrix_char(SETS *set, int i, int j) {
    char  *temp = *(set->matrix + i);
    ///point row i to j
    *(set->matrix + i) = *(set->matrix + j);
    ///point j to i stored in temp
    *(set->matrix + j) = temp;
}

void exch_rows_matrix_ufp6(SETS *set, int i, int j) {
    int  *temp = *(set->matrix_ufp6 + i);
    ///point row i to j
    *(set->matrix_ufp6 + i) = *(set->matrix_ufp6 + j);
    ///point j to i stored in temp
    *(set->matrix_ufp6 + j) = temp;
    ///Exchange in arr_ufp6_size
    exch(set->arr_ufp6_size, i, j);
}

void exch_rows_from_both_matrix(SETS *set, int i, int j) {
    exch_rows_matrix_char(set, i, j);
    exch_rows_matrix_ufp6(set, i, j);
}


void is_sorted_matrix(const SETS *set, int N, bool flag) {
    for (int i = 0; i < N - 1; ++i) {
        if(flag == 1){
            if (strcmp(set->matrix[i], set->matrix[i + 1]) > 0) {
                printf("Not sorted in ASC order\n");
                return;
            }
        }else{
            if (strcmp(set->matrix[i], set->matrix[i + 1]) < 0) {
                printf("Not sorted in DESC order\n");
                return;
            }
        }
    }
    if(flag == 1){
        printf("Set sorted properly by alphabetical  ASC!!!\n");
    }else{
        printf("Set sorted properly by alphabetical  DESC !!!\n");
    }
}

void is_sorted_sizes(const SETS *set, int N, bool flag) {
        for (int i = 0; i < N - 1; ++i) {
            if (flag == 1) {
                if (set->arr_word_size[i] > set->arr_word_size[i + 1]) {
                    printf("Not sorted by ASC order\n");
                    return;
                }
            } else {
                if (set->arr_word_size[i] < set->arr_word_size[i + 1]) {
                    printf("Not sorted in DESC order\n");
                    return;
                }
            }
        }
        if(flag == 1){
            printf("Set sorted properly by words size ASC !!!\n");
        }else{
            printf("Set sorted properly by words size DESC !!!\n");
        }
}
void generatePermutations(int a[], int size, int N) {
    if (size == 1) {
        for (int i = 0; i < N; i++) {
            printf("%d ", a[i]);
        }
        putchar('\n');
        return;
    }

    for (int i = 0; i < size; i++) {
        generatePermutations(a, size - 1, N);
        // Swap elements based on the parity of 'size'
        if (size % 2 == 1) {
            exch(a, 0, size - 1);
        } else {
            exch(a, i, size - 1);
        }
    }
}
void combination_ufp6_in_both_sets(SETS *set1, SETS *set2) {
    int arr[10] = {1,0, 0,1};
    //generate_combination_without_repetition(set1->matrix_ufp6[1], set1->arr_ufp6_size[1]);
    //generate_combination_without_repetition(arr, 2);
    generatePermutations(arr, 4, 4);
}


void sort(SETS *set, char **aux_matrix, int **aux_matrix_ufp6, int lo, int hi, bool flag) {
     if(hi <= lo) return;
    ///Cutoff to insertion sort for small subarrays
    ///CUTOFF = 10
    if(hi <= lo + CUTOFF - 1){
        insertion_sort(set, lo, hi, 0, flag);
        return;
    }

    int mid = lo + (hi - lo) / 2;
    sort(set, aux_matrix, aux_matrix_ufp6, lo, mid, flag);
    sort(set, aux_matrix, aux_matrix_ufp6, mid + 1, hi, flag);
    ///Stop if already sorted
    if (strcmp(set->matrix[mid],  set->matrix[mid + 1]) <= 0) return;
    merge(set, aux_matrix,aux_matrix_ufp6, lo, mid, hi, flag);
}

void merge(SETS *set, char **aux_matrix, int **aux_matrix_ufp6, int lo, int mid, int hi, bool flag) {
    int i, j;
    for (int l = lo; l <= hi; ++l) {
        aux_matrix[l] = set->matrix[l];
        aux_matrix_ufp6[l] = set->matrix_ufp6[l];
    }
    i = lo;
    j = mid+1;
    ///Sort in ASC order
    if(flag == 1) {
        for (int k = lo; k <= hi; k++) {
            if (i > mid) {
               set->matrix_ufp6[k] = aux_matrix_ufp6[j];
               set->matrix[k] = aux_matrix[j++];
            } else if (j > hi) {
                set->matrix_ufp6[k] = aux_matrix_ufp6[i];
                set->matrix[k] = aux_matrix[i++];
            } else if (strcmp(aux_matrix[j], aux_matrix[i]) < 0) {
                set->matrix_ufp6[k] = aux_matrix_ufp6[j];
                set->matrix[k] = aux_matrix[j++];
            }  else {
             set->matrix_ufp6[k] = aux_matrix_ufp6[i];
                set->matrix[k] = aux_matrix[i++];
            }
        }
        ///Sort in DESC order
    }else{
        for (int k = lo; k <= hi; k++) {
            if (i > mid) {
                set->matrix_ufp6[k] = aux_matrix_ufp6[j];
                set->matrix[k] = aux_matrix[j++];
            } else if (j > hi) {
                set->matrix_ufp6[k] = aux_matrix_ufp6[i];
                set->matrix[k] = aux_matrix[i++];
            } else if (strcmp(aux_matrix[j], aux_matrix[i]) > 0) {
                set->matrix_ufp6[k] = aux_matrix_ufp6[j];
                set->matrix[k] = aux_matrix[j++];
            }  else {
                    set->matrix_ufp6[k] = aux_matrix_ufp6[i];
                    set->matrix[k] = aux_matrix[i++];
            }
        }
    }
}


void sort_by_alphabetical_order(SETS *set,const int *sizes_ufp6, bool flag){
    ///Allocate memory for auxiliary arrays of pointers to use in mergesort algorithm
    char **aux_mat = (char**) calloc(sizeof(char*), set->rowsize);
    if (aux_mat == NULL){
        fperror("Calloc aux_mat in sort_by_alphabetical_order");
    }
    int **aux_mat_ufp6 =  (int**) calloc(sizeof(int*), set->rowsize);
    if (aux_mat_ufp6 == NULL){
        fperror("Calloc aux_mat_ufp6 in sort_by_alphabetical_order");
    }

    sort(set, aux_mat, aux_mat_ufp6, 0, set->rowsize - 1, flag);
    ///After sort calculate sizes of words and UFP6 from set of words
    ///and store in both arrays in struct, instead of exchanging inside sort algorithm, to have less extra space
    ///This function has a time complexity of O(N) so it won't change much about mergesort Time Complexity
    calculate_sizes_words_and_ufp6_from_set(set, sizes_ufp6);

    free(aux_mat);
    free(aux_mat_ufp6);
}

void calculate_sizes_words_and_ufp6_from_set(SETS *set, const int *sizes_ufp6){
    for (int i = 0; i < set->rowsize; ++i) {
        set->arr_word_size[i] = (int) strlen(set->matrix[i]);
        calc_ufp6_size(set, i, set->matrix[i], sizes_ufp6);
    }
}

void write_to_txt_benchmark_sorting(char *fn, float time_delta_merge_s, float time_delta_msd, unsigned long number_words) {
    FILE *fp = fopen(fn, "a");
    if(fp == NULL){
        fperror("Error opening file in write_to_txt_benchmark_sorting");
    }
    fprintf(fp, "Benchmark for %lu words\n", number_words);
    fprintf(fp,"MSD time_delta : %2.6f MERGE SORT time_delta : %2.5f\n ", time_delta_msd, time_delta_merge_s);
    fclose(fp);
}
