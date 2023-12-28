#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "test_functions_1.h"
#include "../functions/functions_1.h"

#define R 8
#define  FILE_PATTERN_FOUND_SET ../data/set_words_found.txt"
#define MSD_VS_MERGES_FILE "../data/sorting_comp.txt"

#define TIMER_START() gettimeofday(&tv1, NULL)
#define TIMER_STOP() \
gettimeofday(&tv2, NULL);    \
timersub(&tv2, &tv1, &tv);   \
time_delta = (float)tv.tv_sec + tv.tv_usec / 1000000.0

struct timeval tv1, tv2, tv;
float time_delta;

int main_test_functions_1(int argc, char **argv) {
   // TIMER_START();
    /**1) Test functions to initialize set with random words
     * and with exact number of columns in each matrix to hold words
     * and their UFP6 representation
     */
    //test_function1_feature1();
    /**2) Test functions to encode to UFP6 a matrix of words
    */
   //test_function1_feature2();
    /**3) Test functions to insert and remove words and their respective representation from set
     * shifting rows
    */
   //test_function1_feature3();
    /**4) Test functions to find equal combinations of UFP6 representations from 2 sets
     */
    test_function1_feature4();
   /**5) Test functions to search for a pattern in a set of words and their respective UFP6
    * representation and output into console and txt file
    */
     //test_functions1_feature5();
    /**6) Test functions to sort set (both matrix) by alphabetical order (ASC and DESC) and by words size
     * (ASC and DESC) also
    */
     //test_functions1_feature6();
     //test_cmp_msd_mergesort();
     //TIMER_STOP();
   // fprintf(stdout, "time_delta %f\n", time_delta);

   // exit(0);
    return 0;
}

void test_function1_feature1(){
    int dict[MAX_UFP6][BITS - 1]={
            {0, 0},
            {0, 0}
    };
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-compute UFP6 dictionary and an array storing the sizes of
    ///each representation of each UFP6 char
    ufp6_dictionary(dict, sizes_ufp6_dict);

    SETS set1 = {NULL, NULL, NULL, NULL, 0};
    int  num_words_set1 = 5;

    ///Initialize sets with random words
    sets_struct_init(&set1, sizes_ufp6_dict,num_words_set1);

    /// Print set1
    printf("SET 1 !!!!\n");
    print_matrix_char(&set1);
    print_matrix_int(&set1);
}

void test_function1_feature2() {
    ///Matrix (Dictionary) to hold all char representations of UFP6 encoding
    int dict[MAX_UFP6][BITS - 1]={
            {0, 0},
            {0, 0}
    };
    ///Array holding the sizes of each UFP6 representation of each char
    ///suported by UFP6
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-compute dictionary of binary representations and their respective size
    ufp6_dictionary(dict, sizes_ufp6_dict);

    //print_ufp6_dictionary(dict, sizes_ufp6_dict);

    char word[] = "1";
    int W = 1;
    ///result of ufp6 representation
    int result[strlen(word) * BITS - 1];
    /// array with ufp6 size of a word for only test purpose
    int size[W];
    encode_word(word, result,size, 0, sizes_ufp6_dict, dict,(int) strlen(word));
    ///Print UFP6 representation
    for (int i = 0; i < size[0]; ++i) {
        printf("%d", result[i]);
    }

    SETS set1 = {NULL, NULL, NULL, NULL, 0};
    int  num_words_set1 = 5;

    /// Initialize sets with random words
    sets_struct_init(&set1, sizes_ufp6_dict,num_words_set1);

    /// Encode SET1
    encode_matrix_words(&set1, sizes_ufp6_dict, dict);

    printf("\nSET 1 !!!!\n");
    print_matrix_char(&set1);
    print_matrix_int(&set1);
}

