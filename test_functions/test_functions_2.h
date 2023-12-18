#ifndef PROJETO_AED1_LP1_TEST_FUNCTIONS_2_H
#define PROJETO_AED1_LP1_TEST_FUNCTIONS_2_H

void test_function_2_a();
void test_function_2_8_b(int *sizes_bin_dict, int bin_dict[][BITS]);
void test_function_2_8_c(int *sizes_bin_dict, int bin_dict[][BITS]);
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
