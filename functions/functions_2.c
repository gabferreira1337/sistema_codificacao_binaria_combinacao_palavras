#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <ctype.h>
#include "functions_2.h"
#include "functions_1.h"

#define N 10

int main_functions_2(int argc, char **argv) {

    AD_WORDS_HOLDER *arr;
    arr = dynamic_array_init(N);

    free_dynamic_array(arr);
    return 0;
}

AD_WORDS_HOLDER* dynamic_array_init(int size) {
    AD_WORDS_HOLDER *arr = malloc(sizeof(AD_WORDS_HOLDER));

    if(arr == NULL) {
        fperror("Dynamic array malloc 1");
    }

    arr->size = size;
    arr->count = 0;
    arr->array_val = malloc(sizeof(VAL_AD_WORDS_HOLDER) * size);

    if(arr->array_val == NULL) {
        fperror("Dynamic array malloc 2");
    }

    return arr;
}

void free_dynamic_array(AD_WORDS_HOLDER *arr) {
    free(arr->array_val);
    arr->array_val = NULL;
    free(arr);
    arr = NULL;
}

