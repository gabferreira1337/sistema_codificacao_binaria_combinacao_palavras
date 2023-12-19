#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "test_functions_1.h"
#include "../functions/functions_1.h"

#define M_KMP 8
#define R 11
#define C 5
#define WORD_LENGTH 5
#define BITS 7
#define RADIX 63
#define  FILE_WORDS_FOUND_SET "set_words_found.txt"

#define TIMER_START() gettimeofday(&tv1, NULL)
#define TIMER_STOP() \
gettimeofday(&tv2, NULL);    \
timersub(&tv2, &tv1, &tv);   \
time_delta = (float)tv.tv_sec + tv.tv_usec / 1000000.0

struct timeval tv1, tv2, tv;
float time_delta;

int main_test_functions_1(int argc, char **argv) {
   // TIMER_START();
    /**1) Test functions to search words in a given set of words and their respective ufp6
    * representation and output into console and txt file
    */
    //test_function1_feature1();
    /**2) Test functions to search words in a given set of words and their respective ufp6
    * representation and output into console and txt file
    */
    //test_function1_feature2(&set1,&set2, sizes_bin_dic, dic);
    /**3) Test functions to search words in a given set of words and their respective ufp6
    * representation and output into console and txt file
    */
   // test_function1_feature3();
   /**5) Test functions to search words in a given set of words and their respective ufp6
    * representation and output into console and txt file
    */
    //test_functions1_feature5();
    /**6) Test functions to sort set by alphabetical order (ASC and DESC) and sort by words_size
     * (ASC and DESC)
    */
     test_functions1_feature6();
     //TIMER_STOP();
   // fprintf(stdout, "time_delta %f\n", time_delta);

    exit(0);
    return 0;
}

void test_function1_feature1(){
    SETS set1 = {NULL, NULL, NULL, NULL, 0, 0};
    SETS set2 = {NULL, NULL, NULL, NULL, 0, 0};
    int  num_words_set1 = 5;
    int  num_words_set2 = 5;

    /* Initialize set1  */
    sets_struct_init(&set1, num_words_set1);
    /* Initialize set2  */
    sets_struct_init(&set2, num_words_set2);

    /* Print set1 */
    printf("SET 1 !!!!\n");
    print_matrix_char(&set1);
    print_matrix_int(&set1);
    /* Print set2 Matrix*/
    printf("SET 2 !!!!\n");
    print_matrix_char(&set2);
    print_matrix_int(&set2);

}

void test_function1_feature2(int sizes_bin_dict[], int bin_dict[MAX_UFP6][BITS]) {
    int dic[MAX_UFP6][BITS]={
            {0, 0},
            {0, 0}
    };
    // sizes of each binary representation
    int sizes_bin_dic[MAX_UFP6] = {0};
    // Pre-compute dictionary of binary representations and their respective size
    ufp6_dictionary(bin_dict, sizes_bin_dict);

    char word[] = "ola";
    int W = 1;
    //result of ufp6 representation
    int result[100];
    //array with ufp6 size of a word for only test purpose
    int size[W];
    encode_word(word, result,size, 0, sizes_bin_dict, bin_dict);

    for (int i = 0; i < size[0]; ++i) {
        printf("%d", result[i]);
    }

    SETS set1 = {NULL, NULL, NULL, NULL, 0, 0};
    SETS set2 = {NULL, NULL, NULL, NULL, 0, 0};
    int  num_words_set1 = 5;
    int  num_words_set2 = 5;

    sets_struct_init(&set1, num_words_set1);
    sets_struct_init(&set2, num_words_set2);

    matrix_rnd_char_gen(&set1);
    matrix_rnd_char_gen(&set2);

    /* Encode SET1      */
    encode_matrix_words(&set1, sizes_bin_dict, bin_dict);

    /* Encode SET2      */
    encode_matrix_words(&set1, sizes_bin_dict, bin_dict);
    printf("SET 1 !!!!\n");
    print_matrix_char(&set1);
    print_matrix_int(&set1);
    printf("SET 2 !!!!\n");
    print_matrix_char(&set2);
    print_matrix_int(&set2);
}

