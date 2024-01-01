#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/time.h>
#include "../functions/functions_2.h"
#include "../functions/functions_1.h"
#include "test_functions_2.h"


#define R 5
#define AD_SIZE 4
#define NUM_SETS 8
#define FILE_WORDS_FOUND_AD "../data/words_found_ad.txt"
#define FILE_WORDS_FOUND_LL "../data/words_found_ll.txt"
#define FILE_AD "../data/ad_history.txt"
#define FILE_AD_BIN "../data/ad_history.bin"
#define FILE_LL "../data/LL_history.txt"
#define FILE_LL_BIN "../data/LL_history.bin"

#define TIMER_START() gettimeofday(&tv1, NULL)
#define TIMER_STOP() \
gettimeofday(&tv2, NULL);    \
timersub(&tv2, &tv1, &tv);   \
time_delta = (float)tv.tv_sec + tv.tv_usec / 1000000.0

struct timeval tv1, tv2, tv;
float time_delta;

int main_test_functions_2(int argc, char **argv) {
    /**
    * @paragraph Test functions to init, reallocate and print Dynamic array AD_WORDS_HOLDER
    */
    test_function_2_8_a();
    /**
    * @paragraph Test functions to insert an element in chronological order
    * (by last modified date ASC) in Dynamic array ,
    */
    //test_function_2_8_b();
    /**
    * @paragraph Test functions to insert an element at given index in Dynamic array
    */
    //test_function_2_8_c();
    /**
    * @paragraph Test functions to remove an element from dynamic array at given index,
    * adjusting the positions of other elements
    */
    //test_function_2_8_d();
    /**
    * @paragraph Test functions to search for words and respective UFP6 only at given
    * indexes of Dynamic array and output to a txt file
    */
    //test_function_2_8_e();
    /**
    * @paragraph Test functions to insert nodes to a LL in chronological order by
    * last modified date DESC
    */
     //test_function_2_9_a();
    /**
    * @paragraph Test functions for inserting nodes at specific indices in a linked list
    */
    //test_function_2_9_b();
    /**
    * @paragraph Test functions to remove node given position / index
    */
    //test_function_2_9_c();
    /**
    * @paragraph Test functions to search for words and their respective UFP6 representation only in
    * specific nodes of a linked list
    */
    //test_function_2_9_d();
    /**
    * @paragraph Use txt files for input and output of sets of words and their
    * respective ufp6 representations Dynamic array
    */
    //test_function_2_10_ad();
    /**
    * @paragraph Use txt files for input and output sets of words and their
    * respective ufp6 representations Linked List
    */
    //test_function_2_10_ll();
    /**
    * @paragraph Use bin files for input and output of sets of words and their
    * respective ufp6 representations Dynamic Array
    */
    //test_functions_2_11_ad();
    /**
    * @paragraph Use bin files for input and output of sets of words and their
    * respective ufp6 representations Linked List
    */
   //test_functions_2_11_ll();

    return 0;
}

void test_function_2_8_a() {
    AD_WORDS_HOLDER *ad = NULL;
    ad = dynamic_array_init(AD_SIZE);
    /**we double the size when ad_SIZE == count before inserting into ad
     * realloc_AD(ad, ad->size * 2)
     * and halve when ad is one-quarter full when removing an element
     * realloc_AD(ad, ad->size / 2)
     **/
    print_AD(ad);
    free_dynamic_array(ad);

    exit(0);
}


