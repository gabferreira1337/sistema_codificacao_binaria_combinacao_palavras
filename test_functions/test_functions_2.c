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
#define FILE "set.txt"

#define FILE_AD "ad_history.txt"
#define FILE_AD_BIN "ad_history.bin"
#define FILE_LL "LL_history.txt"
#define FILE_LL_BIN "LL_history.bin"

#define TIMER_START() gettimeofday(&tv1, NULL)
#define TIMER_STOP() \
gettimeofday(&tv2, NULL);    \
timersub(&tv2, &tv1, &tv);   \
time_delta = (float)tv.tv_sec + tv.tv_usec / 1000000.0

int main_test_functions_2(int argc, char **argv) {
    struct timeval tv1, tv2, tv;
    float time_delta = 0.0f;
    int dict[MAX_UFP6][BITS] = {0};
    int sizes[MAX_UFP6] = {0};

    //TIMER_START();
    //precompute bin_dict to encode words
    //test_function1_feature2(NULL, NULL, sizes, dict);

    //test_function_2_a();

    //test_function_2_8_b(&ad, sizes,dict);
    //test_function_2_8_c(&ad, sizes,dict);
    /*Test functions to input and output sets of words
     and their respective ufp6 representations  with AD// .txt file*/
    //test_function_2_10_ad();

    /*Test functions to input and output sets of words
    and their respective ufp6 representations with LL // .txt file*/
    //test_function_2_10_ll();
    /*Test functions to input and output sets of words
    and their respective ufp6 representations with AD //.bin file*/
    //test_functions_2_11_ad();
    /*Test functions to input and output sets of words
    and their respective ufp6 representations with LL //.bin file*/
     test_functions_2_11_ll();
    //TIMER_STOP();
    //fprintf(stdout, "%f secs\n", time_delta);

    exit(0);

    return 0;
}

void test_function_2_a() {
    AD_WORDS_HOLDER *ad = NULL;
    ad = dynamic_array_init(AD_SIZE);
    /*we double the size when ad_SIZE == count before inserting into ad
     *
     * realloc_AD(ad, ad->size * 2)
     * /*/
    free_dynamic_array(ad);
}


void test_function_2_8_b(int *sizes_ufp6_dict, int bin_dict[RADIX][BITS]) {
    AD_WORDS_HOLDER *ad_sorted = NULL;
    ad_sorted = dynamic_array_init(AD_SIZE);

    SETS set1  = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set1, sizes_ufp6_dict, R);
    SETS set2 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set2, sizes_ufp6_dict, R);
    SETS set3 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set3, sizes_ufp6_dict, R);
    SETS set4 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set4, sizes_ufp6_dict, R);


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

    insert_element_to_AD_in_order(ad_sorted, &set1, &set2, testDates[0]);
    insert_element_to_AD_in_order(ad_sorted, &set1, &set2, testDates[1]);
    insert_element_to_AD_in_order(ad_sorted, &set1, &set2, testDates[2]);
    insert_element_to_AD_in_order(ad_sorted, &set1, &set2, testDates[3]);
    insert_element_to_AD_in_order(ad_sorted, &set1, &set2, testDates[4]);

    print_AD(ad_sorted);

    freemem(&set1);
    freemem(&set2);
    freemem(&set3);
    freemem(&set4);

    free_dynamic_array(ad_sorted);

    exit(0);
}

void test_function_2_8_c(int *sizes_ufp6_dict, int (*bin_dict)[BITS]) {
    AD_WORDS_HOLDER *ad = NULL;
    ad = dynamic_array_init(AD_SIZE);
    SETS set1  = {NULL, NULL, NULL, NULL, 0, 0};
    //Initialize sets with random words
    sets_struct_init(&set1, sizes_ufp6_dict,R);
    SETS set2 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set2, sizes_ufp6_dict, R);
    SETS set3 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set3, sizes_ufp6_dict, R);
    SETS set4 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set4, sizes_ufp6_dict, R);

    encode_matrix_words(&set1, sizes_ufp6_dict, bin_dict);
    encode_matrix_words(&set2, sizes_ufp6_dict, bin_dict);
    encode_matrix_words(&set3, sizes_ufp6_dict, bin_dict);
    encode_matrix_words(&set4, sizes_ufp6_dict, bin_dict);

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

    insert_element_to_index_AD(ad, &set1, &set2, testDates[0], 0);
    insert_element_to_index_AD(ad, &set2, &set3, testDates[1],1);
    insert_element_to_index_AD(ad, &set3, &set4, testDates[2],2);
    insert_element_to_index_AD(ad, &set1, &set4, testDates[3],3);
    insert_element_to_index_AD(ad, &set1, &set3, testDates[4],4);


    print_AD(ad);

    freemem(&set1);
    freemem(&set2);
    freemem(&set3);
    freemem(&set4);

    free_dynamic_array(ad);

    exit(0);
}

