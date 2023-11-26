#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <ctype.h>
#include "functions_2.h"
#include "functions_1.h"

#define R 5
#define DATE_SIZE 20

#define N 1

int main_functions_2(int argc, char **argv) {

    AD_WORDS_HOLDER *arr_din;
    arr_din = dynamic_array_init(N);
    int dic[MAX_UFP6][BITS];
    int sizes[MAX_UFP6];

    binary_dictionary(dic, sizes);
    SETS set1 ;
    sets_struct_init(&set1, R);
    SETS set2 ;
    sets_struct_init(&set2, R);

    //encode_matrix_words(&set1, sizes, dic);

    insert_element_to_AD(arr_din, set1, set2);
    insert_element_to_AD(arr_din, set1, set2);
    /*insert_element_to_AD(arr_din, set1, set2);
    insert_element_to_AD(arr_din, set1, set2);
    insert_element_to_AD(arr_din, set1, set2);*/



    char *testDates[] = {
            "2023-11-25",
            "2023-11-24",
            "2022-12-01",
            "2023-01-15",
            "2022-08-10",
    };
    char **result = malloc(arr_din->count * sizeof(char *));

    for (int i = 0; i < arr_din->count; i++) {
        result[i] = malloc(9 * sizeof(char));
    }

    for (int l = 0; l < arr_din->count ; ++l) {
        result[l ] = arr_din->array_val[l].last_update_date;
    }
    for (int i = 0; i < arr_din->count; ++i) {
        printf("time %s\n", result[i]);
    }
    sort(&arr_din->array_val,result, 0, arr_din->count);
    print_AD(arr_din);
    for (int i = 0; i < arr_din->count; i++) {
        free(result[i]);
    }

    free(result);
    free_dynamic_array(arr_din);
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
        fperror("Dynamic array array_val_malloc ");
    }

    for (int i = 0; i < size; ++i) {
        arr->array_val[i].last_update_date = NULL;
    }

    return arr;
}


void free_dynamic_array(AD_WORDS_HOLDER *arr) {
    for (int i = 0; i < arr->size; ++i) {
        free(arr->array_val[i].last_update_date);
        arr->array_val[i].last_update_date = NULL;
    }

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
    char *date_str = malloc(sizeof(char) * DATE_SIZE); // Adjust the size as needed
    strftime(date_str, 9, "%d/%m/%y", timeinfo);
    return date_str;
}

void insert_element_to_AD(AD_WORDS_HOLDER *ad_holder,SETS s1 , SETS s2) {
    // Double the size when array is full
    if(ad_holder->count == ad_holder->size){
        realloc_AD(ad_holder, ad_holder->size * 2);
    }

    ad_holder->array_val[ad_holder->count].words_holder.s1 = s1;
    ad_holder->array_val[ad_holder->count].words_holder.s2 = s2;
    ad_holder->array_val[ad_holder->count].last_update_date = malloc(sizeof(char) * DATE_SIZE);


    if(ad_holder->array_val[ad_holder->count].last_update_date == NULL) {
        fperror("Dynamic array last_update_date_malloc ");
    }

    ad_holder->array_val[ad_holder->count].last_update_date = get_current_date();
    ad_holder->count++;

}

// Double the size when array is full , halve the size when array is one-quarterfull
void realloc_AD(AD_WORDS_HOLDER *ad_holder, int size) {
    ad_holder->array_val = (VAL_AD_WORDS_HOLDER*) realloc(ad_holder->array_val, size * sizeof(VAL_AD_WORDS_HOLDER));

    if(ad_holder->array_val == NULL){
        fperror("Realloc AD");
    }

    ad_holder->size = size;
}

void print_AD(const AD_WORDS_HOLDER *ad) {
    printf("count: %d\n", ad->count);
    for (int i = 0; i < ad->count; ++i) {
        puts("SET 1 ");
        puts("Words ");
        print_matrix_char(&((*(ad->array_val + i)).words_holder.s1));
        puts("Encode ");
        // print_matrix_int(&ad->array_val[i].words_holder.s1);
        // with pointer notation
        print_matrix_int(&((*(ad->array_val + i)).words_holder.s1));
        puts("SET 2 ");
        puts("Words ");
        print_matrix_char(&((*(ad->array_val + i)).words_holder.s2));
        puts("Encode ");
        print_matrix_int(&((*(ad->array_val + i)).words_holder.s2));
    }
}

void merge_sort(AD_WORDS_HOLDER ad) {

}

void sort(VAL_AD_WORDS_HOLDER **arr, char **result, int lo, int hi) {
    if(hi <= lo) return;

    /*if(hi < lo + CUTOFF - 1){
        insertion_sort(a, hi);
        return;
    }*

    if(check_if_sorted(a, 16)){
        return;
    }*/

    int mid = lo + (hi - lo) / 2;

    sort(arr, result, lo, mid);
    sort(arr, result, mid + 1, hi);

    merge(arr, result, lo, mid, hi);
}

void merge(VAL_AD_WORDS_HOLDER **arr, char **result, int lo, int mid, int hi) {
    int i, j;

    i = lo;
    j = mid + 1;

    for (int k = lo; k <= hi; k++) {
        printf("lo %d hi = %d k = %d\n", lo, hi, k);
        if (i > mid) {
            strcpy(arr[k]->last_update_date, result[j++]);
        } else if (j > hi) {
            strcpy(arr[k]->last_update_date, result[i++]);
        } else if (strcmp(result[j], result[i]) < 0) {
            //printf("Comparing: %s < %s  %d %d\n", result[j], result[i], strlen(result[j]), strlen(date[k]));
            strcpy(arr[k]->last_update_date, result[j++]);
        } else {
            printf("i %s\n", result[i]);
            printf("i %s\n", arr[k]->last_update_date);
            for (int l = 0, m = 0; l < strlen(arr[k]->last_update_date) + 1; ++l, m++) {
                arr[k]->last_update_date[l] = result[i][m];
            }
            i++;
            //strcpy(arr[k]->last_update_date, result[i++]);
        }
    }

}

