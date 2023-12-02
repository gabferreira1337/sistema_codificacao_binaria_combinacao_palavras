#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "functions_2.h"
#include "functions_1.h"

#define R 5
#define DATE_SIZE 11
#define BUFFER_SIZE 8096

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


    matrix_rnd_char_gen(&set1);
    matrix_rnd_char_gen(&set2);


    char *testDates[] = {
            "2023-11-25",
            "2023-11-24",
            "2022-12-01",
            "2023-01-15",
            "2022-08-10",
    };


    // LL 9)a)
    LL_WORDS_HOLDER *ll = (LL_WORDS_HOLDER*) malloc(sizeof(LL_WORDS_HOLDER));

    insert_word_char(&set1, set1.rowsize, 2);
    insert_word_char(&set2, set2.rowsize, 1);

    insert_node_ll_sorted(ll, &set1, &set2, testDates[0]);
    insert_node_ll_sorted(ll, &set1, &set2, testDates[3]);
    insert_node_ll_sorted(ll, &set1, &set2, testDates[2]);



    encode_matrix_words(&set1, sizes, dic);
    encode_matrix_words(&set2, sizes, dic);

    char *words[] = {
            "ola",
            "olas",
    };

    find_word_ll(ll, words, 2, 0, 2);

    print_ll_words_holder(ll);

    free_ll_words_holder(ll);

   // b)

    /*insert_word_char(&set1, set1.rowsize, 2);
    insert_word_char(&set2, set2.rowsize, 1);

    encode_matrix_words(&set1, sizes, dic);
    encode_matrix_words(&set2, sizes, dic);


    insert_node_ll_index(ll, &set1, &set2, testDates[3], 0);
    insert_node_ll_index(ll, &set1, &set2, testDates[2], 1);
    insert_node_ll_index(ll, &set1, &set2, testDates[1], 2);
    insert_node_ll_index(ll, &set1, &set2, testDates[3], 1);
    insert_node_ll_index(ll, &set1, &set2, testDates[2], 2);

   // insert_node_ll_index(ll, &set1, &set2, testDates[2], 0);

    char *words[] = {
            "ola",
            "olas",
    };

    find_word_ll(ll, words, 2, 0, 4);

   // delete_ll_node_index(ll, 5);
   // delete_ll_node_index(ll, 4);
   // insert_node_ll_index(ll, &set1, &set2, testDates[1], 1);
    print_ll_words_holder(ll);

    free_ll_words_holder(ll);*/


    //
   // insert_element_to_index_AD(arr_din, &set1, &set2, testDates[1], 10);
   // insert_element_to_AD_in_order(arr_din, set1, set2, testDates[1]);

   /* insert_word_char(&set1, set1.rowsize, 2);
    insert_word_char(&set2, set2.rowsize, 1);
*/

   // encode_matrix_words(&set1, sizes, dic);
   /* encode_matrix_words(&set1, sizes, dic);
    encode_matrix_words(&set2, sizes, dic);

    insert_element_to_AD_in_order(arr_din, set1, set2, testDates[1]);
    insert_element_to_AD_in_order(arr_din, set1, set2, testDates[4]);
    insert_element_to_AD_in_order(arr_din, set1, set2, testDates[3]);*/

   /* insert_element_to_AD_in_order(arr_din, set1, set2,testDates[3]);

    insert_element_to_AD_in_order(arr_din, set1, set2, testDates[0]);*/

    //insert_element_to_index_AD(arr_din, val_ad_words_holder, testDates[0], 0);

    //print_AD(arr_din);

    //delete_element_index(arr_din, 1);


   // print_KMP_BinMatches(&set1, index_words_found);

/*
    char *words[] = {
            "ola",
            "olas",
    };

    find_word_ad(arr_din, words, 2, 0, 1);
    print_AD(arr_din);

    free_dynamic_array(arr_din);*/

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


