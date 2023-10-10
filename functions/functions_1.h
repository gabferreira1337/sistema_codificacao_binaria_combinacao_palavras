#ifndef PROJETO_AED1_LP1_FUNCTIONS_1_H
#define PROJETO_AED1_LP1_FUNCTIONS_1_H

/**
 * set 1 struct
 */
typedef struct{

    char **matrix;
    int  **matrix_encode;
    short size;
    short size_encode;

}SETS;



/**  encode a matrix of strings to UFP6 (binary)
 * @params
 *
 */
void encode(SETS *set);
/**  initialize matrix of ints to 0
 * @params
 *
 */

char gen_rnd_char(int length);

short **matrix_init_short(int row ,int col);
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
/**  print matrix
 * @params
 *
 */
void print_matrix_char(SETS *set);
/**  free memory allocated
 * @params
 *
 */
void freemem(SETS *set);

int main_functions_1(int argc , char **argv);

#endif //PROJETO_AED1_LP1_FUNCTIONS_1_H
