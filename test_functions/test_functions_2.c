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

int main_test_functions_2(int argc, char **argv) {


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
