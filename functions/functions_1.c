#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <ctype.h>
#include <math.h>
#include <fcntl.h>
#include "functions_1.h"



#define R 5
#define C 5
#define WORD_LENGTH 5
#define BITS 7
#define RADIX 36
#define TIMER_START() gettimeofday(&tv1, NULL)
#define TIMER_STOP() \
gettimeofday(&tv2, NULL);    \
timersub(&tv2, &tv1, &tv);   \
time_delta = (float)tv.tv_sec + tv.tv_usec / 1000000.0
#define M_KMP 8



int main_functions_1(int argc , char **argv){
    struct timeval tv1, tv2, tv;
    float time_delta;

    /*
     * Initialize set1  *
                        */
    SETS set1;
    set1.rowsize = R;
    set1.colsize_encode =C * BITS;
    init_arr_word_size(&set1);
    rnd_word_size_gen(set1.arr_word_size, set1.rowsize);
    set1.matrix_encode = matrix_init_int(set1.rowsize,C);
    set1.matrix = matrix_init_char(set1.rowsize,set1.arr_word_size);
   // set1.arr_bits_size = arr_bits_size(set1.arr_bits_size, set1.rowsize);
    set1.arr_bits_size = calloc(set1.rowsize, sizeof(int));

    /*
    * Initialize set2  *
                       */
   /* SETS set2;
    set2.matrix_encode = matrix_init_int(R,C);
    set2.matrix = matrix_init_char(R,C);
    set2.colsize_encode =C * BITS;
    set2.rowsize = R;
    init_arr_word_size(&set2);

    /* Generate words for both sets  */
    matrix_rnd_char_gen(&set1);
    print_matrix_char(&set1);
    // matrix_rnd_char_gen(&set2);

    TIMER_START();

    /* ENCODE V1  */
    // encode(&set1);
    //printf("\nHelloo ENCODe\n");
    // print_matrix_char(set1);
    // encode(&set2);

   /* ENCODE V2 */
    int dic[MAX_UFP6][BITS + 1];
    int sizes[MAX_UFP6];

    binary_dictionary(dic, 3, sizes);
    // print_binary_dictionary(dic, sizes);
    //encode_matrix_words(&set1, sizes, dic);

    /* 3)*/

    /* Insert word */
      insert_word_char(&set1, set1.rowsize, 2);
      encode_matrix_words(&set1, sizes, dic);

    /* Remove word */
    char pattern[BITS + 1] = "ola";
    int dfa[MAX_UFP6][MAX_UFP6];
    int *index_words_found = calloc(set1.rowsize, sizeof(int));
    KMP(pattern,dfa);
    index_words_found =  search_KMP(&set1, dfa, strlen(pattern));

    int *arr_words = malloc(sizeof(int) * index_words_found[0]);

    arr_words = find_Word(&set1, strlen(pattern), index_words_found);

    //start in 1 because pos 0 is storing size of array;
    for (int i = 1; i < arr_words[0]; ++i) {
        printf("%d\n", arr_words[i]);
    }
    remove_Word(&set1, arr_words);

    encode_matrix_words(&set1,sizes,dic);

    free(arr_words);

    /* 5) */

   /* char pattern[BITS + 1] = "ola";
    int dfa[MAX_UFP6][MAX_UFP6];
    int *index_words_found = calloc(set1.rowsize, sizeof(int));
    KMP(pattern,dfa);
    index_words_found =  search_KMP(&set1, dfa, strlen(pattern));
    print_KMP_BinMatches(&set1, index_words_found);

    free(index_words_found);*/

   // print_kmp(dfa);



    /* Print both sets  */
    puts("SET 1");
    print_matrix_char(&set1);
    puts("SET 1 ENCODE");
    print_matrix_int(&set1);
   /* puts("SET 2");
    print_matrix_char(set2);
    puts("SET 2 ENCODE");
    print_matrix_int(set2);

    /* Sort Both arrays in descending order*/
   /* msdRadixSort(&set1, 0, set1.rowsize,0);
    puts("SET 1 . SORTED DESC");
    print_matrix_char(set1);
    encode(&set1);
    print_matrix_int(set1);*/
   /* msdRadixSort(&set2, 0, set2.rowsize, 0);
    puts("SET 2 . SORTED");
    print_matrix_char(set2);
    encode(&set2);
    print_matrix_int(set2);
     /* Sort Both arrays in descending order*/
    /* msdRadixSort(&set1, 0, set1.rowsize,1);
    puts("SET 1 . SORTED ASC");
    print_matrix_char(set1);
    encode(&set1);
    print_matrix_int(set1);
    puts("SET 2 . SORTED ASC");
    msdRadixSort(&set2, 0, set1.rowsize,1);
    print_matrix_char(set2);
    encode(&set2);
    print_matrix_int(set2);*/


   /* Print array word size */
    //print_arr_word_size(&set1);
    //print_array(set1.arr_bits_size, set1.rowsize);

   // write_matrix_char_txt(set1.matrix, set1.rowsize, set1.arr_word_size, "sets_test.txt");

    /* free memory  */
   /* freemem(&set1);
    freemem(&set2);

    TIMER_STOP();
    fprintf(stdout, "%f secs\n", time_delta);*/


    //print_matrix_char(set1);
    //print_matrix_int(set1);

    freemem(&set1);
    free(set1.arr_word_size);

    TIMER_STOP();
    fprintf(stdout, "%f secs\n", time_delta);

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
        *(mat+i) = (int*)calloc(col * 7, sizeof(int));

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
        *(mat + i) = (char*)calloc(size_cols[i], sizeof(char));
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
        for (int j = 0; j < *(set->arr_bits_size + i); ++j) {
            printf(" %d",*(*(set->matrix_encode + i) +j));
        }
        putchar('\n');
    }
}