void test_function_2_8_b() {
    int dict[MAX_UFP6][BITS - 1]={
            {0, 0},
            {0, 0}
    };
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-compute UFP6 dictionary and an array storing the sizes of
    ///each representation of each UFP6 char
    ufp6_dictionary(dict, sizes_ufp6_dict);

    AD_WORDS_HOLDER *ad_sorted = NULL;
    ad_sorted = dynamic_array_init(AD_SIZE);

    ///Initialize sets with random words and encode them
    SETS sets[NUM_SETS] = {0};
    for (int i = 0; i < NUM_SETS; ++i) {
        sets_struct_init(&sets[i], sizes_ufp6_dict,R);
        encode_matrix_words(&sets[i], sizes_ufp6_dict, dict);
    }

    char *testDates[] = {
            "2023-11-25",       ///Test insert when empty
            "2022-11-24",       ///Test insert to first index
            "2023-10-01",       ///Test insert between two elements
            "2024-01-15",       ///Test insert in last index

    };
    ///Insert elements to Dynamic array in chronological order ASC
    for (int i = 0, j = 0; i < NUM_SETS && j < sizeof(testDates) / sizeof(testDates[0]); i+=2, j++) {
        insert_element_to_AD_in_order(ad_sorted, &sets[i], &sets[i + 1],testDates[j]);
    }
    print_AD(ad_sorted);

    free_dynamic_array(ad_sorted);
    exit(0);
}

void test_function_2_8_c() {
    int dict[MAX_UFP6][BITS - 1]={
            {0, 0},
            {0, 0}
    };
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-compute UFP6 dictionary and an array storing the sizes of
    ///each representation of each UFP6 char
    ufp6_dictionary(dict, sizes_ufp6_dict);
    AD_WORDS_HOLDER *ad = NULL;
    ad = dynamic_array_init(AD_SIZE);
    ///Initialize sets with random words and encode them
    SETS sets[NUM_SETS] = {0};
    for (int i = 0; i < NUM_SETS; ++i) {
        sets_struct_init(&sets[i], sizes_ufp6_dict,R);
        encode_matrix_words(&sets[i], sizes_ufp6_dict, dict);
    }

    char *testDates[] = {
            "2023-11-25",
            "2022-11-24",
            "2023-10-01",
            "2024-01-15",
    };
    int indexes[] = { 0, 1, 1, 3};
    for (int i = 0, j = 0; i < NUM_SETS && j < sizeof(testDates) / sizeof(testDates[0]); i+=2, j++) {
        insert_element_to_index_AD(ad, &sets[i], &sets[i + 1],testDates[j], indexes[j]);
    }

    print_AD(ad);
    free_dynamic_array(ad);
    exit(0);
}


void test_function_2_8_d() {
    int dict[MAX_UFP6][BITS - 1]={
            {0, 0},
            {0, 0}
    };
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-compute UFP6 dictionary and an array storing the sizes of
    ///each representation of each UFP6 char
    ufp6_dictionary(dict, sizes_ufp6_dict);
    AD_WORDS_HOLDER *ad = NULL;
    ad = dynamic_array_init(AD_SIZE);
    ///Initialize sets with random words and encode them
    SETS sets[NUM_SETS] = {0};
    for (int i = 0; i < NUM_SETS; ++i) {
        sets_struct_init(&sets[i], sizes_ufp6_dict,R);
        encode_matrix_words(&sets[i], sizes_ufp6_dict, dict);
    }

   const char *testDates[] = {
            "2023-11-25",
            "2022-11-24",
            "2023-10-01",
            "2024-01-15",
    };
    int indexes[] = { 0, 1, 1, 3};
    for (int i = 0, j = 0; i < NUM_SETS && j < sizeof(testDates) / sizeof(testDates[0]); i+=2, j++) {
        insert_element_to_index_AD(ad, &sets[i], &sets[i + 1],testDates[j], indexes[j]);
    }

    //print_AD(ad);

    int delete_element = 3;
    delete_element_index(ad, delete_element);
    printf("\nAfter delete element %d\n", delete_element);
    print_AD(ad);
    free_dynamic_array(ad);

    exit(0);
}

