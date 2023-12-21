#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include "functions_1.h"
#include "functions_2.h"

#define CUTOFF 10
#define M_KMP 8
#define R 5
#define C 5
#define RADIX 63



int main_functions_1(int argc , char **argv){

    return 0;
}

int **matrix_init_int(int row ,int col){
    // Allocate memory for array of pointers
    int** mat = (int**)calloc(row, sizeof(int*));

    if (mat == NULL) {
        printf("Matrix_init_int - row malloc\n");
        exit(1);
    }

    for (int i = 0; i < row; ++i) {
        // Allocate memory for each pointer (cols)
        *(mat+i) = (int*)calloc(col * BITS, sizeof(int));

        if (*(mat+i) == NULL) {
            printf("Matrix int col malloc\n");
            free(mat);
            exit(1);
        }
    }
    return mat;
}

char **matrix_init_char(int row ,int *size_cols){
    // Allocate memory for array of pointers
    char** mat = (char**) malloc(row * sizeof(char*));

    if (mat == NULL) {
        printf("Matrix int row malloc\n");
        exit(0);
    }

    for (int i = 0; i < row; ++i) {
        // Allocate memory for each pointer (cols)
        //for '\0'
        *(mat + i) = (char*)calloc(size_cols[i] + 1, sizeof(char));
       // *(mat + i) = (char*)calloc(BITS + 1, sizeof(char));
        if (mat[i] == NULL) {
            printf("Matrix char cols malloc\n");
            exit(0);
        }
    }
    return mat;
}

void print_matrix_int(const SETS *set) {
    for (int i = 0; i < set->rowsize; ++i){
        for (int j = 0; j < *(set->arr_ufp6_size + i); ++j) {
            printf("%d ",*(*(set->matrix_ufp6 + i) + j));
        }
        putchar('\n');
    }
}

void print_matrix_char(const SETS *set) {
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
        //calculate_bin_sizes ( *(*(set->));
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
        word_length_arr[i] = (rand() % (BITS - 1)) + 1 ;
    }
}

char gen_rnd_char(){
    int random_number;
    /* Generate random number between 'a' and 'z' */
    random_number = 'a' + rand() % 26;
    return (char) random_number;
}

