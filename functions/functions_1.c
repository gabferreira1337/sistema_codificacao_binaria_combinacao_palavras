#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <ctype.h>
#include "functions_1.h"



#define R 2
#define C 5
#define WORD_LENGTH 5
#define BITS 7
#define RADIX 37
#define TIMER_START() gettimeofday(&tv1, NULL)
#define TIMER_STOP() \
gettimeofday(&tv2, NULL);    \
timersub(&tv2, &tv1, &tv);   \
time_delta = (float)tv.tv_sec + tv.tv_usec / 1000000.0



int main_functions_1(int argc , char **argv){
    struct timeval tv1, tv2, tv;
    float time_delta;
    /* seed to generate random numbers */
    srand(time(NULL));
    /*
     * Initialize set1  *
                        */
    SETS set1;
    set1.matrix_encode = matrix_init_int(R,C);
    set1.matrix = matrix_init_char(R,C);
    set1.colsize_char = C;
    set1.colsize_encode =C * BITS;
    set1.rowsize = R;
    init_arr_word_size(&set1);
    /*
    * Initialize set2  *
                       */
    SETS set2;
    set2.matrix_encode = matrix_init_int(R,C);
    set2.matrix = matrix_init_char(R,C);
    set2.colsize_char = C;
    set2.colsize_encode =C * BITS;
    set2.rowsize = R;
    init_arr_word_size(&set2);

    /* Generate words for both sets  */
    matrix_rnd_char_gen(&set1, WORD_LENGTH);
    matrix_rnd_char_gen(&set2, WORD_LENGTH);

    TIMER_START();

    /* Encode both sets  */
    encode(&set1);
    encode(&set2);

    /* Insert word */
    insert_word_char(&set1, set1.rowsize, 2);
    encode(&set1);

    /* Print both sets  */
    puts("SET 1");
    print_matrix_char(set1);
    puts("SET 1 ENCODE");
    print_matrix_int(set1);
    puts("SET 2");
    print_matrix_char(set2);
    puts("SET 2 ENCODE");
    print_matrix_int(set2);

    /* Sort Both arrays */
    msdRadixSort(&set1, 0, set1.rowsize );
    puts("SET 1 . SORTED");
    print_matrix_char(set1);
    encode(&set1);
    print_matrix_int(set1);
    msdRadixSort(&set2, 0, set2.rowsize );
    puts("SET 2 . SORTED");
    print_matrix_char(set2);
    encode(&set2);
    print_matrix_int(set2);


   /* Print array word size */
   // print_arr_word_size(set1);

    /* free memory  */
    freemem(&set1);
    freemem(&set2);

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

char **matrix_init_char(int row ,int col){
    // Allocate memory for array of pointers
    char** mat = (char**)calloc(row, sizeof(char*));

    if (mat == NULL) {
        printf("Matrix int row malloc\n");
        exit(0);
    }

    for (int i = 0; i < row; ++i) {
        // Allocate memory for each pointer (cols)
        *(mat +i) = (char*)calloc(col, sizeof(char));
        if (mat[i] == NULL) {
            printf("Matrix int col malloc\n");
            exit(0);
        }
    }
    return mat;
}

void print_matrix_int(SETS set) {
    for (int i = 0; i < set.rowsize; ++i){
        for (int j = 0; j < *(set.arr_word_size + i) * 7; ++j) {
            if (*(*(set.matrix_encode + i) +j) == -1) continue;
            printf(" %d",*(*(set.matrix_encode + i) +j));
        }
        putchar('\n');
    }
}

void print_matrix_char(SETS set) {
    for (int i = 0; i < set.rowsize; ++i) {
        for (int j = 0; j < *(set.arr_word_size + i); ++j) {
            printf(" %c",*(*(set.matrix + i) +j));
        }
        putchar('\n');
    }
}

void encode(SETS *set){
    int charCalc = 0;
    int  j=0;
    for (int i = 0; i < set->rowsize; ++i) {
        //printf("%s\n", set->matrix[i]);
        // printf("--%s",set->matrix[i]);
        j =0;
        int count = 0;
        for (int k = 0;k < *(set->arr_word_size + i); k++) {
          //  printf("j : %d\n", j);
          //  printf("k - %d\n");
            charCalc = (unsigned char) *(*(set->matrix + i) + k) ;
            //printf("char - %c\n", charCalc);
            // printf("--%s",set->matrix[i]);
            //printf(" \n%d\n", count++);
            if (charCalc >= '0' && charCalc <= '9') {
                int digit = charCalc - '0';
                for (int l = BITS - 1; l >= 0 && j < (set->arr_word_size[i]) * BITS ; l--, j++) {
                    *(*(set->matrix_encode + i) +j) = (digit >> l) & 1;
                }
            } else if (charCalc >= 'a' && charCalc <= 'z') {
                 //printf("char %c\n", charCalc);
                //printf(" %d", count);
                /* 10 represents the beginning of letters */
                int letter = charCalc - 'a' + 10;
                //printf(" %d", letter);
                for (int l = BITS -1; l >= 0 && j < (set->arr_word_size[i]) * BITS;l--, j++) {
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
                for (int l = BITS -1; l >= 0 && j < (set->arr_word_size[i]) * BITS; l--, j++) {
                    if((letter >>l) == 0) break;
                    *(*(set->matrix_encode + i) +j) = (letter >> l) & 1;
                }
            }
        }
    }
}


char gen_rnd_char(int length){
    int random_number;
    /* Generate random number between 'a' and 'z' */
    random_number = 'a' + rand() % 26;
    return (char) random_number;
}

char **matrix_rnd_char_gen(SETS *set,int word_length) {
    for (int i = 0; i < set->rowsize; ++i) {
        /* store word_length in an array */
        set->arr_word_size[i] = word_length;
        for (int j = 0; j < set->colsize_char; ++j) {
            *(*(set->matrix + i) +j) = gen_rnd_char(word_length);
        }
    }
    return NULL;
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


void print_arr_word_size(SETS set){
    for (int i = 0; i < set.rowsize; ++i) {
        printf("pos: %d - size: %d\n", i, set.arr_word_size[i]);
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

void msdRadixSort_r(SETS *set, char **aux, int lo, int hi, int d) {
    if (hi <= lo)return;

    int count[RADIX + 2] = {0};

    for (int i = lo; i <= hi; i++) {
        //printf(" i : %d = %s\n",i, *(set->matrix + i));
        char currentChar = *(*(set->matrix + i) + d);
        if(currentChar == ' '){
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

        if(currentChar == ' '){
            currentChar = '0';
        }

        int charIndex = (int)currentChar;

        if (charIndex >= '0' && charIndex <= '9') {
            aux[count[(charIndex - '0') + 1]++] = *(set->matrix + i);
        } else if (charIndex >= 'a' && charIndex <= 'z') {
            aux[count[(charIndex - 'a' + 10) + 1]++] = *(set->matrix + i);
        } else if (charIndex >= 'A' && charIndex <= 'Z') {
            aux[count[(charIndex - 'A' + 36) + 1]++] = *(set->matrix + i);
        }
    }
    /* Copy values */
    for (int i = lo; i <= hi; ++i) {
        *(set->matrix + i) = aux[i - lo];
    }

    for (int r = 0; r < RADIX; ++r) {
        int low = lo + count[r];
        int high = lo + count[r + 1] - 1;

        if (high > low + 1) {
            msdRadixSort_r(set, aux, low, high, d + 1);
        }
    }
}

int msdRadixSort(SETS *set, int lo, int hi) {
    char **aux = (char **)malloc((hi - lo + 1) * sizeof(char *));
    if (aux == NULL) {
        fperror("AUX in msdRadixSort Memory allocation\n");
        return -1;
    }

    msdRadixSort_r(set, aux, lo, hi - 1, 0);
    free(aux);
    /* After sorting change array word sizes with current sizes */
    FillArray_Word_Size(set);
}

void FillArray_Word_Size(SETS *set) {
    for (int i = 0; i < set->rowsize; ++i) {
        set->arr_word_size[i] =(int) strlen(set->matrix[i]);
    }
}