void test_function_2_8_e() {
    int dict[MAX_UFP6][BITS - 1] = {
            {0, 0},
            {0, 0}
    };
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-compute UFP6 dictionary and an array storing the sizes of
    ///each representation of each UFP6 char
    ufp6_dictionary(dict, sizes_ufp6_dict);
    AD_WORDS_HOLDER *ad = NULL;
    ad = dynamic_array_init(AD_SIZE);
    ///Initialize sets with random words and encode them
    SETS sets[NUM_SETS] = {0};
    for (int i = 0; i < NUM_SETS; ++i) {
        sets_struct_init(&sets[i], sizes_ufp6_dict, R);
        encode_matrix_words(&sets[i], sizes_ufp6_dict, dict);
    }

    const char *insert_words_[] = {
            "ola",
            "olas",
    };
    int isize = sizeof(insert_words_) / sizeof(insert_words_[0]);

    ///Insert words to after test search function
    insert_words(&sets[0], insert_words_, sizes_ufp6_dict, dict, 1);
    insert_words(&sets[1], insert_words_, sizes_ufp6_dict, dict, isize);

    const char *testDates[] = {
            "2023-11-25",
            "2022-11-24",
            "2023-10-01",
            "2024-01-15",
    };
    int indexes[] = { 0, 1, 1, 3};
    for (int i = 0, j = 0; i < NUM_SETS && j < sizeof(testDates) / sizeof(testDates[0]); i+=2, j++) {
        insert_element_to_index_AD(ad, &sets[i], &sets[i + 1],testDates[j], indexes[j]);
    }
    const char *find_words[] = {
            "ola",
            "olas",
            "ol+",      ///Test invalid input
    };
    int fsize = sizeof(find_words) / sizeof(find_words[0]);

    ///Search for words between index 0 and 1 and write to a txt file and print
    find_words_ad(ad, find_words, fsize, 0, 1,FILE_WORDS_FOUND_AD,1);
    ///Search for words and print to print
    //find_words_ad(ad, find_words, fsize, 0, 1,NULL,0);

    free_dynamic_array(ad);
    exit(0);
}

void test_function_2_9_a() {
    int dict[MAX_UFP6][BITS - 1] = {
            {0, 0},
            {0, 0}
    };
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-compute UFP6 dictionary and an array storing the sizes of
    ///each representation of each UFP6 char
    ufp6_dictionary(dict, sizes_ufp6_dict);
    LL_WORDS_HOLDER *ll = ll_init();
    ///Initialize sets with random words and encode them into set
    SETS sets[NUM_SETS] = {0};
    for (int i = 0; i < NUM_SETS; ++i) {
        sets_struct_init(&sets[i], sizes_ufp6_dict, R);
        encode_matrix_words(&sets[i], sizes_ufp6_dict, dict);
    }
    const char *testDates[] = {
            "2023-11-25",       ///Test Insert to head when empty
            "2022-11-24",       ///Test Insert to head
            "2023-10-01",       ///Test Insert between two nodes
            "2024-01-15",       ///Test Insert to tail
    };
    ///Insert nodes into LL in chronological order by last modified date DESC
    for (int i = 0, j = 0; i < NUM_SETS && j < sizeof(testDates) / sizeof(testDates[0]); i+=2, j++) {
        insert_node_ll_sorted(ll, &sets[i], &sets[i + 1],testDates[j]);
    }

    print_ll_words_holder(ll);
    free_ll_words_holder(ll);
}

void test_function_2_9_b() {
    int dict[MAX_UFP6][BITS - 1] = {
            {0, 0},
            {0, 0}
    };
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-compute UFP6 dictionary and an array storing the sizes of
    ///each representation of each UFP6 char
    ufp6_dictionary(dict, sizes_ufp6_dict);
    LL_WORDS_HOLDER *ll = ll_init();
    ///Initialize sets with random words and encode them
    SETS sets[NUM_SETS] = {0};
    for (int i = 0; i < NUM_SETS; ++i) {
        sets_struct_init(&sets[i], sizes_ufp6_dict, R);
        encode_matrix_words(&sets[i], sizes_ufp6_dict, dict);
    }
    const char *testDates[] = {
            "2023-11-25",
            "2022-11-24",
            "2023-10-01",
            "2024-01-15",
    };
    int indexes[] = { 0, 1, 1, 3};
    ///Insert nodes into LL in chronological order by last modified date DESC
    for (int i = 0, j = 0; i < NUM_SETS && j < sizeof(testDates) / sizeof(testDates[0]); i+=2, j++) {
        insert_node_ll_index(ll, &sets[i], &sets[i + 1],testDates[j], indexes[j]);
    }

    print_ll_words_holder(ll);
    free_ll_words_holder(ll);
    exit(0);
}

