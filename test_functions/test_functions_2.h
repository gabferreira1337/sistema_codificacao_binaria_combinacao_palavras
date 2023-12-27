#ifndef PROJETO_AED1_LP1_TEST_FUNCTIONS_2_H
#define PROJETO_AED1_LP1_TEST_FUNCTIONS_2_H

/**
 * @paragraph Test functions to init, reallocate and print Dynamic array AD_WORDS_HOLDER
 */
void test_function_2_8_a();
/**
 * @paragraph Test functions to insert an element in chronological order
 * (by last modified date) in Dynamic array ,
 */
void test_function_2_8_b();
/**
 * @paragraph Test functions to insert an element at given index in Dynamic array
 */
void test_function_2_8_c();
/**
 * @paragraph Test functions to remove an element from dynamic array at given index,
 * adjusting the positions of other elements
 */
void test_function_2_8_d();
/**
 * @paragraph Test functions to search for words and respective UFP6 only at given
 * indexes of Dynamic array and output to a txt file
 */
void test_function_2_8_e();
/**
 * @paragraph Test functions to insert nodes to a LL in chronological order by
 * last modified date DESC
 */
void test_function_2_9_a();
/**
 * @paragraph Test functions for inserting nodes at specific index in a linked list
 */
void test_function_2_9_b();
/**
 * @paragraph Test functions for delete nodes at specific index in a linked list
 */
void test_function_2_9_c();
/**
 * @paragraph Use txt files for input and output of sets of words and their
 * respective ufp6 representations
 * In this function we test all functions to write a Dynamic array AD_WORDS_HOLDER
 * to txt file and after read that file to aa new Dynamic array
 */
void test_function_2_10_ad();
/**
 * @paragraph Use txt files for input and output of sets of words and their
 * respective ufp6 representations
 * In this function we test all functions to write a linked list LL_WORDS_HOLDER
 * to txt file and after read that file to a new Linked List
 */
void test_function_2_10_ll();
/**
 * @paragraph Use bin files for input and output of sets of words and their
 * respective ufp6 representations
 * In this function we test all functions to write Dynamic Array AD_WORD_HOLDER
 * to bin file and after read that file to a new Dynamic Array AD_WORDS_HOLDER
 */
void test_functions_2_11_ad();
/**
 * @paragraph Use bin files for input and output of sets of words and their
 * respective ufp6 representations
 * In this function we test all functions to write a linked list LL_WORDS_HOLDER
 * to bin file and after read that file to a new Linked List
 */
void test_functions_2_11_ll();


int main_test_functions_2(int argc, char **argv);
#endif //PROJETO_AED1_LP1_TEST_FUNCTIONS_2_H