void find_word_ad(AD_WORDS_HOLDER *arr, char **words,int W, int lo, int hi) {
    if(lo < 0 || hi >= arr->count){
        fperror("LO or HI out of bounds");
        //exit(0);
    }
    int *index_set1 = NULL,*index_set2 = NULL;
    for (int i = 0; i < W; ++i) {
        //check if word is valid in ufp6
        if(is_ufp6(words[i]) == -1) continue;
        int dfa[MAX_UFP6][BITS];
        KMP (words[i], dfa);
            for (int j = lo; j <= hi; ++j) {
            // perguntar! e search KMP também
            index_set1 = search_KMP(&arr->array_val[j].words_holder.s1,dfa ,(int) strlen(words[i]));
            index_set2 =  search_KMP(&arr->array_val[j].words_holder.s2,dfa ,(int) strlen(words[i]));
            print_words_found(arr, index_set1, index_set2, j);

            free(index_set1);
            index_set1 = NULL;
            free(index_set2);
            index_set2 = NULL;
        }
    }
}

void print_words_found(AD_WORDS_HOLDER *arr, int *index_set1, int *index_set2, int index_ad) {
    if(index_set1 != NULL){
        printf("Dynamic Array Index -> %d Set1 Match ", index_ad);
        print_found_words_and_ufp6(&arr->array_val[index_ad].words_holder.s1, index_set1);
    }

    if(index_set2 != NULL){
        printf("Dynamic Array Index -> %d Set2 Match, ", index_ad);
        print_found_words_and_ufp6(&arr->array_val[index_ad].words_holder.s2, index_set2);
    }
}

void insert_node_ll_sorted(LL_WORDS_HOLDER *ll, SETS *set1, SETS *set2, char *last_date) {
    //if empty
    NODE_LL_WORDS_HOLDER *pos = bin_search_insert_ll(ll, last_date);
    NODE_LL_WORDS_HOLDER *temp;
    if(ll->ptail == NULL && ll->phead == NULL){
        ll->phead = create_words_holder_node(ll, pos,set1, set2, last_date);
        ll->ptail = ll->phead;
        ll->nnodes++;
        return;
    }

    if(pos->pback == NULL){
        ll->phead = create_words_holder_node(ll, pos, set1, set2, last_date);
        pos->pback = ll->phead;
        ll->phead->pnext = pos;
    }else if(pos->pnext == NULL){
        ll->ptail = create_words_holder_node(ll, pos, set1, set2, last_date);
        pos->pnext = ll->phead;
        ll->ptail->pback = pos;
        ll->ptail->pnext = NULL;
    }else{
       temp = create_words_holder_node(ll, pos, set1, set2, last_date);
        pos->pnext->pback = temp;
        // point the new node to the next to node
        temp->pnext = pos->pnext;
        // point the new node to the back node
        temp->pback = pos;
        // point the pos node to new n
        pos->pnext = temp;
    }

    ll->nnodes++;
}

/*NODE_LL_WORDS_HOLDER *bin_search_insert_ll(LL_WORDS_HOLDER *ll, char *date) {
    int l = 0;
    int h = ll->nnodes - 1;
    int mid;

    NODE_LL_WORDS_HOLDER *current = ll->phead;
    NODE_LL_WORDS_HOLDER *lo = ll->phead;
    NODE_LL_WORDS_HOLDER *hi = NULL;

    while (l <= h) {
        mid = l + (h - l) / 2;

        for (int i = 0; i < mid; ++i) {
            current = current->pnext;
        }

        int cmp = strcmp(current->last_update_date, date);

        if (cmp < 0) {
            // mid pointer to next
            lo = current->pnext;
            l = mid + 1;
        } else if (cmp > 0) {
            hi = current;
            h = mid - 1;
        } else {
            // If elements are equal, modify based on your requirements
            // For example, return lo or hi for insertion after or before the current node
            return lo;
        }
    }

    return lo;
}*/

// even if runtime is O(n), we only do O(log n) total comparisons (one per step of bs).
NODE_LL_WORDS_HOLDER *bin_search_insert_ll(LL_WORDS_HOLDER *ll, char *date) {

    NODE_LL_WORDS_HOLDER *lo = ll->phead;
    NODE_LL_WORDS_HOLDER *hi = ll->ptail;
    NODE_LL_WORDS_HOLDER *mid = NULL;

    do {
        // Find middle
         mid = find_mid_ll(lo, hi);

        // If middle is empty
        if (mid == NULL)
            return NULL;

        int cmp = strcmp(mid->last_update_date, date);

        // If value is present at middle
        if (cmp < 0){
            lo = mid->pnext;
        }else if (cmp > 0){
            hi = mid;
        }else{
            return mid;
        }

    } while (hi == NULL && hi->pnext != lo);


    return mid;
}