void test_function_2_9_c() {
    int dict[MAX_UFP6][BITS - 1] = {
            {0, 0},
            {0, 0}
    };
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-compute UFP6 dictionary and an array storing the sizes of
    ///each representation of each UFP6 char
    ufp6_dictionary(dict, sizes_ufp6_dict);
    LL_WORDS_HOLDER *ll = ll_init();
    ///Initialize sets with random words and encode them
    SETS sets[NUM_SETS] = {0};
    for (int i = 0; i < NUM_SETS; ++i) {
        sets_struct_init(&sets[i], sizes_ufp6_dict, R);
        encode_matrix_words(&sets[i], sizes_ufp6_dict, dict);
    }
    const char *testDates[] = {
            "2023-11-25",
            "2022-11-24",
            "2023-10-01",
            "2024-01-15",
    };
    int indexes[] = { 0, 1, 1, 3};
    ///Insert nodes into LL in chronological order by last modified date DESC
    for (int i = 0, j = 0; i < NUM_SETS && j < sizeof(testDates) / sizeof(testDates[0]); i+=2, j++) {
        insert_node_ll_index(ll, &sets[i], &sets[i + 1],testDates[j], indexes[j]);
    }
    ///Delete nodes
    //print_ll_words_holder(ll);
     delete_ll_node_index(ll, 0);        //delete first
    //delete_ll_node_index(ll, 2);        //delete between nodes
    //delete_ll_node_index(ll, ll->nnodes - 1);        //delete last

    print_ll_words_holder(ll);
    free_ll_words_holder(ll);
    exit(0);
}

void test_function_2_9_d() {
    int dict[MAX_UFP6][BITS - 1] = {
            {0, 0},
            {0, 0}
    };
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-compute UFP6 dictionary and an array storing the sizes of
    ///each representation of each UFP6 char
    ufp6_dictionary(dict, sizes_ufp6_dict);
    LL_WORDS_HOLDER *ll = ll_init();
    ///Initialize sets with random words and encode them
    SETS sets[NUM_SETS] = {0};
    for (int i = 0; i < NUM_SETS; ++i) {
        sets_struct_init(&sets[i], sizes_ufp6_dict, R);
        encode_matrix_words(&sets[i], sizes_ufp6_dict, dict);
    }
    const char *insert_words_[] = {
            "ola",
            "olas",
    };
    int isize = sizeof(insert_words_) / sizeof(insert_words_[0]);

    ///Insert words to after test search function
    insert_words(&sets[0], insert_words_, sizes_ufp6_dict, dict, 1);
    insert_words(&sets[1], insert_words_, sizes_ufp6_dict, dict, isize);

    const char *testDates[] = {
            "2023-11-25",
            "2022-11-24",
            "2023-10-01",
            "2024-01-15",
    };
    int indexes[] = { 0, 1, 1, 3};
    ///Insert nodes into LL in chronological order by last modified date DESC
    for (int i = 0, j = 0; i < NUM_SETS && j < sizeof(testDates) / sizeof(testDates[0]); i+=2, j++) {
        insert_node_ll_index(ll, &sets[i], &sets[i + 1],testDates[j], indexes[j]);
    }

    const char *find_words[] = {
            "ola",
            "olas",
            "ol+",      ///Test invalid input
    };
    int fsize = sizeof(find_words) / sizeof(find_words[0]);
    int flag = 1;

    ///Find words in given nodes and output to console
   // find_words_ll(ll, find_words, NULL,fsize, 0, 1, flag);
    ///Search for words between index 0 and 1 and write to a txt file and output to console
    find_words_ll(ll, find_words,FILE_WORDS_FOUND_LL ,fsize, 0, 1,flag);

    free_ll_words_holder(ll);
    exit(0);
}