//Apontador porque é mais eficiente do que uma cópia
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
                for (int l = BITS - 1; l >= 0 && j < set->arr_bits_size[i] ; l--, j++) {
                    *(*(set->matrix_encode + i) +j) = (digit >> l) & 1;
                }
            } else if (charCalc >= 'a' && charCalc <= 'z') {
                /* 10 represents the beginning of letters */
                int letter = charCalc - 'a' + 10;
                for (int l = BITS -1; l >= 0 && j < set->arr_bits_size[i];l--, j++) {
                    /* when last digit is 0 break from the loop, so it won't store the left 0's */
                    if ((letter >> l) == 0) {
                        *(*(set->matrix_encode + i) + j) = -1;
                    } else {
                        *(*(set->matrix_encode + i) + j) = (letter >> l) & 1;
                    }
                }
            } else if (charCalc >= 'A' && charCalc <= 'Z') {
                /* 'a' is the value 36 (A = 10 a = 10 + 26) */
                int letter = charCalc - 'A' + 36;
                for (int l = BITS -1; l >= 0 && j < set->arr_bits_size[i]; l--, j++) {
                    if((letter >>l) == 0) break;
                    *(*(set->matrix_encode + i) +j) = (letter >> l) & 1;
                }
            }
        }
    }
}

void rnd_word_size_gen(int *word_length_arr, int W) {
    /* seed to generate random numbers */
    srand((unsigned int)time(NULL));
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
    srand((unsigned int)time(NULL));
    for (int i = 0; i < set->rowsize; ++i) {
        for (int j = 0; j < set->arr_word_size[i]; ++j) {
            *(*(set->matrix + i) +j) = gen_rnd_char();
        }
    }

}



void insert_word_char(SETS *set,int start_row, int number_words) {
    /* Start_row always max num of lines */
    set->rowsize += number_words;
    /* Realloc mem for both matrix */

    char word[BITS + 1] = " ";
    for (int i = start_row; i < set->rowsize; ++i) {

        if (fscanf(stdin, "%s", word) == EOF) {
            printf("Failed to read the word.\n");
            freemem(set);
            return;
        }
        /* store size of new word in arr_word_size for delim */
        set->arr_word_size[i] = (int) strlen(word);

        matrix_realloc(set);
        matrix_encode_realloc(set);

        for (int j = 0; j < set->arr_word_size[i]; ++j) {
            //printf("%c", word[j]);
            *(*(set->matrix + i) + j) = word[j];
            /* if the word is smaller than colsize_char fill the rest with ' ' */
            if (j >= strlen(word))
                *(*(set->matrix + i) + j) = ' ';
        }
    }


}

void insert_word_short(SETS *set,int start_row, int number_words) {
        // Start_row é sempre o valor maximo no de linhas

}

void freemem(SETS *set){

        for (int i = 0; i < set->rowsize; ++i) {
            free(set->matrix_encode[i]);
            set->matrix_encode[i] =NULL;

            free(set->matrix[i]);
            set->matrix[i] =NULL;
        }

        free(set->matrix);
        set->matrix =NULL;

        free(set->matrix_encode);
        set->matrix_encode =NULL;

        free(set->arr_word_size);
        set->arr_word_size = NULL;
}