void test_function1_feature3() {
    ///Matrix (Dictionary) to hold all char representations of UFP6 encoding
    int ufp6_dict[MAX_UFP6][BITS - 1]={
            {0, 0},
            {0, 0}
    };
    /// Sizes of each UFP6 representation of each char
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ufp6_dictionary(ufp6_dict,sizes_ufp6_dict);
    SETS set1 = {NULL, NULL, NULL, NULL, 0};

    int  num_words_set1 = 5;

    ///Initialize sets with random words
    sets_struct_init(&set1, sizes_ufp6_dict,num_words_set1);
    encode_matrix_words(&set1,sizes_ufp6_dict,ufp6_dict);
    //print_matrix_int(set1);

    const char *insert_words1[] = {"ol4", "ola","L", "-"};

    int N1 = sizeof(insert_words1) / sizeof(insert_words1[0]);
    ///Insert words and UFP6 in set
    insert_words(&set1,insert_words1,sizes_ufp6_dict,ufp6_dict, N1);
    printf("SET 1 !!!!\n");
    print_matrix_char(&set1);
    print_matrix_int(&set1);

    ///Remove words and UFP6 from set
    const char *remove_words1[] = {"ol4"};
    int N2 = sizeof(remove_words1) / sizeof(remove_words1[0]);

    remove_Words(&set1, remove_words1, N2);

    printf("SET 1 !!!!\n");
    print_matrix_char(&set1);
    print_matrix_int(&set1);
}

void test_functions1_feature5(){
    int ufp6_dict[MAX_UFP6][BITS - 1]={
            {0, 0},
            {0, 0}
    };
    /// Sizes of each UFP6 representation from each char
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-Compute UFP6 dictionary
    ufp6_dictionary(ufp6_dict, sizes_ufp6_dict);
    SETS set1 = {NULL, NULL, NULL, NULL, 0};
    int  num_words_set1 = 5;
    ///Initialize sets with random words
    sets_struct_init(&set1, sizes_ufp6_dict,num_words_set1);
    ///Encode words
    encode_matrix_words(&set1, sizes_ufp6_dict, ufp6_dict);

    const  char *words_insert[] = {"ola", "olas"};
    int num_words = sizeof(words_insert)/sizeof(words_insert[0]);
    ///Insert words in set
    insert_words(&set1, words_insert, sizes_ufp6_dict, ufp6_dict, num_words);
    const  char *pattern_search[] = {"-", "ol"};
    int num_pattern_search = sizeof(pattern_search)/sizeof(pattern_search[0]);
    ///Search for words and their respective ufp6 representation with a given pattern without writing to a txt file
    find_words_with_pattern(&set1, pattern_search, num_pattern_search, NULL, 0);
    ///Search for words and their respective ufp6 representation with a given pattern and writing to a txt file
    //find_words_with_pattern(&set1, pattern_search, num_pattern_search, FILE_PATTERN_FOUND_SET, 1);
    print_matrix_char(&set1);
    print_matrix_int(&set1);
    freemem_set(&set1);
}

void test_functions1_feature6() {
    int ufp6_dict[MAX_UFP6][BITS - 1]={
            {0, 0},
            {0, 0}
    };
    /// Sizes of each ufp6 representation
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    /// Pre-Compute UFP6 dictionary
    ufp6_dictionary(ufp6_dict, sizes_ufp6_dict);
    SETS set1 = {NULL, NULL, NULL, NULL, 0};
    int  num_words_set1 = R;
    ///Initialize sets with random words
    sets_struct_init(&set1, sizes_ufp6_dict, num_words_set1);
    encode_matrix_words(&set1, sizes_ufp6_dict, ufp6_dict);
    printf("Before sort\n");
    print_matrix_char(&set1);
    print_matrix_int(&set1);

    int flag = 1; // ASC
    /** @paragraph Sort by alphabetical order (ASC and DESC)
     *  if flag set to 1 = ASC ,if set to 0 = DESC
     *  */
    printf("\nSort by alphabetical order\n");
    sort_by_alphabetical_order(&set1, sizes_ufp6_dict,flag);
    is_sorted_matrix(&set1, set1.rowsize,flag);
    // msdRadixSort(&set1, sizes_ufp6_dict, 0, set1.rowsize, flag);
    print_matrix_char(&set1);
    print_matrix_int(&set1);
    /* TIMER_START();
    insertion_sort_char(&set2, set2.rowsize, 1);
    TIMER_STOP();
    fprintf(stdout, "Time_delta Insertion sort %f\n", time_delta);*/
    /** * @paragraph Sort by words_size in (ASC and DESC)
     *  if flag set to 1 = ASC, if set to 0 = DESC
     *  */
    printf("\nSort by words size\n");
    sort_size(&set1, flag);

    print_matrix_char(&set1);
    print_matrix_int(&set1);
    //print_arr_word_size(&set1);
    is_sorted_sizes(&set1, set1.rowsize, flag);
    freemem_set(&set1);
    exit(0);
}

