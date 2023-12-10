#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../functions/functions_2.h"
#include "../functions/functions_1.h"
#include "test_functions_2.h"


#define R 5
#define DATE_SIZE 11
#define AD_SIZE 4
#define FILE "sets.txt"

int main_test_functions_2(int argc, char **argv) {
    test_function_2_10();

    return 0;
}
/*Perguntar como o professor pretende que implementamos encode na LL  */
void test_function_2_a() {
    AD_WORDS_HOLDER *ad;

    ad = dynamic_array_init(AD_SIZE);

    /*we double the size when ad_SIZE == count before inserting into ad
     *
     * realloc_AD(ad, ad->size * 2)
     * /*/

    free_dynamic_array(ad);
}

/**
 * Test function to test feature 10
 * @paragraph Use files for input and output of sets of words
 * and their respective UFP6 representation
 */
void test_function_2_10() {
    AD_WORDS_HOLDER *arr_din;
    arr_din = dynamic_array_init(AD_SIZE);
    int dic[MAX_UFP6][BITS];
    int sizes[MAX_UFP6];

    binary_dictionary(dic, sizes);
    SETS set1 ;
    sets_struct_init(&set1, R);
    SETS set2 ;
    sets_struct_init(&set2, R);

    matrix_rnd_char_gen(&set1);
    matrix_rnd_char_gen(&set2);

    encode_matrix_words(&set1, sizes,dic);
    encode_matrix_words(&set2, sizes,dic);

   //save_set_txt(&set1, "set.txt");

    save_both_sets_to_txt(&set1, &set2, "set.txt");

    SETS *set3 = calloc(1,sizeof(SETS));
    read_txt_to_set(set3, FILE);

    print_matrix_int(set3);

    freemem(&set1);
    freemem(&set2);
    freemem(set3);
}