void matrix_rnd_char_gen(SETS *set) {
    /* seed to generate random numbers */
    seed_random();
    //srand((unsigned int)time(NULL));
    int j = 0;
    for (int i = 0; i < set->rowsize; ++i) {
        for (j = 0; j < set->arr_word_size[i]; ++j) {
            *(*(set->matrix + i) +j) = gen_rnd_char();
        }
        //terminate each word with '\0'
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


void freemem(SETS *set){
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
            freemem(set);
            exit(0);
        }

        for (int i = 0; i < set->rowsize; ++i) {
            realloc_col_word(&*(set->matrix +i),*(set->arr_word_size + i));
        }
}

void init_arr_word_size(SETS *set){
    set->arr_word_size = (int *) calloc(set->rowsize, sizeof(int));

    if((set->arr_word_size) == NULL){
        printf("Array word size calloc\n");
        freemem(set);
        exit(0);
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
                freemem(set);
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


void msdRadixSort_r(SETS *set, char **aux,int **aux_ufp6,const int *arr_sizes_ufp6, int lo, int hi, int d, bool flag) {
    if (hi <= lo) return;
    //Store frequencies of each char
    int count[RADIX + 2] = {0};

    //Add frequencies of each char to count array
    for (int i = lo; i <= hi; i++) {
        char currentChar = *(*(set->matrix + i) + d);
        //calculate Index to insert into count
        int charIndex = calculate_index_char(currentChar, flag);
        // + 2 for after store cumulative frequencies
        count[charIndex + 2]++;
    }
  
    //Update cumulative frequencies of each char
    for (int r = 0; r < RADIX + 1; ++r) {
        count[r + 1] += count[r];
    }

    // Insert words into aux array in the right order //
    for (int i = lo; i <= hi; ++i) {
        // Get char from row i col d
        char currentChar = *(*(set->matrix + i) + d);
        // find right index in RADIX
        int charIndex = calculate_index_char(currentChar, flag);
        int index = *(count + charIndex + 1);
        // insert into aux to aux and aux_ufp6 pointers to rows in sorted positions
        *(aux_ufp6 + index) = *(set->matrix_ufp6 + i);
        *(aux + index) = *(set->matrix + i);
        //increment in count array to insert in next pos
        count[charIndex + 1]++;
    }

    // Copy values from aux to arr //
    for (int i = lo; i <= hi; ++i) {
        // aux is the sorted array, so change *(set->matrix + i) to point to sorted row from aux
        *(set->matrix + i) = *(aux + i - lo);
        *(set->matrix_ufp6 + i) = *(aux_ufp6 + i - lo);
        // calculate size of ufp6 representation moved to ufp6_matrix and store into arr_sizes_ufp6
        calc_ufp6_size(set, i, *(set->matrix + i), arr_sizes_ufp6);
        // calculate size of word moved to matrix and store into arr_word_sizes
        *(set->arr_word_size + i) = (int)strlen(*(set->matrix + i));
    }

    for (int r = 0; r < RADIX; ++r) {
        //Calculate lower bound of a set of words
        int low = lo + count[r];
        //Calculate higher bound of a set of words
        int high = lo + count[r + 1] - 1;
        //recursive call to sort sets between low and hi
        //d + 1 to go to next column from left to right
        msdRadixSort_r(set, aux, aux_ufp6,arr_sizes_ufp6, low, high, d + 1, flag);
    }
}

void msdRadixSort(SETS *set,const int *array_sizes_ufp6 ,int lo, int hi, bool flag) {
    //temp array of char pointers
    char **aux = (char **)malloc((hi - lo + 1) * sizeof(char *));
    if (aux == NULL) {
        fperror("aux in msdRadixSort Memory Allocation");
    }
    //temp array of int pointers
    int **aux_ufp6 = (int **)malloc((hi - lo + 1) * sizeof(int *));
    if (aux_ufp6 == NULL) {
        fperror("aux_ufp6 in msdRadixSort Memory Allocation");
    }

    if(flag == 1){
        // For small arrays, use Insertion Sort because msd has too much overhead for small arrays
        if (hi - lo <= CUTOFF) {
            insertion_sort_char(set, hi, flag);
            return;
        }
        msdRadixSort_r(set, aux,aux_ufp6,array_sizes_ufp6, lo, hi - 1, 0,flag);
    }else{
        // For small arrays, use Insertion Sort because msd has too much overhead for small subarrays
        if (hi - lo <= CUTOFF) {
            insertion_sort_char(set, hi, flag);
            return;
        }

        msdRadixSort_r(set, aux,aux_ufp6,array_sizes_ufp6, lo, hi - 1, 0,flag);
    }
    free(aux);
}

void FillArray_Word_Size(SETS *set) {
    for (int i = 0; i < set->rowsize; ++i) {
        set->arr_word_size[i] =(int) strlen(set->matrix[i]);
    }
}

void ufp6_dictionary(int ufp6_dict[][BITS], int *size_ufp6) {
    int index = 0;
    // Convert '0' to '9' to ufp6
    for (char digit = '0'; digit <= '9'; digit++) {
        charToBinary(digit - '0', ufp6_dict[index], size_ufp6);
        if(digit - '0' == 0 || digit - '0' == 1){
            size_ufp6[index] = 1;
        }else{
            size_ufp6[index] = (int) log2((digit - '0') ) + 1;
        }
        index++;
    }

    // Convert 'a' to 'z' to ufp6
    for (char letter = 'a'; letter <= 'z'; letter++) {
        size_ufp6[index] = log2((letter - 'a' + 10)) + 1;
        charToBinary(letter - 'a' + 10, ufp6_dict[index], size_ufp6);
        index++;
    }

    // Convert 'A' to 'Z' to ufp6
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        size_ufp6[index] = log2((letter - 'A' + 36)) + 1;
        charToBinary(letter - 'A' + 36, ufp6_dict[index], size_ufp6);
        index++;
    }
}


void charToBinary(int c, int *result, int *size_bin) {
    int numBits = 0;
    // Because log2(0) -inf
    // We use numBits to only store the right number of bits of each value
    // log2(value) because for example  2 = 10 so 2^1 is the number of bits needed
    if(c == 0){
        numBits = 1;
    }else{
      numBits =(int) (log2(c) + 1);
    }

    for (int i = numBits - 1; i >= 0; i--) {
        result[numBits - 1 - i] = (c >> i) & 1;
    }
}

void print_ufp6_dictionary(int (*bin_d)[BITS], int *size_ufp6) {
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


void encode_word(const char* word, int *encoded, int *word_bits_size, int k, const int sizes_ufp6[], const int ufp6_dict[MAX_UFP6][BITS]) {
    if(ufp6_dict[0][0] != 0) fperror("Bin_dict not precomputed endcode_matrix_words");
    int index = 0;
    int len =(int) strlen(word);
    word_bits_size[k] = 0; //initialize to 0 the array with ufp6 size
    for (int i = 0; i < len; i++) {
        char currentChar = word[i];

        // Check if the character is a valid key in dictionary
        if ((currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= '0' && currentChar <= '9') || (currentChar >= 'a' && currentChar <= 'z')) {
            int charIndex = 0;
            if(currentChar >= 'A' && currentChar <= 'Z'){
                charIndex = (currentChar - 'A' + 36);
            }else if(currentChar >= '0' && currentChar <= '9'){
                charIndex = (currentChar - '0');
            }else{
                charIndex = (currentChar - 'a' + 10);
            }

            // Store the size of bits each word
            word_bits_size[k] += sizes_ufp6[charIndex];

            // Copy the binary representation to the encoded array
            for (int j = 0; j < sizes_ufp6[charIndex]; j++) {
                encoded[index++] = ufp6_dict[charIndex][j];
            }
        }
    }
}


void encode_matrix_words(SETS *set, int *sizes_ufp6_dict, int ufp6_dict[][BITS]) {
    for (int i = 0; i < set->rowsize; ++i) {
        encode_word(set->matrix[i], set->matrix_ufp6[i], set->arr_ufp6_size, i, sizes_ufp6_dict, ufp6_dict);
    }
}


int *arr_bits_size_calloc(int *arr, int N) {
    arr = (int*) calloc(sizeof(int) , N);

    if(arr == NULL){
        fperror("arr_ufp6_size malloc");
    }
    return arr;
}

void calculate_bin_sizes(char *word, int *arr_bin_sizes,int *words_bin_sizes, int N, int w) {
    for (int i = 0; i < N; i++) {
        char currentChar = word[i];

        // Check if the character is a valid key in dictionary
        if ((currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= '0' && currentChar <= '9') ||
            (currentChar >= 'a' && currentChar <= 'z')) {
            int charIndex = 0;
            if (currentChar >= 'A' && currentChar <= 'Z') {
                charIndex = (currentChar - 'A' + 36);
            } else if (currentChar >= '0' && currentChar <= '9') {
                charIndex = (currentChar - '0');
            } else {
                charIndex = (currentChar - 'a' + 10);
            }

            // Store the size of each word
            words_bin_sizes[w] += arr_bin_sizes[charIndex];
        }
    }
}

/**
 * Function to Pre-compute the pattern building a DFA
 */
void KMP (const char pattern[BITS], int dfa[MAX_UFP6][BITS]) {
    int indexChar = 0;
    int pattern_size =(int) strlen(pattern);

    //Initialize DFA to 0
    for (int i = 0; i < MAX_UFP6; ++i) {
        //Until word size
        for (int j = 0; j < pattern_size; ++j) {
            dfa[i][j] = 0;
        }
    }

    //Calculate index of char in UFP6 ASCII table in ASC order
    indexChar = calculate_index_char(pattern[0], 1);

    dfa[indexChar][0] = 1;              //Initialize first col of given row to 1

    for (int X = 0, j = 1; j < pattern_size; ++j){
        for (int c = 0; c < MAX_UFP6 ; ++c) {
            //Calculate index char in ufp6 ASCII table in ASC order
           indexChar = calculate_index_char(pattern[j], 1);
          
           dfa[c][j] = dfa[c][X];       //copy mismatch cases
        }
        dfa[indexChar][j] = j + 1;      //set match case
        X = dfa[indexChar][X];          //update restart state
    }
   // print_kmp(dfa);
}

int calculate_index_char(char currentChar, bool flag) {
    int charIndex = 0;
    //if char is supported in UFP6
    if ((currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= '0' && currentChar <= '9') ||
        (currentChar >= 'a' && currentChar <= 'z')) {
        //Calculate in ASC order
        if (flag == 1) {
            if (currentChar >= 'A' && currentChar <= 'Z') {
                charIndex = (currentChar - 'A' + 36);
            } else if (currentChar >= '0' && currentChar <= '9') {
                charIndex = (currentChar - '0');
            } else {
                charIndex = (currentChar - 'a' + 10);
            }
        } else {
            //Reverse subtraction to calculate index in DESC order
            if (currentChar >= 'A' && currentChar <= 'Z') {
                charIndex = ('Z' - currentChar);
            } else if (currentChar >= '0' && currentChar <= '9') {
                charIndex = ('9' - currentChar + 36);
            } else {
                charIndex = ('z' - currentChar + 10);
            }
        }
    }
    return charIndex;
}

/**
 * Function to search for a given word given size and pre-computed DFA
 */
int *search_KMP(SETS *set, int dfa[MAX_UFP6][BITS], int word_size){
    int i , j;
    int indexChar = 0;
    int *arr_index = (int*) calloc(set->rowsize,sizeof(int));

    if(arr_index == NULL){
        fperror("Calloc arr_index in search_KMP");
    }
    //start pos of arr_index where we want to insert all index that contains the given word
    //start to 1 to store in pos 0 the count of indexes
    int l = 1;
    for (int k = 0; k < set->rowsize; ++k) {
        for (i = 0, j = 0; i < strlen(*(set->matrix + k)) && j < word_size ; ++i) {
            //Calculate index char in ufp6 ASCII table in ASC order
            indexChar = calculate_index_char(*(*(set->matrix + k ) + i), 1);
            j = dfa[indexChar][j];          //no backup
        }
        // Search for words with the exact size of the pattern ex: ola has size 3 and the words we found can be ola , olas etc
        //And if found word in a row (if j gets to last state in DFA)
        if (j == word_size && strlen(*(set->matrix + k )) == word_size){
            arr_index[l++] = k;
        }
    }
    //store in pos 0 of array the count of words found with pattern
    arr_index[0] = l-1;
    //if found words return array
    if(arr_index[0] != 0)
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
   // printf("Words Found and their UFP6!!!\n");
    // start in 1 because storing in index 0 the count of words found // if *array_index == 0 , no words found
    for (int k = 1; k <= *array_index; ++k) {
        printf("Index -> %d\n", *(array_index + k));
        printf("Word = %s |", *(set->matrix + (*(array_index + k))));
        printf(" UFP6 = ");
        for (int i = 0; i < *(set->arr_ufp6_size + (*(array_index + k))); i++) {
           // printf("%d", *(*(set->matrix_ufp6 + (*(array_index + k))))+ i);
            printf("%d", set->matrix_ufp6[array_index[k]][i]);
        }
        putchar('\n');
    }
}

/**
 * Find words in a given set using KMP Algorithm
 * This function has Time Complexity of O(W (M + N))
 * M = length of longest pattern N = number of rows (words in set) W = number of words to search for
 */
void find_Words(const SETS *set, const char **words, int W,const char *fn, bool flag) {
    if (W <= 0) {
        fperror("Incorrect number words (less or equal to 0) in find_Words");
    }

    //array to store the indexes of the words found in set
    int *array_index = NULL;
    // For each word
    for (int i = 0; i <W; ++i) {
        find_Word(set, words[i], &array_index);
        //If flag == 1 write words found and their respective ufp6 representation to a txt file
        if(flag == 1){
            write_words_found_to_txt_set(set, array_index, fn);
        }
    }
}

void remove_Word (SETS *set,const int *arr_index_words_found) {
    //For each index of words_found
    for (int i = 0; i < *arr_index_words_found; ++i){
        //adjust rows of matrix and matrix_ufp6 moving next row to previous
        for (int j = *(arr_index_words_found + 1); j < set->rowsize - 1; ++j) {
            //Realloc row size if previous row has lesser size than the next row
            realloc_row_remove(set, i);
            //copy values from prev to current
            *(set->arr_word_size + j) = *(set->arr_word_size + j + 1);
            *(set->arr_ufp6_size + j) = *(set->arr_ufp6_size + j + 1);
            strcpy(set->matrix[j], set->matrix[j + 1]);
            //ufp6
            remove_UFP6(set, j);
        }
        //adjust number of rows of matrix after deleting and adjusted rows
        set->rowsize--;
        //free row deleted
        free(set->matrix[set->rowsize + 1]);
        free(set->matrix_ufp6[set->rowsize + 1]);
        set->arr_word_size[set->rowsize + 1] = 0;
        set->arr_ufp6_size[set->rowsize + 1] = 0;
    }
}


void  realloc_row_remove(SETS *set, int row) {
    //Realloc row size if previous row has lesser size than the next row
    if(set->arr_word_size[row] < set->arr_word_size[row + 1] ){
        set->matrix[row] =  realloc(set->matrix[row], sizeof(char) * set->arr_word_size[row + 1]);
        if(set->matrix[row] == NULL){
            fperror(" REALLOC in realloc_row_remove");
        }
    }
}

void compute_words_size(const char **words, int *words_index ,int W) {
    for (int i = 0; i < W; ++i) {
        words_index[i] = (int) strlen(words[i]);
    }
}

void sets_struct_init(SETS *set, int num_words) {
    set->rowsize = num_words;
    set->colsize_encode =C * BITS;
    init_arr_word_size(set);
    rnd_word_size_gen(set->arr_word_size, set->rowsize);
    set->matrix_ufp6 = matrix_init_int(set->rowsize, C);
    set->matrix = matrix_init_char(set->rowsize,set->arr_word_size);
    // set1.arr_ufp6_size = arr_bits_size_calloc(set1.arr_ufp6_size, set1.rowsize);
    set->arr_ufp6_size = (int*) calloc(set->rowsize, sizeof(int));
}

// clock function to measure processor time and use as a seed
void seed_random() {
    unsigned  int seed = (unsigned int)time(NULL) + (unsigned  int) clock();
    srand(seed);
}

int is_ufp6(const char *word) {
    char currentChar = '\0';
    for (int i = 0; i < strlen(word); ++i) {
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
    /* Realloc memory for arr_ufp6_size */
    set->arr_ufp6_size = (int *) realloc(set->arr_ufp6_size, set->rowsize * sizeof(int));

    if(set->arr_word_size == NULL){
        fperror("Realloc arr_ufp6_size failed in realloc_arr_ufp6_size !");
    }
}

void insert_ufp6(SETS *set, const int sizes_ufp6_dict[], int ufp6_dict[][BITS], const char *word, int index) {
    encode_word(word, set->matrix_ufp6[index], set->arr_ufp6_size, index, sizes_ufp6_dict, ufp6_dict);
}

void calc_ufp6_size(SETS *set, int index,const char *word, const int *sizes_ufp6){
    set->arr_ufp6_size[index] =0;
    for (int i = 0; i < strlen(word); ++i) {
        char currentChar = word[i];

        // Check if the character is a valid key in dictionary
        if ((currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= '0' && currentChar <= '9') ||
            (currentChar >= 'a' && currentChar <= 'z')) {
            int charIndex = 0;
            if (currentChar >= 'A' && currentChar <= 'Z') {
                charIndex = (currentChar - 'A' + 36);
            } else if (currentChar >= '0' && currentChar <= '9') {
                charIndex = (currentChar - '0');
            } else {
                charIndex = (currentChar - 'a' + 10);
            }

            // Store the size of ufp6 representation of each word
            set->arr_ufp6_size[index] += sizes_ufp6[charIndex];
        }
    }
}


void insert_words(SETS *set, const char **words, const int *sizes_ufp6_dict, int ufp6_dict[][BITS], int num_words) {
    set->rowsize += num_words;
    /* Realloc memory for arr_word_size and arr_ufp6_size */
    realloc_arr_words_size(set);
    realloc_arr_ufp6_size(set);

    /* Realloc mem for both matrix */
    realloc_rows_matrix(set,set->rowsize);
    realloc_rows_ufp6(set, set->rowsize);

    for (int i = set->rowsize - num_words, k = 0; i < set->rowsize && k < num_words; ++i,k++) {
        //calculate word size and ufp6 size and store in set
        set->arr_word_size[i] = (int) strlen(words[k]);
        calc_ufp6_size(set, i, words[k], sizes_ufp6_dict);
        //reallocate memory for both matrix
        realloc_col_ufp6(&set->matrix_ufp6[i], set->arr_ufp6_size[i]);
        realloc_col_word(&set->matrix[i],set->arr_word_size[i]);
        insert_word_char(set,words[k],i);
        insert_ufp6(set, sizes_ufp6_dict, ufp6_dict, words[k], i);
    }
}

void realloc_col_word(char **mat_row, int col_words_size) {
        *mat_row = (char*) realloc(*mat_row,col_words_size *sizeof(char));
        if(*mat_row == NULL){
            fperror("Realloc mat_row in realloc_col_word");
        }
}

void realloc_col_ufp6(int **mat_row, int col_words_size) {
    *mat_row = (int*) realloc(*mat_row,col_words_size *sizeof(int));
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

void find_Word(SETS *set, const char *word, int **array_index) {
    // If the current word is in UFP6 notation, 0-9 a-z A-Z
    if (is_ufp6(word) == -1) fperror("Word not supported in UFP6 in find_Words");
    int dfa[MAX_UFP6][BITS];
    // Pre-process the pattern into dfa
    KMP (word, dfa);
    // Search for words with the exact size of the pattern ex: ola has size 3 and the words we found can be ola , olas etc
    // And return pointer to array with indexes of words found
    *array_index = search_KMP(set, dfa, strlen(word));
    //if found word in set
    if(array_index != NULL){
        print_found_words_and_ufp6(set, *array_index);
    }else{
        printf("Word %s not found in set\n", word);
    }
}

void remove_Words(SETS *set, const char **words, int W) {
    int *array_index = (int*) calloc(set->rowsize, sizeof(int));
    if(array_index == NULL){
        fperror("Calloc array_index in remove_");
    }
    for (int i = 0; i < W; ++i) {
        printf("word found \n");
        find_Word(set, words[i], &array_index);
        remove_Word(set, array_index);
    }
    free(array_index);
}

void remove_UFP6(SETS *set, int index) {
    //if previous row size is lesser than next row
    if(set->arr_ufp6_size[index] < set->arr_ufp6_size[index + 1] ){
        realloc_col_ufp6(&set->matrix_ufp6[index], set->arr_ufp6_size[index + 1]);
    }
    for (int i = 0; i < set->arr_ufp6_size[index + 1]; ++i) {
        set->matrix_ufp6[index][i] = set->matrix_ufp6[index + 1][i];
    }
}

int partition(SETS *set,int *arr, int lo, int hi, bool flag) {
    int i = lo;
    int j = hi + 1;

    int pivot = arr[lo];

    while(1){
        //Scan from left to right as long as (arr[++i] < pivot)
        //if flag to 1 sort in asc order
        if(flag == 1){
            while(arr[++i] < pivot){
                if(i == hi) break;
            }

            //Scan from right to left as long as (arr[--j] > pivot)
            while(arr[--j] > pivot){
                if(j == lo) break;
            }

        }else{
            //Scan from left to right as long as (arr[++i] > pivot)
            //in desc order
            while(arr[++i] > pivot){
                if(i == hi) break;
            }
            //Scan from right to left as long as (arr[--j] < pivot)
            while(arr[--j] < pivot){
                if(j == lo) break;
            }
        }

        //if pointers cross switch j with pivot and return pivot index
        if(i >= j){
            exch_rows_from_both_matrix(set,lo, j);
            exch(arr, lo, j);
            return j;
        }
        //swap rows in both matrix
        exch_rows_from_both_matrix(set, i, j);
        //swap with partitioning item arr_size
        exch(arr, i, j);
    }
}

void exch(int *arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void q_sort(SETS *set, int *arr, int lo, int hi, bool flag) {
    //Cutoff to small subarrays // size 10
    if(hi <= lo) return;

    //Improvement median of 3
    int median = findMedian(arr, lo, lo + (hi-lo)/2, hi);
    //Exchange arr[lo] with arr[median]
    exch(arr, lo, median);
    //Exchange matrix[lo] with matrix[median], arr_size[lo] with arr_size[median],
    //matrix_ufp6[lo] with matrix_ufp6[lo] and matrix_ufp6_size[lo] with matrix_ufp6_size[median]
    exch_rows_from_both_matrix(set, lo, median);

    int p = partition(set, arr, lo, hi, flag);
    q_sort(set, arr, lo, p - 1, flag);
    q_sort(set, arr, p+1, hi, flag);
}

void knuth_shuffle(int *arr, int N) {
    srand(time(NULL));
    int index = 0;

    for (int i = N - 1; i > 0; i--) {
        index = rand() % i + 1;
        exch(arr, index, i);
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
    q_sort(set,set->arr_word_size, 0, set->rowsize - 1, flag);
}

void exch_rows_matrix_char(SETS *set, int i, int j) {
    char  *temp = *(set->matrix + i);
    //point row i to j
    *(set->matrix + i) = *(set->matrix + j);
    //point j to i stored in temp
    *(set->matrix + j) = temp;
}

void exch_rows_matrix_ufp6(SETS *set, int i, int j) {
    int  *temp = *(set->matrix_ufp6 + i);
    //point row i to j
    *(set->matrix_ufp6 + i) = *(set->matrix_ufp6 + j);
    //point j to i stored in temp
    *(set->matrix_ufp6 + j) = temp;
    //Exchange in arr_ufp6_size
    exch(set->arr_ufp6_size, i, j);
}

void exch_rows_from_both_matrix(SETS *set, int i, int j) {
    exch_rows_matrix_char(set, i, j);
    exch_rows_matrix_ufp6(set, i, j);
}

void insertion_sort_char(SETS *set, int N, bool flag) {
    int i = 0, j = 0;
    char *key = NULL;
    //In Ascending order
    if (flag == 1) {
        for (i = 1; i < N; i++) {
            //store in key row[i]
            key = set->matrix[i];
            j = i - 1;
            //swap elements from j until 0 if is not sorted
            while (j >= 0 && strcmp(set->matrix[j], key) > 0) {
                //swap row j + 1 with j
                set->matrix[j + 1] = set->matrix[j];
                //exchange rows from matrix_ufp6 to sort properly and in arr_ufp6_sizes
                exch_rows_matrix_ufp6(set, j + 1, j);
                //exchange sizes in arr_word_size
                int temp = set->arr_word_size[j + 1];
                set->arr_word_size[j + 1] = set->arr_word_size[j];
                set->arr_word_size[j] = temp;
                j--;
            }
            //swap row j + 1 with j
            set->matrix[j + 1] = key;
        }
        //In descending order
    } else {
        for (i = N - 1; i >= 0; i--) {
            key = set->matrix[i];
            j = i + 1;
            //swap elements from j until N if is not sorted
            while (j < N && strcmp(set->matrix[j], key) > 0) {
                //swap row in matrix j + 1 with j
                set->matrix[j - 1] = set->matrix[j];
                //exchange rows from matrix_ufp6 to sort properly and in arr_ufp6_sizes
                exch_rows_matrix_ufp6(set, j - 1, j);
                //exchange sizes in arr_word_size
                int temp = set->arr_word_size[j - 1];
                set->arr_word_size[j - 1] = set->arr_word_size[j];
                set->arr_word_size[j] = temp;
                j++;
            }
            set->matrix[j - 1] = key;
        }
    }
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
  //  generate_combination_without_repetition(set1->matrix_ufp6[1], set1->arr_ufp6_size[1]);
    //generate_combination_without_repetition(arr, 2);
    generatePermutations(arr, 4, 4);
}