void test_function_2_10_ad() {
    int dict[MAX_UFP6][BITS - 1]={
            {0, 0},
            {0, 0}
    };
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-compute UFP6 dictionary and an array storing the sizes of
    ///each representation of each UFP6 char
    ufp6_dictionary(dict, sizes_ufp6_dict);

    AD_WORDS_HOLDER *ad_sorted = NULL;
    ad_sorted = dynamic_array_init(AD_SIZE);

    ///Initialize sets with random words and encode them
    SETS sets[NUM_SETS] = {0};
    for (int i = 0; i < NUM_SETS; ++i) {
        sets_struct_init(&sets[i], sizes_ufp6_dict,R);
        encode_matrix_words(&sets[i], sizes_ufp6_dict, dict);
    }

    char *testDates[] = {
            "2023-11-25",       ///Test insert when empty
            "2022-11-24",       ///Test insert to first index
            "2023-10-01",       ///Test insert between two elements
            "2024-01-15",       ///Test insert in last index

    };
    int indices[] = {0, 1, 2, 3};
    ///Insert elements to Dynamic array in chronological order ASC
    for (int i = 0, j = 0; i < NUM_SETS && j < sizeof(testDates) / sizeof(testDates[0]); i+=2, j++) {
        insert_element_to_AD_in_order(ad_sorted, &sets[i], &sets[i + 1],testDates[j]);
        //insert_element_to_index_AD(arr_din, &sets[i],&sets[i + 1], testDates[j], indices[j]);
    }

    //print_AD(ad_sorted);
    ///Write Dynamic array to txt file
    write_ad_to_txt(ad_sorted,FILE_AD);
    ///Read from txt file to arr_din2
    AD_WORDS_HOLDER *arr_din2 = NULL;
    /// Last argument is a flag , if set to 1 read in chronological order
    /// Pass to function address of pointer arr_din so changes stay outside function
    read_from_txt_to_ad(&arr_din2, FILE_AD, 1);

    print_AD(arr_din2);

    free_dynamic_array(ad_sorted);
    free_dynamic_array(arr_din2);
    exit(0);
}


void test_function_2_10_ll() {
    int dict[MAX_UFP6][BITS - 1] = {
            {0, 0},
            {0, 0}
    };
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-compute UFP6 dictionary and an array storing the sizes of
    ///each representation of each UFP6 char
    ufp6_dictionary(dict, sizes_ufp6_dict);
    LL_WORDS_HOLDER *ll = ll_init();
    ///Initialize sets with random words and encode them
    SETS sets[NUM_SETS] = {0};
    for (int i = 0; i < NUM_SETS; ++i) {
        sets_struct_init(&sets[i], sizes_ufp6_dict, R);
        encode_matrix_words(&sets[i], sizes_ufp6_dict, dict);
    }
    const char *testDates[] = {
            "2023-11-25",       ///Test Insert to head when empty
            "2022-11-24",       ///Test Insert to head
            "2023-10-01",       ///Test Insert between two nodes
            "2024-01-15",       ///Test Insert to tail
    };
   // int indices[] = {0, 1, 2, 3};
    ///Insert nodes into LL in chronological order by last modified date DESC
    for (int i = 0, j = 0; i < NUM_SETS && j < sizeof(testDates) / sizeof(testDates[0]); i+=2, j++) {
        insert_node_ll_sorted(ll, &sets[i], &sets[i + 1],testDates[j]);
        //insert_node_ll_index(ll, &sets[i],&sets[i + 1], testDates[j], indices[j]);

    }
    ///Write to txt file Linked List
    write_ll_to_txt(ll,FILE_LL);
    free_ll_words_holder(ll);

    LL_WORDS_HOLDER *ll_2 = ll_init();
    int flag = 1;
    /// Last argument is a flag , if set to 1 read in chronological order DESC
    ///Pass to function address of pointer arr_din so changes stay outside function
    read_from_txt_to_ll(ll_2,FILE_LL, flag);
    print_ll_words_holder(ll_2);

    free_ll_words_holder(ll_2);
    exit(0);
}

