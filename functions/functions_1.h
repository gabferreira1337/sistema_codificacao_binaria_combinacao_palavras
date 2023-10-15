#ifndef PROJETO_AED1_LP1_FUNCTIONS_1_H
#define PROJETO_AED1_LP1_FUNCTIONS_1_H

/**
 * sets struct
 */
typedef struct{

    char **matrix;
    unsigned int **matrix_encode;
    int rowsize;
    int colsize_char;
    int colsize_encode;


}SETS;



/**  encode a matrix of strings to UFP6 (binary)
 * @params
 *
 */
void encode(SETS *set);

unsigned int int_to_bin(unsigned int k);


/** generate random char
 * @params length - word length
 * @return  word generated
 */
char gen_rnd_char(int length);

/** Initialize matrix with random words generated
 * @params length - word length
 * @return  word generated
 */
char **matrix_rnd_char_gen(SETS *set,int word_length);

/**  initialize matrix of ints to 0
 * @params
 *
 */
unsigned int **matrix_init_int(int row ,int col);

/**  initialize matrix of char to 0
 * @params
 *
 */
char **matrix_init_char(int row ,int col);

/**  print matrix
 * @params
 *
 */
void print_matrix_int(SETS *set);

/**  insert word into matrix char
 * @params
 *
 */
void insert_word_char(SETS *set,int start_row,  int number_words);
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

/** print matrix
 * @params
 *
 */
void print_matrix_char(SETS *set);

/** free memory allocated
 * @params
 *
 */
void freemem(SETS *set);

int main_functions_1(int argc , char **argv);

#endif //PROJETO_AED1_LP1_FUNCTIONS_1_H
