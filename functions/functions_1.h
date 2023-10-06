#ifndef PROJETO_AED1_LP1_FUNCTIONS_1_H
#define PROJETO_AED1_LP1_FUNCTIONS_1_H

/**
 * set 1 struct
 */
typedef struct{

    char **matrix1;
    int  **matrixc1;
    short size1;
    short sizec1;

}SET1;

/**
 * set 2 struct
 */
typedef struct{

    char **matrix2;
    int **matrixc2;
    short size2;
    short sizec2;

}SET2;

/**  encode a matrix of strings to UFP6 (binary)
 * @params
 *
 */
void encode(SET1 *set1);
/**  initialize matrix of ints to 0
 * @params
 *
 */

char gen_rnd_char(int length);

int **matrix_init_int(int row ,int col);
/**  initialize matrix of char to 0
 * @params
 *
 */
char **matrix_init_char(int row ,int col);
/**  print matrix
 * @params
 *
 */


void print_matrix_int(SET1 *set1, SET2 *set2);
/**  print matrix
 * @params
 *
 */
void print_matrix_char(SET1 *set1, SET2 *set2);
/**  free memory allocated
 * @params
 *
 */
void freemem(SET1 *set1, SET2 *set2);

int main_functions_1(int argc , char **argv);

#endif //PROJETO_AED1_LP1_FUNCTIONS_1_H