void test_functions_2_11_ad() {
    int dict[MAX_UFP6][BITS - 1]={
            {0, 0},
            {0, 0}
    };
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-compute UFP6 dictionary and an array storing the sizes of
    ///each representation of each UFP6 char
    ufp6_dictionary(dict, sizes_ufp6_dict);

    AD_WORDS_HOLDER *ad_sorted = NULL;
    ad_sorted = dynamic_array_init(AD_SIZE);

    ///Initialize sets with random words and encode them
    SETS sets[NUM_SETS] = {0};
    for (int i = 0; i < NUM_SETS; ++i) {
        sets_struct_init(&sets[i], sizes_ufp6_dict,R);
        encode_matrix_words(&sets[i], sizes_ufp6_dict, dict);
    }

    char *testDates[] = {
            "2023-11-25",       ///Test insert when empty
            "2022-11-24",       ///Test insert to first index
            "2023-10-01",       ///Test insert between two elements
            "2024-01-15",       ///Test insert in last index

    };
    int indices[] = {0, 1, 2, 3};
    ///Insert elements to Dynamic array in chronological order ASC
    for (int i = 0, j = 0; i < NUM_SETS && j < sizeof(testDates) / sizeof(testDates[0]); i+=2, j++) {
        insert_element_to_AD_in_order(ad_sorted, &sets[i], &sets[i + 1],testDates[j]);
        //insert_element_to_index_AD(ad_sorted, &sets[i],&sets[i + 1], testDates[j], indices[j]);
    }

    //print_AD(ad_sorted);
    write_ad_to_bin(ad_sorted,FILE_AD_BIN);
    free_dynamic_array(ad_sorted);

    AD_WORDS_HOLDER *arr_din2 = NULL;
    int flag = 1; /// Read from file to dynamic array in chronological order ASC
    /// Last argument is a flag , if set to 1 read in chronological order
    ///Pass to function address of pointer arr_din so changes stay outside function
    read_from_bin_to_ad(&arr_din2, FILE_AD_BIN, flag);

    print_AD(arr_din2);

    free_dynamic_array(arr_din2);
    exit(0);
}

void test_functions_2_11_ll() {
    int dict[MAX_UFP6][BITS - 1] = {
            {0, 0},
            {0, 0}
    };
    int sizes_ufp6_dict[MAX_UFP6] = {0};
    ///Pre-compute UFP6 dictionary and an array storing the sizes of
    ///each representation of each UFP6 char
    ufp6_dictionary(dict, sizes_ufp6_dict);
    LL_WORDS_HOLDER *ll = ll_init();
    ///Initialize sets with random words and encode them
    SETS sets[NUM_SETS] = {0};
    for (int i = 0; i < NUM_SETS; ++i) {
        sets_struct_init(&sets[i], sizes_ufp6_dict, R);
        encode_matrix_words(&sets[i], sizes_ufp6_dict, dict);
    }
    const char *testDates[] = {
            "2023-11-25",       ///Test Insert to head when empty
            "2022-11-24",       ///Test Insert to head
            "2023-10-01",       ///Test Insert between two nodes
            "2024-01-15",       ///Test Insert to tail
    };
    // int indices[] = {0, 1, 2, 3};
    ///Insert nodes into LL in chronological order by last modified date DESC
    for (int i = 0, j = 0; i < NUM_SETS && j < sizeof(testDates) / sizeof(testDates[0]); i+=2, j++) {
         insert_node_ll_sorted(ll, &sets[i], &sets[i + 1],testDates[j]);
        //insert_node_ll_index(ll, &sets[i],&sets[i + 1], testDates[j], indices[j]);
    }

    ///Write to bin file Linked List
    write_ll_to_binfile(ll,FILE_LL_BIN);
    free_ll_words_holder(ll);

    LL_WORDS_HOLDER *ll_2 = ll_init();
    int flag = 1;       /// Read from bin file to LL in chronological order DESC
    /// Last argument is a flag , if set to 1 read in chronological order
    ///Pass to function address of pointer arr_din so changes stay outside function
    read_from_binfile_to_ll(ll_2,FILE_LL_BIN, flag);
    print_ll_words_holder(ll_2);

    free_ll_words_holder(ll_2);
    exit(0);
}