NODE_LL_WORDS_HOLDER *create_words_holder_node(LL_WORDS_HOLDER *ll, NODE_LL_WORDS_HOLDER *pos, SETS *set1, SETS *set2, char *last_date) {
    NODE_LL_WORDS_HOLDER *node = (NODE_LL_WORDS_HOLDER *) calloc(1,sizeof(NODE_LL_WORDS_HOLDER)); //New node
    if(node == NULL){
        fperror("Calloc NODE_LL_WORDS_HOLDER");
        // exit(0);
    }

    node->words_holder.s1 = *set1;
    node->words_holder.s2 = *set2;

    node->pnext = NULL;
    node->pback = NULL;
// if is not empty
   /* if (pos != NULL) {
        // If pos is not the head, set the new node's pback to pos->pback
            node->pnext = pos->pnext;
            pos->pnext = node;

        if (pos->pback != NULL) {
            node->pback = pos->pback;
        }

        pos->pback = node;
        node->pnext = pos;

    }
*/
    node->last_update_date = (char*) malloc(sizeof(char) * DATE_SIZE);
    strcpy(node->last_update_date, last_date);

    if(node->last_update_date == NULL){
        fperror("last_update_date malloc");
    }

    return node;
}
/*NODE_LL_WORDS_HOLDER *create_words_holder_node(LL_WORDS_HOLDER *ll, NODE_LL_WORDS_HOLDER *pos, SETS *set1, SETS *set2, char *last_date) {
    NODE_LL_WORDS_HOLDER *node = (NODE_LL_WORDS_HOLDER *)calloc(1, sizeof(NODE_LL_WORDS_HOLDER));
    if (node == NULL) {
        fperror("Calloc NODE_LL_WORDS_HOLDER");
    }

    node->words_holder.s1 = *set1;
    node->words_holder.s2 = *set2;

    node->pnext = NULL;

    if (pos != NULL) {
        // Insert in the middle or at the beginning
        NODE_LL_WORDS_HOLDER *temp = pos->pnext;
        pos->pnext = node;
        node->pnext = temp;1
    } else {
        // Insert at the beginning for an empty list
        node->pnext = ll->phead;
        ll->phead = node;

        // Update ptail if the list was empty
        if (ll->ptail == NULL) {
            ll->ptail = node;
        }
    }

    node->last_update_date = (char *)malloc(sizeof(char) * DATE_SIZE);
    if (node->last_update_date == NULL) {
        fperror("last_update_date malloc");
        // Handle the error appropriately
        free(node);
        return NULL;
    }

    strcpy(node->last_update_date, last_date);

    return node;
}*/


void print_ll_words_holder(LL_WORDS_HOLDER *ll) {
    NODE_LL_WORDS_HOLDER *current = ll->phead;

    for (int i = 0; i < ll->nnodes; ++i) {
        puts("SET1");
        printf("last update: %s\n", current->last_update_date);
        print_matrix_char(&current->words_holder.s1);
        print_matrix_int(&current->words_holder.s1);
        puts("SET2");
        print_matrix_char(&current->words_holder.s2);
        print_matrix_int(&current->words_holder.s2);

        current = current->pnext;
    }
}

void free_ll_words_holder(LL_WORDS_HOLDER *ll) {
        NODE_LL_WORDS_HOLDER *current = ll->ptail;
        NODE_LL_WORDS_HOLDER *prev;

        for (int i = 0; i < ll->nnodes; ++i) {
            free(current->last_update_date);

            prev = current->pback;  // Save the pointer to the previous node
            free(current);
            current = prev;  // Move to the previous node for the next iteration
        }
        free(ll);
}


