#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "functions_2.h"
#include "functions_1.h"


#define R 5
#define DATE_SIZE 9

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

    //VAL_AD_WORDS_HOLDER *val_ad_words_holder = NULL;

   // insert_to_VAL_AD_WORDS_HOLDER(val_ad_words_holder, &set1, &set2);


    //encode_matrix_words(&set1, sizes, dic);
    matrix_rnd_char_gen(&set1);
    matrix_rnd_char_gen(&set2);



    char *testDates[] = {
            "2023-11-25",
            "2023-11-24",
            "2022-12-01",
            "2023-01-15",
            "2022-08-10",
    };

   // insert_element_to_index_AD(arr_din, &set1, &set2, testDates[1], 10);
   // insert_element_to_AD_in_order(arr_din, set1, set2, testDates[1]);

    insert_word_char(&set1, set1.rowsize, 2);
    insert_word_char(&set2, set2.rowsize, 1);


   // encode_matrix_words(&set1, sizes, dic);

    insert_element_to_AD_in_order(arr_din, set1, set2, testDates[1]);
    insert_element_to_AD_in_order(arr_din, set1, set2, testDates[4]);
    insert_element_to_AD_in_order(arr_din, set1, set2, testDates[3]);


   /* insert_element_to_AD_in_order(arr_din, set1, set2,testDates[3]);

    insert_element_to_AD_in_order(arr_din, set1, set2, testDates[0]);*/

    //insert_element_to_index_AD(arr_din, val_ad_words_holder, testDates[0], 0);

    print_AD(arr_din);

    delete_element_index(arr_din, 1);


  //  print_KMP_BinMatches(&set1, index_words_found);


    char *words[] = {
            "ola",
            "olas",
    };

    find_word_ad(arr_din, words, 2, 0, 1);
    print_AD(arr_din);

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
    for (int i = 0; i < arr->count; ++i) {
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

void insert_element_to_AD_in_order(AD_WORDS_HOLDER *ad_holder, SETS s1, SETS s2, char *last_date) {
    // Double the size when array is full
    if (ad_holder->count == ad_holder->size) {
        realloc_AD(ad_holder, ad_holder->size * 2);
    }

    int pos = bin_search_insert_pos(ad_holder, last_date);

    for (int i = ad_holder->count; i > pos; i--) {
        ad_holder->array_val[i] = ad_holder->array_val[i - 1];
    }

    ad_holder->array_val[pos].words_holder.s1 = s1;
    ad_holder->array_val[pos].words_holder.s2 = s2;

    ad_holder->array_val[pos].last_update_date = malloc(sizeof(char) * DATE_SIZE);

    if (ad_holder->array_val[pos].last_update_date == NULL) {
        fperror("Dynamic array last_update_date_malloc ");
    }

    strcpy(ad_holder->array_val[pos].last_update_date, last_date);

    ad_holder->count++;
}


// Double the size when array is full , halve the size when array is one-quarterfull
void realloc_AD(AD_WORDS_HOLDER *ad_holder, int size) {
    ad_holder->array_val = (VAL_AD_WORDS_HOLDER*) realloc(ad_holder->array_val, size * sizeof(VAL_AD_WORDS_HOLDER));

    if (ad_holder->array_val == NULL) {
        fperror("Realloc AD");
    }

    ad_holder->size = size;
}

void print_AD(const AD_WORDS_HOLDER *ad) {
    printf("size: %d\n", ad->size);
    //printf("count: %d\n", ad->count);
    for (int i = 0; i < ad->count; ++i) {
        printf("last update date: %s\n", ad->array_val[i].last_update_date);
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


void sort(VAL_AD_WORDS_HOLDER *arr, char **result, int lo, int hi) {
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

void merge(VAL_AD_WORDS_HOLDER *arr, char **result, int lo, int mid, int hi) {
    int i, j;

    for (int l = lo; l <= hi ; ++l) {
        memcpy(result[l], arr[l].last_update_date,DATE_SIZE);
    }

    i = lo;
    j = mid + 1;
    //printf("asalcnççpç%s\n", arr[0].last_update_date);
    //printf("asalcnççpç1%s\n", arr[1].last_update_date);

    for (int k = lo; k <= hi; k++) {
      //  printf("lo %d hi = %d k = %d\n", lo, hi, k);

        if (i > mid && j < hi  ) {
           // memcpy(arr[k]->last_update_date, result[j++], DATE_SIZE);
            strcpy(arr[k].last_update_date, result[j++]);

            //printf("Updated last_update_date: %s\n", arr[k].last_update_date);
        } else if (j > hi && i < mid ) {
           // memcpy(arr[k]->last_update_date, result[i++], DATE_SIZE);
            strcpy(arr[k].last_update_date, result[i++]);

           // printf("Updated last_update_date: %s\n", arr[k].last_update_date);
        } else if (i <= mid && j <= hi) {
            if (strcmp(result[j], result[i]) < 0) {
                // memcpy(arr[k]->last_update_date, result[j++], DATE_SIZE);
                strcpy(arr[k].last_update_date, result[j++]);

                //printf("Updated last_update_date: %s\n", arr[k].last_update_date);
            } else {
                //memcpy(arr[k]->last_update_date, result[i++], DATE_SIZE);
                strcpy(arr[k].last_update_date, result[i++]);
                //printf("Updated last_update_date: %s\n", arr[k].last_update_date);
            }
        }
       // printf("Updated last_update_date: %s\n", arr[k].last_update_date);
    }
}


int bin_search_insert_pos(const AD_WORDS_HOLDER *arr_din, char *date) {
    int lo = 0;
    int hi = arr_din->count - 1;
    int mid;

    while(lo <= hi){
        mid = lo + (hi - lo) / 2;

        int cmp = strcmp(arr_din->array_val[mid].last_update_date, date);

        if (cmp < 0) {
            lo = mid + 1;
        } else if (cmp > 0) {
            hi = mid - 1;
        } else {
            //If elements are equal, insert at the current position
            return mid;
        }
    }
    // return insert position
    return lo;
}


/*void insert_element_to_index_AD(AD_WORDS_HOLDER *ad_holder, VAL_AD_WORDS_HOLDER *val_words_holder ,char*last_date, int index) {
    // Double the size when array is full
    if (ad_holder->count == ad_holder->size) {
        realloc_AD(ad_holder, ad_holder->size * 2);
    }

    for (int i = ad_holder->count; i > index; i--) {
        ad_holder->array_val[i] = ad_holder->array_val[i - 1];
    }

    ad_holder->array_val[index] = *val_words_holder;

    ad_holder->array_val[index].last_update_date = malloc(sizeof(char) * DATE_SIZE);

    if (ad_holder->array_val[index].last_update_date == NULL) {
        fperror("Dynamic array last_update_date_malloc ");
    }

    strcpy(ad_holder->array_val[index].last_update_date, last_date);

    ad_holder->count++;
}
*/

void insert_to_VAL_AD_WORDS_HOLDER(VAL_AD_WORDS_HOLDER *val_ad_words_holder, SETS *set1, SETS *set2) {
    WORDS_HOLDER words_holder;
    words_holder.s1 = *(set1);
    words_holder.s2 = *(set2);

    val_ad_words_holder = malloc(sizeof(VAL_AD_WORDS_HOLDER));

    if(val_ad_words_holder == NULL){
        fperror("val_ad_words_holder malloc in insert_to_VAL_AD_WORDS_HOLDER");
    }

    val_ad_words_holder->words_holder = words_holder;
}

void insert_element_to_index_AD(AD_WORDS_HOLDER *ad_holder, SETS *set1, SETS *set2,char*last_date, int index) {
    // Double the size when array is full or when want to insert in index equal to ad size
    if (ad_holder->count == ad_holder->size) {
        realloc_AD(ad_holder, ad_holder->size * 2);
    }else if(index >= ad_holder->size){
        realloc_AD(ad_holder, index * 2);
    }

    for (int i = ad_holder->count; i > index; i--) {
        ad_holder->array_val[i] = ad_holder->array_val[i - 1];
    }

    ad_holder->array_val[index].words_holder.s1 = *set1;
    ad_holder->array_val[index].words_holder.s2 = *set2;

    ad_holder->array_val[index].last_update_date = malloc(sizeof(char) * DATE_SIZE);

    if (ad_holder->array_val[index].last_update_date == NULL) {
        fperror("Dynamic array last_update_date_malloc ");
    }

    strcpy(ad_holder->array_val[index].last_update_date, last_date);

    ad_holder->count++;
}

void delete_element_index(AD_WORDS_HOLDER *ad, int index) {
    //halve the size when array is one-quarterfull
    if (ad->count == (1/4 * ad->size)){
        realloc_AD(ad, ad->size / 2);
    }

    for (int i = index; i < ad->count; ++i) {
       ad->array_val[i] = ad->array_val[i + 1];
    }

    free(ad->array_val[ad->count].last_update_date);
    // ask 0 filled

    ad->count--;
}


// recursive?
void find_word_ad(AD_WORDS_HOLDER *arr, char **words,int W, int lo, int hi) {
    if(lo < 0 || hi >= arr->count){
        fperror("LO or HI out of bounds");
        //exit(0);
    }
    int *index_set1 = NULL,*index_set2 = NULL;
    for (int i = 0; i < W; ++i) {
        int dfa[MAX_UFP6][BITS + 1];
        KMP (words[i], dfa);
            for (int j = lo; j <= hi; ++j) {
            // perguntar! e search KMP também
            index_set1 = search_KMP(&arr->array_val[j].words_holder.s1,dfa , strlen(words[i]));
            index_set2 =  search_KMP(&arr->array_val[j].words_holder.s2,dfa ,(int) strlen(words[i]));
            find_Word(&arr->array_val[j].words_holder.s1,);
            print_words_found(arr, index_set1, index_set2, j);
        }
        free(index_set1);
        index_set1 = NULL;
        free(index_set2);
        index_set2 = NULL;
    }
}

void print_words_found(AD_WORDS_HOLDER *arr, int *index_set1, int *index_set2, int index_ad) {
    printf("SET1 - word found in index %d \n", index_ad);
    for (int j = 1; j < (*index_set1); j++) {

        printf("%s\n",arr->array_val[index_ad].words_holder.s1.matrix[index_set1[j]]);
    }

    printf("SET2 - word found\n");
    for (int j = 1; j < *index_set2; ++j) {
        printf("%s\n",arr->array_val[index_ad].words_holder.s2.matrix[index_set1[j]]);
    }

}