void test_function1_feature3() {
    int ufp6_dict[MAX_UFP6][BITS]={
            {0, 0},
            {0, 0}
    };
    // sizes of each binary representation
    int sizes_bin_dict[MAX_UFP6] = {0};
    ufp6_dictionary(ufp6_dict,sizes_bin_dict);
    SETS set1 = {NULL, NULL, NULL, NULL, 0, 0};
    SETS set2 = {NULL, NULL, NULL, NULL, 0, 0};
    int  num_words_set1 = 5;
    int  num_words_set2 = 5;

    sets_struct_init(&set1, num_words_set1);
    sets_struct_init(&set2, num_words_set2);

    matrix_rnd_char_gen(&set1);
    matrix_rnd_char_gen(&set2);

    const char *insert_words1[] = {"ol4", "ola","L","123"};
    int N1 = 4;
    encode_matrix_words(&set1,sizes_bin_dict,ufp6_dict);
    //print_matrix_int(set1);
    insert_words(&set1,insert_words1,sizes_bin_dict,ufp6_dict, N1);
    printf("SET 1 !!!!\n");
    print_matrix_char(&set1);
    print_matrix_int(&set1);

    remove_Words(&set1, insert_words1, N1);

    encode_matrix_words(&set1,sizes_bin_dict,ufp6_dict);
    //print_matrix_int(set1);
    insert_words(&set1,insert_words1,sizes_bin_dict,ufp6_dict, N1);
    printf("SET 1 !!!!\n");
    print_matrix_char(&set1);
    print_matrix_int(&set1);
    /*const char *insert_words2[] = {"ola", "olas"};
    int N2 = 2;

    insert_words(&set2,insert_words2,sizes_bin_dict,bin_dict, N2);
    printf("SET 2 !!!!\n");
    print_matrix_char(&set2);
    print_matrix_int(&set2);*/
}

void test_functions1_feature5(){
    int bin_dict[MAX_UFP6][BITS]={
            {0, 0},
            {0, 0}
    };

    // sizes of each binary representation
    int sizes_bin_dict[MAX_UFP6] = {0};
    //Pre-Compute UFP6 dictionary
    ufp6_dictionary(bin_dict, sizes_bin_dict);
    SETS set1 = {NULL, NULL, NULL, NULL, 0, 0};
    SETS set2 = {NULL, NULL, NULL, NULL, 0, 0};
    int  num_words_set1 = 5;
    int  num_words_set2 = 5;

    sets_struct_init(&set1, num_words_set1);
    sets_struct_init(&set2, num_words_set2);
    //Generate random words
    matrix_rnd_char_gen(&set1);
    matrix_rnd_char_gen(&set2);

    const  char *words_insert[] = {"ola", "olas"};
    int num_words = 2;

    const  char *words_search[] = {"ola","olas"};
    int num_words_search = 2;
    //insert words in set
    insert_words(&set1, words_insert, sizes_bin_dict, bin_dict, num_words);
    //search for words and their respective ufp6 representation without writing to a txt file
   // find_Words(&set1, words_search, num_words_search, NULL, 0);
    //search for words and their respective ufp6 representation and writing to a txt file
    find_Words(&set1, words_search, num_words_search, FILE_WORDS_FOUND_SET, 1);
    freemem(&set1);
    freemem(&set2);

}

void test_functions1_feature6() {
    int bin_dict[MAX_UFP6][BITS]={
            {0, 0},
            {0, 0}
    };

    // sizes of each binary representation
    int sizes_bin_dict[MAX_UFP6] = {0};
    //Pre-Compute UFP6 dictionary
    ufp6_dictionary(bin_dict, sizes_bin_dict);
    SETS set1 = {NULL, NULL, NULL, NULL, 0, 0};
    SETS set2 = {NULL, NULL, NULL, NULL, 0, 0};
    int num_words_set2 = R;
    int  num_words_set1 = R;

    sets_struct_init(&set1, num_words_set1);
    sets_struct_init(&set2, num_words_set2);

    //Generate random words
    matrix_rnd_char_gen(&set1);
    matrix_rnd_char_gen(&set2);

    encode_matrix_words(&set1, sizes_bin_dict, bin_dict);
    encode_matrix_words(&set2, sizes_bin_dict, bin_dict);

    print_matrix_int(&set1);
    print_matrix_char(&set1);

    /** * @paragraph Sort by alphabetical order (ASC and DESC)
     *  if flag set to 1 = ASC ,if set to 0 = DESC*/
    printf("Sort by alphabetical order\n");
    int flag = 0; // ASC
    TIMER_START();
     msdRadixSort(&set1,sizes_bin_dict, 0, set1.rowsize, flag);
    TIMER_STOP();
    fprintf(stdout, "Time_delta MSD %f\n", time_delta);
    is_sorted_matrix(&set1, set1.rowsize, flag);
    print_matrix_int(&set1);
    print_matrix_char(&set1);
   /* TIMER_START();
    insertion_sort_char(&set2, set2.rowsize, 1);
    TIMER_STOP();
    is_sorted(&set2, set2.rowsize);
    fprintf(stdout, "Time_delta Insertion sort %f\n", time_delta);*/

    /** * @paragraph Sort by words_size in (ASC and DESC)
     *  if flag set to 1 = ASC, if set to 0 = DESC*/
   /* printf("Sort by words size\n");
    sort_size(&set1, flag);

    print_matrix_char(&set1);
    print_matrix_int(&set1);
    print_arr_word_size(&set1);
    is_sorted_sizes(&set1, set1.rowsize, flag);
*/
    freemem(&set1);
    freemem(&set2);
}