void insert_node_ll_index(LL_WORDS_HOLDER *ll, SETS *set1, SETS *set2, char *last_date, int index){
    NODE_LL_WORDS_HOLDER *pos = NULL;

    if(ll->ptail == NULL && ll->phead == NULL){
        ll->phead = create_words_holder_node(ll, pos, set1, set2, last_date);
        ll->ptail = ll->phead;
        ll->nnodes++;
        return;
    }

    pos = ll->phead;
    for (int i = 0; i < index - 1 && pos->pnext != NULL; ++i) {
        pos = pos->pnext;
    }


    if (pos->pback != NULL && pos->pnext != NULL) {
        //insert between two nodes
        NODE_LL_WORDS_HOLDER *temp = create_words_holder_node(ll, pos, set1, set2, last_date);
        pos->pnext->pback = temp;
        temp->pnext = pos->pnext;
        temp->pback = pos;
        pos->pnext = temp;
    } else if (pos->pnext == NULL) {
        // Insert to tail
        ll->ptail = create_words_holder_node(ll, pos, set1, set2, last_date);
        pos->pnext = ll->ptail;
        ll->ptail->pback = pos;
        ll->ptail->pnext = NULL;
    } else {
        // Insert at the beginning
        ll->phead = create_words_holder_node(ll, pos, set1, set2, last_date);
        pos->pback = ll->phead;
        ll->phead->pnext = pos;
    }

    ll->nnodes++;
}

/*NODE_LL_WORDS_HOLDER *create_words_holder_node_index(LL_WORDS_HOLDER *ll, NODE_LL_WORDS_HOLDER *pos, SETS *set1, SETS *set2, char *last_date) {
    NODE_LL_WORDS_HOLDER *node = (NODE_LL_WORDS_HOLDER *) calloc(1,sizeof(NODE_LL_WORDS_HOLDER)); //New node
    if(node == NULL){
        fperror("Calloc NODE_LL_WORDS_HOLDER");
        // exit(0);
    }

    node->words_holder.s1 = *set1;
    node->words_holder.s2 = *set2;
    node->pnext = NULL; // initialize the pointers
    node->pback = NULL;

 //if is not empty
    if(pos != NULL) {
        // insert between 2 nodes //
        if (pos->pnext != NULL && pos->pback != NULL) {
            // point the index of node in position  we want to insert to new node added behind
            pos->pnext->pback = node;
            // point the new node to the next to node
            node->pnext = pos->pnext;
            // point the new node to the back node
            node->pback = pos;
            // point the pos node to new n
            pos->pnext = node;
           // insert to tail  //
        } else if(pos->pnext == NULL){
            pos->pnext = node;
            node->pback = pos;
        }else{
            // insert in pos 1 because pos will point to index 0 //
            node->pnext = pos;
            pos->pback = node;
        }
    }*/

   /* node->last_update_date = (char*) malloc(sizeof(char) * DATE_SIZE);
    strcpy(node->last_update_date, last_date);

    if(node->last_update_date == NULL){
        fperror("last_update_date malloc");
    }

    return node;
}*/

NODE_LL_WORDS_HOLDER *find_mid_ll(NODE_LL_WORDS_HOLDER *lo, NODE_LL_WORDS_HOLDER *hi) {
    if (lo == NULL) {
        // If the linked list is empty
        return NULL;
    }

    NODE_LL_WORDS_HOLDER *slow_ptr = lo;
    NODE_LL_WORDS_HOLDER *fast_ptr = lo->pnext;

    while (fast_ptr != NULL && fast_ptr->pnext != NULL) {
        fast_ptr = fast_ptr->pnext->pnext;
        slow_ptr = slow_ptr->pnext;
    }

    return slow_ptr;
}

void delete_ll_node_index(LL_WORDS_HOLDER *ll, int index) {
    if(ll->phead == NULL && ll->ptail == NULL){
       // printf("EMPTY LL\n");
        return;
    }

    if(index >= ll->nnodes){
        printf("INDEX ALREADY REMOVED !!!\n");
        return;
    }

    NODE_LL_WORDS_HOLDER *pos = NULL;
    pos = ll->phead;

    for (int i = 0; i < index && pos != NULL; ++i) {
        pos = pos->pnext;
    }

    if (pos->pback != NULL && pos->pnext != NULL) {
        // Remove between two nodes
        pos->pback->pnext = pos->pnext;
        pos->pnext->pback = pos->pback;
        // Remove node in tail (last node)
    } else if (pos->pnext == NULL) {
        ll->ptail = pos->pback;
        pos->pback->pnext = NULL;
    } else {
        // Remove in head (first one)
        ll->phead = pos->pnext;
        pos->pnext->pback = NULL;
    }
    free(pos->last_update_date);
    free(pos);

    ll->nnodes--;

    return;
}