void matrix_realloc(SETS *set){
        /* Realloc memory for arr_word_size */
        set->arr_word_size = (int *) realloc(set->arr_word_size,set->rowsize * sizeof(int));

        if(set->arr_word_size == NULL){
            printf("Realloc arr_word_size failed !\n");
            freemem(set);
            exit(0);
        }

        set->matrix = (char **) realloc(set->matrix,set->rowsize * sizeof(char *));

        if(set->matrix == NULL){
            printf("Realloc set->matrix failed !\n");
            freemem(set);
            exit(0);
        }

        for (int i = 0; i < set->rowsize; ++i) {
            *(set->matrix +i) = (char*) realloc(*(set->matrix + i),set->arr_word_size[i] *sizeof(char));
            if(*(set->matrix + i) == NULL){
                printf("Matrix char realloc\n");
                freemem(set);
                exit(0);
            }
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
    /* Realloc memory for encode matrix*/
    set->matrix_encode = (int **) realloc(set->matrix_encode, set->rowsize * sizeof(int *)); //allocate for n_words

    if (set->matrix_encode == NULL) {
        printf("ERROR encode realloc\n");
        exit(0);
    }
        //allocate for words_size
        for (int i = 0; i < set->rowsize; ++i) {
            *(set->matrix_encode + i) = (int *) realloc(*(set->matrix_encode + i), *(set->arr_word_size + i) * BITS *
                    sizeof(int));
            if (*(set->matrix_encode + i) == NULL) {
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
            *(*(set->matrix_encode + i) + j) = -1;
        } else {
            *(*(set->matrix_encode + i) + j) = (letter >> l) & 1;
        }
    }
}*/

int fperror(char *message) {
    fprintf(stderr, "ERROR: %s", message);
    exit(0);
}

void remove_word_matrix(SETS *set, int row){

}


void insertionSort(char** arr, int low, int high, int d) {
    for (int i = low + 1; i <= high; i++) {
        for (int j = i; j > low && strcmp(arr[j], arr[j - 1]) < 0; j--) {
            char* temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
        }
    }
}

void msdRadixSort_r(SETS *set, char **aux, int lo, int hi, int d, bool flag) {
    if (hi <= lo) return;

    int count[RADIX + 2] = {0};
    int *arr_sizes = calloc(sizeof(int) , set->rowsize);

    for (int i = lo; i <= hi; i++) {
        //printf(" i : %d = %s\n",i, *(set->matrix + i));
        char currentChar = *(*(set->matrix + i) + d);
        if (currentChar == ' '){
            currentChar = '0';
        }
        int charIndex = (int)currentChar;

        if (charIndex >= '0' && charIndex <= '9') {
           // printf(" i : %d = %s\n",i, *(set->matrix + i));
            count[charIndex - '0' + 2]++;
        } else if (charIndex >= 'a' && charIndex <= 'z') {
            count[charIndex - 'a' + 10 + 2]++;
        } else if (charIndex >= 'A' && charIndex <= 'Z') {
            count[charIndex - 'A' + 36 + 2]++;
        }
    }

    for (int r = 0; r < RADIX + 1; ++r) {
        count[r + 1] += count[r];
    }


    /* Insert words into aux array in right order */
    for (int i = lo; i <= hi; ++i) {
        char currentChar = *(*(set->matrix + i) + d);
        if (currentChar == ' ') {
            currentChar = '0';
        }

        int charIndex = (int) currentChar;
        if (charIndex >= '0' && charIndex <= '9') {
            aux[count[(charIndex - '0') + 1]++] = *(set->matrix + i);
            arr_sizes[count[(charIndex - '0') + 1]] = set->arr_word_size[i];
        } else if (charIndex >= 'a' && charIndex <= 'z') {
            aux[count[(charIndex - 'a' + 10) + 1]++] = *(set->matrix + i);
            arr_sizes[count[(charIndex - 'a' + 10) + 1]] = set->arr_word_size[i];
        } else if (charIndex >= 'A' && charIndex <= 'Z') {
            aux[count[(charIndex - 'A' + 36) + 1]++] = *(set->matrix + i);
            arr_sizes[count[(charIndex - 'A' + 36) + 1]] = set->arr_word_size[i];
        }
    }

    /* Copy values */
    for (int i = lo; i <= hi; ++i) {
        *(set->matrix + i) = aux[i - lo];
        set->arr_word_size[i] = arr_sizes[i-lo];
    }

    free(arr_sizes);

    for (int r = 0; r < RADIX; ++r) {
        int low = lo + count[r];
        int high = lo + count[r + 1] - 1;

        if (high > low + 1) {
            msdRadixSort_r(set, aux, low, high, d + 1,flag);
        }
    }
}

int msdRadixSort(SETS *set, int lo, int hi, bool flag) {
    char **aux = (char **)malloc((hi - lo + 1) * sizeof(char *));
    if (aux == NULL) {
        fperror("AUX in msdRadixSort Memory Allocation\n");
        return -1;
    }

    if(flag == 1){
        msdRadixSort_r(set, aux, lo, hi - 1, 0,flag);
    }else{
        msdRadixSort_r(set, aux, lo, hi - 1, 0,flag);
        reverseArray(set->matrix, 0, set->rowsize -1);
    }

    //msdRadixSort_r(set, aux, lo, hi - 1, 0,flag);

    free(aux);
    /* After sorting change array word sizes with current sizes */
   //FillArray_Word_Size(set);
}

void FillArray_Word_Size(SETS *set) {
    for (int i = 0; i < set->rowsize; ++i) {
        set->arr_word_size[i] =(int) strlen(set->matrix[i]);
    }
}

void binary_dictionary( int bin_d[62][8], int N , int *sizes_bin) {
    int index = 0;

    // Convert '0' to '9' to binary
    for (char digit = '0'; digit <= '9'; digit++) {
        charToBinary(digit - '0', bin_d[index], sizes_bin);
        if(digit - '0' == 0 || digit - '0' == 1){
            sizes_bin[index] = 1;
        }else{
            sizes_bin[index] =(int) log2((digit- '0') ) + 1;
        }
        index++;
    }

    // Convert 'a' to 'z' to binary
    for (char letter = 'a'; letter <= 'z'; letter++) {
        sizes_bin[index] = log2((letter - 'a' + 10)) + 1;
        charToBinary(letter - 'a' + 10, bin_d[index],sizes_bin);
        index++;
    }

    // Convert 'A' to 'Z' to binary
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        sizes_bin[index] = log2((letter - 'A' + 36)) + 1;
        charToBinary(letter - 'A' + 36, bin_d[index],sizes_bin);
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

void print_binary_dictionary(int (*bin_d)[8], int *size_bin) {
    for (int i = 0; i < 62; i++) {
        if( i < 10){
            printf("Binary for %c: ",  ('0' + i) );
        }else if(i >= 10 && i <= 36){
            printf("Binary for %c: ", ('a' + i - 10));
        }else{
            printf("Binary for %c: ",  ('A' + i - 36));
        }
        //printf("Binary for %c: ", (i < 10) ? ('0' + i) : ('a' + i - 10));
        for (int j = 0; j < size_bin[i]; j++) {
            printf("%d", bin_d[i][j]);
        }
        printf("\n");
    }
}


void encode_word(char* word, int *encoded,int *word_bits_size,int k, int sizes_bin[],int bin_dict[RADIX][BITS + 1]) {
    int index = 0;
    int len =(int) strlen(word);

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
            word_bits_size[k] += sizes_bin[charIndex];

            // Copy the binary representation to the encoded array
            for (int j = 0; j < sizes_bin[charIndex]; j++) {
                encoded[index++] = bin_dict[charIndex][j];
            }
        }
    }
}