/**
 * @paragraph Use txt files for input and output of sets of words and their
 * respective ufp6 representations
 * In this function we test all functions to write a Dynamic array AD_WORDS_HOLDER
 * to txt file and after read that file to aa new Dynamic array
 */
void test_function_2_10_ad() {
    AD_WORDS_HOLDER *arr_din = dynamic_array_init(AD_SIZE);
    int dict[MAX_UFP6][BITS];
    int sizes_ufp6_dict[MAX_UFP6];
    //Pre-compute ufp6 dictionary
    ufp6_dictionary(dict, sizes_ufp6_dict);

    SETS *set1 = (SETS *) calloc(1,sizeof(SETS));
    if(set1 == NULL) fperror("Calloc set1 in test_function_2_10_ad");
    sets_struct_init(set1, sizes_ufp6_dict, R);
    SETS *set2 = (SETS *) calloc(1,sizeof(SETS));
    if(set2 == NULL) fperror("Calloc set2 in test_function_2_10_ad");
    sets_struct_init(set2, sizes_ufp6_dict, R);
    SETS *set3 = (SETS *) calloc(1,sizeof(SETS));
    if(set3 == NULL) fperror("Calloc set3 in test_function_2_10_ad");
    sets_struct_init(&set3, sizes_ufp6_dict, R);
    SETS *set4 = (SETS *) calloc(1,sizeof(SETS));
    if(set4 == NULL) fperror("Calloc set4 in test_function_2_10_ad");
    sets_struct_init(&set4, sizes_ufp6_dict, R);

    matrix_rnd_word_gen(set1);
    matrix_rnd_word_gen(set2);
    matrix_rnd_word_gen(set3);
    matrix_rnd_word_gen(set4);

    encode_matrix_words(set1, sizes_ufp6_dict,dict);
    encode_matrix_words(set2, sizes_ufp6_dict,dict);
    encode_matrix_words(set3, sizes_ufp6_dict,dict);
    encode_matrix_words(set4, sizes_ufp6_dict,dict);

    char *testDates[] = {
            "2023-11-25",
            "2023-11-24",
            "2022-12-01",
            "2023-01-15",
            "2024-01-24",
    };

    insert_element_to_AD_in_order(arr_din, set1,set2, testDates[0]);
    insert_element_to_AD_in_order(arr_din, set3,set4, testDates[1]);

    //insert_element_to_index_AD(arr_din, &set1,&set2, testDates[0], 0);
   // insert_element_to_index_AD(arr_din, &set1,&set2, testDates[1], 1);

    write_ad_to_txt(arr_din,FILE_AD);

    AD_WORDS_HOLDER *arr_din2 = NULL;
    // Last argument is a flag , if set to 1 read in chronological order
    //Pass to function adress of pointer arr_din so changes stay outside function
    read_from_txt_to_ad(&arr_din2, FILE_AD, 1);

    print_AD(arr_din2);

    free_dynamic_array(arr_din);
    free_dynamic_array(arr_din2);

    exit(0);
}
/**
 * @paragraph Use txt files for input and output of sets of words and their
 * respective ufp6 representations
 * In this function we test all functions to write a linked list LL_WORDS_HOLDER
 * to txt file and after read that file to a new Linked List
 */
void test_function_2_10_ll() {
    LL_WORDS_HOLDER *ll = ll_init();

    int dict[MAX_UFP6][BITS];
    int sizes_ufp6_dict[MAX_UFP6];
    //Pre-compute ufp6 dictionary
    ufp6_dictionary(dict, sizes_ufp6_dict);
    SETS set1 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set1, sizes_ufp6_dict, R);
    SETS set2 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set2, sizes_ufp6_dict, R);

    //Generate random words
    matrix_rnd_word_gen(&set1);
    matrix_rnd_word_gen(&set2);
    //Encode to ufp6
    encode_matrix_words(&set1, sizes_ufp6_dict,dict);
    encode_matrix_words(&set2, sizes_ufp6_dict,dict);

    char *testDates[] = {
            "2023-11-25",
            "2023-11-24",
            "2022-12-01",
            "2023-01-15",
            "2024-01-24",
    };

    insert_node_ll_sorted(ll, &set1,&set2, testDates[0]);
    insert_node_ll_sorted(ll, &set1,&set2, testDates[1]);

    write_ll_to_txt(ll,FILE_LL);

    LL_WORDS_HOLDER *ll_2 = ll_init();
    // Last argument is a flag , if set to 1 read in chronological order
    //Pass to function adress of pointer arr_din so changes stay outside function
    read_from_txt_to_ll(ll_2,FILE_LL, 1);
    print_ll_words_holder(ll_2);

    free_ll_words_holder(ll);
    free_ll_words_holder(ll_2);

    exit(0);
}

