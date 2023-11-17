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

    strcpy(arr->array_val[0].last_update_date, get_current_date());

    printf("date: %s\n",arr->array_val[0].last_update_date);



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

    for (int i = 0; i < size; ++i) {
        arr->array_val->last_update_date = malloc(sizeof(char) * 9);
        if(arr == NULL) {
            fperror("Dynamic array last_update_date_malloc ");
        }
    }

    return arr;
}

void init_VAL_AD_WORDS_HOLDER(VAL_AD_WORDS_HOLDER *val_holder) {

}


void free_dynamic_array(AD_WORDS_HOLDER *arr) {
    free(arr->array_val);
    arr->array_val = NULL;
    free(arr);
    arr = NULL;
}

char *get_current_date() {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Format the date
    char *date_str = malloc(sizeof(char) * 20); // Adjust the size as needed
    strftime(date_str, 14, "%d/%m/%y", timeinfo);
    return date_str;
}

void insert_element_to_ad(VAL_AD_WORDS_HOLDER val_holder, AD_WORDS_HOLDER *ad_holder) {
    ad_holder->array_val[ad_holder->count] = val_holder;


}

