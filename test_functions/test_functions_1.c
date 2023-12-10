#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_functions_1.h"
#include "../functions/functions_1.h"

#define M_KMP 8
#define R 5
#define C 5
#define WORD_LENGTH 5
#define BITS 7
#define RADIX 36

int main_test_functions_1(int argc, char **argv) {
    SETS set1;
    SETS set2;
    //Feature 1
    test_function1_feature1(&set1,&set2, R);

    //Feature 2
    // dictionary with UFP6
    int dic[MAX_UFP6][BITS];
    // sizes of each binary representation
    int sizes_bin_dic[MAX_UFP6];
    test_function1_feature2(&set1,&set2, sizes_bin_dic, dic);
    test_function1_feature3(&set1, &set2, sizes_bin_dic, dic);

    freemem(&set1);
    freemem(&set2);

    exit(0);
    return 0;
}

void test_function1_feature1(SETS *set1, SETS *set2,int number_words) {
    /* Initialize set1  */
    sets_struct_init(set1, number_words);
    /* Initialize set2  */
    sets_struct_init(set2, number_words);

    //printf("Feature 1 !!!!\n");

    /* Print set1
    printf("SET 1 !!!!\n");
    print_matrix_char(set1);
    print_matrix_int(set1);*/
    /* Print set2 Matrix
    printf("SET 2 !!!!\n");
    print_matrix_char(set2);
    print_matrix_int(set2);*/
}

void test_function1_feature2(SETS *set1, SETS *set2, int sizes_bin_dict[], int bin_dict[MAX_UFP6][BITS]) {
    // Pre-compute dictionary of binary representations and their respective size
    binary_dictionary(bin_dict, sizes_bin_dict);

   // char word[] = "ola";
   /* int W = 1;
    //result of bin representation
    int result[100];
    //array with bin sizes of each word for only test purpose
    int size[W];
    encode_word(word, result,size, 0, sizes_bin_dict, bin_dict);

    for (int i = 0; i < size[0]; ++i) {
        printf("%d", result[i]);
    }*/

    /* Encode SET1      */
    //encode_matrix_words(set1, sizes_bin_dict, bin_dict);

    /* Encode SET2      */
   // encode_matrix_words(set1, sizes_bin_dict, bin_dict);
   /* printf("\nFeature 2 !!!!\n");
    printf("SET 1 !!!!\n");
    print_matrix_char(set1);
    print_matrix_int(set1);
   /* printf("SET 2 !!!!\n");
    print_matrix_char(set2);
    print_matrix_int(set2);*/
}

void test_function1_feature3(SETS *set1, SETS *set2, int *sizes_bin_dict, int bin_dict[RADIX][BITS]) {
    matrix_rnd_char_gen(set1);
    matrix_rnd_char_gen(set2);

    const char *insert_words1[] = {"ola", "olas","L","123"};
    int N1 = 4;
    //print_matrix_char(set1);
    encode_matrix_words(set1,sizes_bin_dict,bin_dict);
    insert_words(set1,insert_words1,sizes_bin_dict,bin_dict, N1);

    printf("SET 1 !!!!\n");
    print_matrix_char(set1);
    print_matrix_int(set1);
   /*const char *insert_words2[] = {"ola", "olas"};
    int N2 = 2;

    insert_words(set2,insert_words2,sizes_bin_dict,bin_dict, N2);
    printf("SET 2 !!!!\n");
    print_matrix_char(set2);
    print_matrix_int(set2);*/
}