void find_word_ll(LL_WORDS_HOLDER *ll, char **words, int W, int lo, int hi) {
    if(lo < 0 || hi >= ll->nnodes){
        fperror("LO or HI out of bounds");
        //exit(0);
    }

    int *index_set1 = NULL,*index_set2 = NULL;
    NODE_LL_WORDS_HOLDER *lo_node;
    lo_node = ll->phead;

    for (int i = 0; i < lo; ++i) {
        lo_node= lo_node->pnext;
    }

    for (int i = 0; i < W; ++i) {
        //check if word is valid in ufp6
        if(is_ufp6(words[i]) == -1) continue;
        int dfa[MAX_UFP6][BITS];
        KMP (words[i], dfa);
        NODE_LL_WORDS_HOLDER *current = lo_node;
        for (int j = lo; j <= hi && current->pnext !=NULL; ++j) {
            index_set1 = search_KMP(&current->words_holder.s1,dfa ,(int) strlen(words[i]));
            index_set2 =  search_KMP(&current->words_holder.s2,dfa ,(int) strlen(words[i]));
            print_words_found_ll(current, index_set1, index_set2, j);
            //write_set_to_txt(&current->words_holder.s1,"teste_find.txt");
            //write_both_sets_to_txt(&current->words_holder.s1, &current->words_holder.s2, "/Users/gabrielferreira/Desktop/projeto_aed1_lp1/teste_find.txt");
            write_words_found_to_txt(current, index_set1, index_set2,"/Users/gabrielferreira/Desktop/projeto_aed1_lp1/teste_find_1.txt");

            free(index_set1);
            index_set1 = NULL;
            free(index_set2);
            index_set2 = NULL;
            current = current->pnext;
        }
    }
}

void print_words_found_ll(NODE_LL_WORDS_HOLDER *current, int *index_set1, int *index_set2, int j) {
    if(index_set1 != NULL){
        printf("LL NODE -> %d Set1 Match ", j);
        print_found_words_and_ufp6(&current->words_holder.s1, index_set1);
    }

    if(index_set2 != NULL){
        printf("LL NODE -> %d Set2 Match, ", j);
        print_found_words_and_ufp6(&current->words_holder.s2, index_set2);
    }
}

int write_set_to_txt(const SETS *set, char *filename) {
    FILE *fp = fopen(filename, "a+");

    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "Words set\n");  // Corrected format specifier
    for (int i = 0; i < set->rowsize; i++) {
        //fwrite(set->matrix[i], sizeof(char), set->arr_word_size[i], fp);  // Write each row
        fprintf(fp, " %s",  set->matrix[i]);
        fputc('\n', fp);
    }

    fclose(fp);

    return 0;
}

int write_both_sets_to_txt(const SETS *s1, const SETS *s2, char *filename) {
    write_set_to_txt(s1, filename);
    write_set_to_txt(s2, filename);
    return 0;
}

int write_words_found_to_txt(NODE_LL_WORDS_HOLDER *current,const int *index_set1,const int *index_set2, char *filename) {
    FILE *fp = fopen(filename, "a+");

    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "Words set 1\n");  // Corrected format specifier

    if(index_set1 != NULL){
        for (int i = 1; i <= *index_set1; i++) {
            //fwrite(set->matrix[i], sizeof(char), set->arr_word_size[i], fp);  // Write each row
            fprintf(fp, " %s",  current->words_holder.s1.matrix[i]);
            fputc('\n', fp);
        }
    }


    fprintf(fp, "Words set 2\n");  // Corrected format specifier
    if(index_set2 != NULL){
        for (int i = 1; i <= *index_set2; i++) {
            //fwrite(set->matrix[i], sizeof(char), set->arr_word_size[i], fp);  // Write each row
            fprintf(fp, " %s",  current->words_holder.s2.matrix[i]);
            fputc('\n', fp);
        }
    }


    fclose(fp);
    return 0;
}

/*
int write_set_to_txt(const SETS *set, char *filename) {
    int fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    write(fd, "Words set\n", sizeof("Words set\n") - 1);

    for (int i = 0; i < set->rowsize; i++) {
        dprintf(fd, " %s\n", set->matrix[i]);
    }

    close(fd);

    return 0;
}*/