void test_functions_2_11_ad() {
    AD_WORDS_HOLDER *arr_din = NULL;
    arr_din = dynamic_array_init(AD_SIZE);
    int dict[MAX_UFP6][BITS];
    int sizes_ufp6_dict[MAX_UFP6];
    //Pre-compute ufp6 dictionary
    ufp6_dictionary(dict, sizes_ufp6_dict);

    SETS *set1 = (SETS *) calloc(1,sizeof(SETS));
    if(set1 == NULL) fperror("Calloc set1 in test_function_2_10_ad");
    sets_struct_init(&set1, sizes_ufp6_dict, R);
    SETS *set2 = (SETS *) calloc(1,sizeof(SETS));
    if(set2 == NULL) fperror("Calloc set2 in test_function_2_10_ad");
    sets_struct_init(&set2, sizes_ufp6_dict, R);
    SETS *set3 = (SETS *) calloc(1,sizeof(SETS));
    if(set3 == NULL) fperror("Calloc set3 in test_function_2_10_ad");
    sets_struct_init(&set3, sizes_ufp6_dict, R);
    SETS *set4 = (SETS *) calloc(1,sizeof(SETS));
    if(set4 == NULL) fperror("Calloc set4 in test_function_2_10_ad");
    sets_struct_init(&set4, sizes_ufp6_dict, R);


    encode_matrix_words(set1, sizes_ufp6_dict,dict);
    encode_matrix_words(set2, sizes_ufp6_dict,dict);
    encode_matrix_words(set3, sizes_ufp6_dict,dict);
    encode_matrix_words(set4, sizes_ufp6_dict,dict);

    char *testDates[] = {
            "2023-11-25",
            "2023-11-24",
            "2022-12-01",
            "2023-01-15",
            "2024-01-24",
    };

    insert_element_to_AD_in_order(arr_din, set1,set2, testDates[0]);
    insert_element_to_AD_in_order(arr_din, set3,set4, testDates[1]);

    //insert_element_to_index_AD(arr_din, &set1,&set2, testDates[0], 0);
    // insert_element_to_index_AD(arr_din, &set1,&set2, testDates[1], 1);

    write_ad_to_bin(arr_din,FILE_AD_BIN);

    AD_WORDS_HOLDER *arr_din2 = NULL;
    // Last argument is a flag , if set to 1 read in chronological order
    //Pass to function adress of pointer arr_din so changes stay outside function
    read_from_bin_to_ad(&arr_din2, FILE_AD_BIN, 1);

    print_AD(arr_din2);

    free_dynamic_array(arr_din);
    free_dynamic_array(arr_din2);

    exit(0);
}

void test_functions_2_11_ll() {
    LL_WORDS_HOLDER *ll = ll_init();

    int dict[MAX_UFP6][BITS];
    int sizes_ufp6_dict[MAX_UFP6];
    //Pre-compute ufp6 dictionary
    ufp6_dictionary(dict, sizes_ufp6_dict);
    SETS set1 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set1, sizes_ufp6_dict, R);
    SETS set2 = {NULL, NULL, NULL, NULL, 0, 0};
    sets_struct_init(&set2, sizes_ufp6_dict, R);

    //Encode to ufp6
    encode_matrix_words(&set1, sizes_ufp6_dict,dict);
    encode_matrix_words(&set2, sizes_ufp6_dict,dict);

    char *testDates[] = {
            "2023-11-25",
            "2023-11-24",
            "2022-12-01",
            "2023-01-15",
            "2024-01-24",
    };

    insert_node_ll_sorted(ll, &set1,&set2, testDates[0]);
    insert_node_ll_sorted(ll, &set1,&set2, testDates[1]);

    write_ll_to_binfile(ll,FILE_LL_BIN);

    LL_WORDS_HOLDER *ll_2 = ll_init();
    // Last argument is a flag , if set to 1 read in chronological order
    //Pass to function adress of pointer arr_din so changes stay outside function
    read_from_binfile_to_ll(ll_2,FILE_LL_BIN, 1);
    print_ll_words_holder(ll_2);

    free_ll_words_holder(ll);
   // free_ll_words_holder(ll_2);
    exit(0);
}
