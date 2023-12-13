#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../functions/functions_2.h"
#include "../functions/functions_1.h"
#include "test_functions_2.h"
#include "test_functions_1.h"


#define R 5
#define DATE_SIZE 11
#define AD_SIZE 4
#define NUM_SETS 4
#define FILE "/Users/gabrielferreira/Desktop/projeto_aed1_lp1/data/set.txt"

int main_test_functions_2(int argc, char **argv) {
    int dict[MAX_UFP6][BITS] = {0};
    int sizes[MAX_UFP6];

    AD_WORDS_HOLDER *ad = NULL;
    //precompute bin_dict to encode words
    //test_function1_feature2(NULL, NULL, sizes, dict);

    test_function_2_a(&ad);

   // test_function_2_8_b(&ad, sizes,dict);
    //test_function_2_8_c(&ad, sizes,dict);

     test_function_2_10();

    free_dynamic_array(ad);

    return 0;
}
/*Perguntar como o professor pretende que implementamos encode na LL  */
void test_function_2_a(AD_WORDS_HOLDER **ad) {

    *ad = dynamic_array_init(AD_SIZE);

    /*we double the size when ad_SIZE == count before inserting into ad
     *
     * realloc_AD(ad, ad->size * 2)
     * /*/

   // free_dynamic_array(ad);
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

    save_both_sets_to_txt(&set1, &set2, FILE);

    SETS *set3 = calloc(1,sizeof(SETS));
    read_txt_to_set(set3, FILE);
    print_matrix_char(set3);
    print_matrix_int(set3);

    freemem(&set1);
    freemem(&set2);
    freemem(set3);
}

void test_function_2_8_b(AD_WORDS_HOLDER **ad_sorted,int *sizes_bin_dict, int bin_dict[RADIX][BITS]) {
    SETS set1  = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set1, R);
    SETS set2 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set2, R);
    SETS set3 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set3, R);
    SETS set4 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set4, R);

    matrix_rnd_char_gen(&set1);
    matrix_rnd_char_gen(&set2);
    matrix_rnd_char_gen(&set3);
    matrix_rnd_char_gen(&set4);

    //or
    /*SETS sets[NUM_SETS];

    for (int i = 0; i < NUM_SETS; ++i) {
        sets_struct_init(&sets[i], R);
    }*/

    char *testDates[] = {
            "2023-11-25",
            "2023-11-24",
            "2022-12-01",
            "2023-01-15",
            "2024-01-24",
    };

    insert_element_to_AD_in_order(*ad_sorted, set1, set2, testDates[0]);
    insert_element_to_AD_in_order(*ad_sorted, set1, set2, testDates[1]);
    insert_element_to_AD_in_order(*ad_sorted, set1, set2, testDates[2]);
    insert_element_to_AD_in_order(*ad_sorted, set1, set2, testDates[3]);
    insert_element_to_AD_in_order(*ad_sorted, set1, set2, testDates[4]);


    print_AD(*ad_sorted);

    freemem(&set1);
    freemem(&set2);
    freemem(&set3);
    freemem(&set4);

    free_dynamic_array(*ad_sorted);

    exit(0);
}

void test_function_2_8_c(AD_WORDS_HOLDER **ad, int *sizes_bin_dict, int (*bin_dict)[7]) {
    SETS set1  = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set1, R);
    SETS set2 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set2, R);
    SETS set3 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set3, R);
    SETS set4 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set4, R);

    matrix_rnd_char_gen(&set1);
    matrix_rnd_char_gen(&set2);
    matrix_rnd_char_gen(&set3);
    matrix_rnd_char_gen(&set4);

    encode_matrix_words(&set1, sizes_bin_dict,bin_dict);
    encode_matrix_words(&set2, sizes_bin_dict,bin_dict);
    encode_matrix_words(&set3, sizes_bin_dict,bin_dict);
    encode_matrix_words(&set4, sizes_bin_dict,bin_dict);


    //or
    /*SETS sets[NUM_SETS];

    for (int i = 0; i < NUM_SETS; ++i) {
        sets_struct_init(&sets[i], R);
    }*/

    char *testDates[] = {
            "2023-11-25",
            "2023-11-24",
            "2022-12-01",
            "2023-01-15",
            "2024-01-24",
    };

    insert_element_to_index_AD(*ad, &set1, &set2, testDates[0], 0);
    insert_element_to_index_AD(*ad, &set2, &set3, testDates[1],1);
    insert_element_to_index_AD(*ad, &set3, &set4, testDates[2],2);
    insert_element_to_index_AD(*ad, &set1, &set4, testDates[3],3);
    insert_element_to_index_AD(*ad, &set1, &set3, testDates[4],4);


    print_AD(*ad);

    freemem(&set1);
    freemem(&set2);
    freemem(&set3);
    freemem(&set4);

    free_dynamic_array(*ad);

    exit(0);
}