void encode_matrix_words(SETS *set, int *sizes_bin_dict, int (*bin_dict)[8]) {

    for (int i = 0; i < set->rowsize; ++i) {
        set->arr_bits_size[i] = 0;
        encode_word(set->matrix[i], set->matrix_encode[i],set->arr_bits_size,i, sizes_bin_dict, bin_dict);
    }
}

// Reverse array in O(N)
void reverseArray(char **arr, int start, int end) {
    while (start < end) {
        char *temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        ++start;
        --end;
    }
}

int *arr_bits_size(int *arr, int N) {
    arr = (int*) calloc(sizeof(int) , N);

    if(arr == NULL){
        fperror("arr_bits_size malloc");
    }
    return arr;
}

void print_array(int *arr, int N) {
    for (int i = 0; i < N; ++i) {
        printf("%d\n", arr[i]);
    }

}

int write_matrix_char_txt(char **mat, int r, int *cols, char *filename) {
    FILE *fp = fopen(filename, "w+");

    if (fp == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "Words set\n", NULL);
    for (int i = 0; i < r; i++){
        fwrite(mat[i], sizeof(char), cols[i], fp);  // Write each row
        fputc('\n', fp);
    }


    // Close the file
    fclose(fp);


    return 0;
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


void KMP (char pattern[M_KMP], int dfa[MAX_UFP6][M_KMP]) {
    int indexChar = 0;
    int pattern_size =(int) strlen(pattern);

    //DFA init
    for (int i = 0; i < MAX_UFP6; ++i) {
        //Until word size
        for (int j = 0; j < pattern_size; ++j) {

            dfa[i][j] = 0;
        }
    }

    indexChar = calculate_index_char(pattern[0]);

    dfa[indexChar][0] = 1;

    for (int X = 0, j = 1; j < pattern_size; ++j){
        for (int c = 0; c < MAX_UFP6 ; ++c) {
           indexChar = calculate_index_char(pattern[j]); //ABBAAV - padrão que queremos procurar
           dfa[c][j] = dfa[c][X];
        }
        dfa[indexChar][j] = j + 1;
        X = dfa[indexChar][X];
    }
   // print_kmp(dfa);
}

int calculate_index_char(char currentChar) {
    int charIndex = 0;

    if ((currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= '0' && currentChar <= '9') ||
        (currentChar >= 'a' && currentChar <= 'z')) {

        if (currentChar >= 'A' && currentChar <= 'Z') {
            charIndex = (currentChar - 'A' + 36);
        } else if (currentChar >= '0' && currentChar <= '9') {
            charIndex = (currentChar - '0');
        } else {
            charIndex = (currentChar - 'a' + 10);
        }
    }
    return charIndex;
}


int *search_KMP(SETS *set, int dfa[MAX_UFP6][M_KMP], int word_size){
    int i , j;
    int indexChar = 0;
    int *arr_index = calloc(set->rowsize,sizeof(int));
    arr_index[0] = -1;

    int l = 1;

    for (int k = 0; k < set->rowsize; ++k) {
        for (i = 0, j = 0; i < strlen(*(set->matrix + k)) && j < word_size ; ++i) {
            indexChar = calculate_index_char(*(*(set->matrix + k ) + i));
            j = dfa[indexChar][j];
        }

        if (j == 3){
            arr_index[l++] = k;
        }
    }

    arr_index[0] = l; //store in pos 0 of array the count of words found with pattern

    if(arr_index[0] != -1)
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

void print_KMP_BinMatches(SETS *set, int *array_index) {
    printf("Words Found and their UFP6!!!\n");
    for (int k = 1; k < *array_index + 0; ++k) {
        printf("%s -> ", *(set->matrix + (*(array_index + k))));
        for (int i = 0; i < *(set->arr_bits_size + (*(array_index + k))); i++) {
           // printf("%d", *(*(set->matrix_encode + (*(array_index + k))))+ i);
            printf("%d", set->matrix_encode[array_index[k]][i]);
        }
        putchar('\n');
    }
}

//
//
int *find_Word(SETS *set, int word_size, int *array_found_words_index) {
    // Search for words with the exact size of the pattern
    int *array_index = (int*) malloc(sizeof(int) * *(array_found_words_index));

    int k = 1;
    for (int i = 1; i < *array_found_words_index; ++i) {
        //If it is equal it means we have a perfect word
        if(word_size == *(set->arr_word_size + *(array_found_words_index + i))){
            *(array_index + k++) = *(array_found_words_index + i);
        }
    }
    // Store size in index 0
    *(array_index) = k;

    return array_index;
}

void remove_Word(SETS *set, int *arr_words) {

    for (int i = *(arr_words + 1); i < set->rowsize - 1; ++i) {
        realloc_row_add(set, i);

        set->arr_word_size[i] = set->arr_word_size[i + 1];
        set->arr_bits_size[i] = set->arr_bits_size[i + 1];

        strcpy(set->matrix[i], set->matrix[i + 1]);
    }
    set->rowsize--;

    set->arr_bits_size =  realloc(set->arr_bits_size, sizeof(int) * set->rowsize);

    if(set->arr_bits_size == NULL){
        printf("ERROR REALLOC\n");
        exit(0);
    }
}


/*void realloc_row_delete(SETS *set,int row) {

    if(set->arr_word_size[row] > 0 && set->arr_word_size[row] == set->arr_word_size[row] / 4 ){
        set->matrix[row] = realloc(set->matrix[row], sizeof(char) / 2);
    }
}*/

void realloc_row_add(SETS *set, int row) {
    if(set->arr_word_size[row] < set->arr_word_size[row + 1] ){
        set->matrix[row] =  realloc(set->matrix[row], sizeof(char) * set->arr_word_size[row + 1]);


        if(set->matrix[row] == NULL){
            printf("ERROR REALLOC\n");
            exit(0);
        }
    }
}