void test_function1_feature4() {
    int ufp6_dict[MAX_UFP6][BITS - 1]={
            {0, 0},
            {0, 0}
    };
    /// sizes of each binary representation
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ufp6_dictionary(ufp6_dict,sizes_ufp6_dict);
    SETS set1 = {NULL, NULL, NULL, NULL, 0};
    SETS set2 = {NULL, NULL, NULL, NULL, 0};
    int  num_words_set1 = 1;
    int  num_words_set2 = 1;

    ///Initialize sets with random words
    sets_struct_init(&set1, sizes_ufp6_dict,num_words_set1);
    sets_struct_init(&set2, sizes_ufp6_dict, num_words_set2);

    encode_matrix_words(&set1, sizes_ufp6_dict,ufp6_dict);
    encode_matrix_words(&set2, sizes_ufp6_dict,ufp6_dict);

    remove_word_from_set(&set1, 0);
    remove_word_from_set(&set2, 0);

    const char *words1[] = {
        "10",
        "10",
    };
    const char *words2[] = {
            "0",
            "5",
    };
    int num_words = sizeof(words1) / sizeof(words1[0]);

    insert_words(&set1, words1, sizes_ufp6_dict, ufp6_dict, num_words);
    insert_words(&set2, words2, sizes_ufp6_dict, ufp6_dict, num_words);

    //print_matrix_int(&set1);
   // print_matrix_int(&set2);

    combination_ufp6_in_both_sets(&set1, &set2);
    freemem_set(&set1);
    freemem_set(&set2);
}

void test_cmp_msd_mergesort() {
    int ufp6_dict[MAX_UFP6][BITS - 1]={
            {0, 0},
            {0, 0}
    };
    /// Sizes of each ufp6 representation
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    /// Pre-Compute UFP6 dictionary
    ufp6_dictionary(ufp6_dict, sizes_ufp6_dict);

    int flag = 1; ///Sort in ASC order
    float time_delta_msd = 0.0f;
    float time_delta_merge_s = 0.0f;
    int arr_num_words[] = {1000, 1000000, 4000000,10000000};
    for (int i = 0; i < 4; ++i) {
        SETS set1 = {NULL, NULL, NULL, NULL, 0};
        SETS set2 = {NULL, NULL, NULL, NULL, 0};
        int num_words_set2 = arr_num_words[i];
        int  num_words_set1 = arr_num_words[i];
        ///Initialize sets with random words
        sets_struct_init(&set1, sizes_ufp6_dict, num_words_set1);
        sets_struct_init(&set2, sizes_ufp6_dict, num_words_set2);

        encode_matrix_words(&set1, sizes_ufp6_dict, ufp6_dict);
        encode_matrix_words(&set2, sizes_ufp6_dict, ufp6_dict);
        TIMER_START();
        sort_by_alphabetical_order(&set1, sizes_ufp6_dict,flag);
        TIMER_STOP();
        time_delta_merge_s = time_delta;
        printf("Time delta merge_sort %f\n", time_delta_merge_s);
        TIMER_START();
        msdRadixSort(&set2, sizes_ufp6_dict, 0, set2.rowsize, flag);
        TIMER_STOP();
        time_delta_msd = time_delta;
        printf("Time delta msd %f\n", time_delta_msd);
        //write_to_txt_benchmark_sorting(MSD_VS_MERGES_FILE, time_delta_merge_s, time_delta_msd, num_words_set1);
        //is_sorted_matrix(&set1, set1.rowsize, flag);
       // is_sorted_matrix(&set2, set2.rowsize, flag);
    }
}
