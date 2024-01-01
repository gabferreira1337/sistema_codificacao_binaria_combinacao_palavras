#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "functions_2.h"
#include "functions_1.h"

#define DATE_SIZE 11



AD_WORDS_HOLDER *dynamic_array_init(int size) {
    if(size <= 0) fperror("Invalid size");

    AD_WORDS_HOLDER *arr = (AD_WORDS_HOLDER*) calloc(1,sizeof(AD_WORDS_HOLDER));
    if(arr == NULL) {
        fperror("Dynamic_array_init array_val calloc");
    }

    arr->size = size;
    arr->array_val = (VAL_AD_WORDS_HOLDER*) calloc(size,sizeof(VAL_AD_WORDS_HOLDER));
    if(arr->array_val == NULL) {
        fperror("Dynamic_array_init array_val calloc");
    }
    return arr;
}


void free_dynamic_array(AD_WORDS_HOLDER *arr) {
    for (int i = 0; i < arr->count; ++i) {
        free(arr->array_val[i].last_update_date);
        arr->array_val[i].last_update_date = NULL;
        ///free both sets of each index
        freemem_set(&arr->array_val[i].words_holder.s1);
        freemem_set(&arr->array_val[i].words_holder.s2);
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

    /// Format date
    char *date_str = malloc(sizeof(char) * DATE_SIZE);
    strftime(date_str, DATE_SIZE, "%d/%m/%y", timeinfo);
    return date_str;
}

/**
 * @paragraph Insert element to AD in chronological order by date ASC
 * @paragraph function uses binary search to search for the position in AD where
 * new element will be inserted and adjusts the position of the other elements in AD before inserting,
 * when array is full double the size of Dynamic Array
 * @paragraph This insertion function has a time complexity of O(2N +Dlog(N)) , Extra space O(1) (inplace)
 * Shift elements O(N) , realloc O(N) , binary_search function O(Dlog(N))
 * D = size of date N = num of elements in Dynamic array
 */
void insert_element_to_AD_in_order(AD_WORDS_HOLDER *ad_holder,const SETS *s1,const SETS *s2,const char *last_date) {
    ///Check if date is valid
    if(!is_valid_date(last_date)) fperror("Invalid date");
    /// Double the size when array is full
    if (ad_holder->count == ad_holder->size) {
        realloc_AD(ad_holder, ad_holder->size * 2);
    }
    ///Search for position to insert in Dynamic array using Bsearch
    int pos = bin_search_insert_pos(ad_holder, last_date);

    insert_element_to_index_AD(ad_holder, s1, s2, last_date, pos);
}


/// Double the size when array is full while inserting in ad, halve the size when array is one-quarterfull while removing element from ad
void realloc_AD(AD_WORDS_HOLDER *ad_holder, int size) {
    ad_holder->array_val = (VAL_AD_WORDS_HOLDER*) realloc(ad_holder->array_val, size * sizeof(VAL_AD_WORDS_HOLDER));
    if (ad_holder->array_val == NULL) {
        fperror("Realloc AD");
    }
    ad_holder->size = size;
}

void print_AD(const AD_WORDS_HOLDER *ad) {
    //printf("size: %d\n", ad->size);
    //printf("count: %d\n", ad->count);
    for (int i = 0; i < ad->count; ++i) {
        printf("\nIndex %d\n", i);
        printf("last update date: %s\n", &(*(ad->array_val + i)->last_update_date));
        puts("SET 1 ");
        print_matrix_char(&((*(ad->array_val + i)).words_holder.s1));
        // print_matrix_int(&ad->array_val[i].words_holder.s1);
        // with pointer notation
        print_matrix_int(&((*(ad->array_val + i)).words_holder.s1));
        puts("SET 2 ");
        print_matrix_char(&((*(ad->array_val + i)).words_holder.s2));
        print_matrix_int(&((*(ad->array_val + i)).words_holder.s2));
    }
}
int compare_dates(const char *date1, const char *date2) {
    struct tm tm_date1, tm_date2;
    /// Parse both dates
    if (strptime(date1, "%Y-%m-%d", &tm_date1) == NULL ||
        strptime(date2, "%Y-%m-%d", &tm_date2) == NULL) {
        fprintf(stderr, "Failed to parse date strings\n");
        return 0;
    }

    if (tm_date1.tm_year < tm_date2.tm_year) {
        return -1;
    } else if (tm_date1.tm_year > tm_date2.tm_year) {
        return 1;
    } else {
        /// Years are equal, compare months
        if (tm_date1.tm_mon < tm_date2.tm_mon) {
            return -1;
        } else if (tm_date1.tm_mon > tm_date2.tm_mon) {
            return 1;
        } else {
            /// Months are equal, compare days of the month
            if (tm_date1.tm_mday < tm_date2.tm_mday) {
                return -1;
            } else if (tm_date1.tm_mday > tm_date2.tm_mday) {
                return 1;
            } else {
                /// Dates are equal
                return 0;
            }
        }
    }
}

/**
 * @paragraph binary search to search for the position in AD where
 * new element will be inserted
 * @paragraph binary_search O(log(N)) , strcmp O(D), Time complexity O(Dlog(N)) , Extra Space O(1) (inplace)
 */
int bin_search_insert_pos(const AD_WORDS_HOLDER *arr_din,const char *date) {
    int lo = 0;
    int hi = arr_din->count - 1;
    int mid = 0;

    while(lo <= hi){
        mid = lo + (hi - lo) / 2;

        int cmp = strcmp(arr_din->array_val[mid].last_update_date, date);

        if (cmp < 0) {
            lo = mid + 1;
        } else if (cmp > 0) {
            hi = mid - 1;
        } else {
            ///If elements are equal, insert at the current position
            return mid;
        }
    }
    /// return insert position
    return lo;
}


/**
 * @paragraph Insert data to VAL_AD_WORDS_HOLDER
 */
void insert_to_VAL_AD_WORDS_HOLDER(VAL_AD_WORDS_HOLDER *val_ad_words_holder,const SETS *set1,const SETS *set2,const char *last_date) {
    val_ad_words_holder->words_holder.s1 = *set1;
    val_ad_words_holder->words_holder.s2 = *set2;

    val_ad_words_holder->last_update_date = malloc(sizeof(char) * DATE_SIZE);

    if (val_ad_words_holder->last_update_date == NULL) {
        fperror("Val_ad_words-holder last_update_date_malloc in insert_to_VAL_AD_WORDS_HOLDER");
    }

    strcpy(val_ad_words_holder->last_update_date, last_date);
}
/**
 * @paragraph Insert element to AD in given index
 * @paragraph This function shifts elements to insert new element at the given index and fill VAl_AD_WORDS_HOLDER
 * with the values passed to the function
 * @paragraph This insertion function has a time complexity of O(2N + D)) , Extra space O(1) (inplace)
 * Shift elements O(N) , realloc O(N) , insertion O(1), strcpy date O(D)
 * D = date size N = size of elements in dynamic array
 */
void insert_element_to_index_AD(AD_WORDS_HOLDER *ad_holder,const SETS *set1,const SETS *set2,const char *last_date, int index) {
    ///Check if date is valid
    if(!is_valid_date(last_date)) fperror("Invalid date");
    /// Double the size when array is full or when index to be inserted is equal
    /// or greater than ad_holder size
    if (ad_holder->count == ad_holder->size) {
        realloc_AD(ad_holder, ad_holder->size * 2);
    }else if(index >= ad_holder->size){
        realloc_AD(ad_holder, index * 2);
    }
    ///Shift elements from count until given index to insert new element
    for (int i = ad_holder->count; i > index; i--) {
        ///Copy from next to prev element
        ad_holder->array_val[i] = ad_holder->array_val[i - 1];
    }
    ///Insert element in Dynamic Array
    insert_to_VAL_AD_WORDS_HOLDER(&ad_holder->array_val[index], set1,set2,last_date);
    ad_holder->count++;
}


void delete_element_index(AD_WORDS_HOLDER *ad, int index) {
    if(ad->count == 0){
        printf("Dynamic Array Empty\n");
        return;
    }
    ///Halve the size when array is one-quarter full
    if (ad->count == (1/4 * ad->size)){
        realloc_AD(ad, ad->size / 2);
    }
    ///Shift elements from next to previous starting from index
    for (int i = index; i < ad->count; ++i) {
       ad->array_val[i] = ad->array_val[i + 1];
    }
    ///Free Memory of last element
    if (ad->array_val[ad->count - 1].last_update_date != NULL) {
        free(ad->array_val[ad->count - 1].last_update_date);
        freemem_set(&ad->array_val[ad->count - 1].words_holder.s1);
        freemem_set(&ad->array_val[ad->count - 1].words_holder.s2);
    }
    ad->count--;
}

int is_valid_date(const char *date_str) {
    struct tm tm_date;
    ///Using strptime function to check if date_str is valid
    ///strptime returns pointer to NULL if date can't be parsed (wrong format)
    if (strptime(date_str, "%Y-%m-%d", &tm_date) == NULL || tm_date.tm_year < 0 || tm_date.tm_mon < 0 || tm_date.tm_yday < 0) {
        return 0;
    }
    /// Valid date
    return 1;
}

int *search_word(const SETS *set,const char *word){
    int *arr_index = (int*) calloc(set->rowsize,sizeof(int));
    if(arr_index == NULL){
        fperror("Calloc arr_index in search_KMP");
    }
    ///Start in index 1 to store in index 0 the count of words found in set
    int l = 1;
    for (int i = 0; i < set->rowsize; ++i) {
        if(strcmp(*(set->matrix + i), word) == 0){
            arr_index[l++] = i;
        }
    }
    ///Store in pos 0 of array the count of words found in set
    *(arr_index + 0) = l - 1;
    ///if found words return pointer to array
    if(*(arr_index + 0) != 0)
        return arr_index;
    return NULL;
}


void find_words_ad(const AD_WORDS_HOLDER *arr, const char **words, int W, int start_index, int end_index, const char *fn, bool flag) {
    if(start_index < 0 || end_index >= arr->count){
        fperror("LO or HI out of bounds");
    }
    int *index_set1 = NULL,*index_set2 = NULL;
    for (int i = 0; i < W; ++i) {
        ///Calculate length of string
        int word_length =(int) strlen(words[i]);
        ///Check if word is valid in UFP6
        if(is_ufp6(words[i], word_length) == -1){
            printf("Word %s not valid in UFP6\n", words[i]);
            continue;
        }
        for (int j = start_index; j <= end_index; ++j) {
            index_set1 = search_word(&arr->array_val[j].words_holder.s1, words[i]);
            index_set2 =  search_word(&arr->array_val[j].words_holder.s2, words[i]);
            if(index_set1 == NULL && index_set2 == NULL){
                printf("Word %s not found in index %d\n\n", words[i], j);
            }else{
                print_words_found(arr, index_set1, index_set2, j);
                ///If flag set to 1 output found words and UFP6 to a txt file
                if(flag == 1 && fn != NULL){
                    write_words_found_in_da_to_txt(&arr->array_val[j], index_set1, index_set2, fn, j);
                }
            }
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

void insert_node_ll_sorted(LL_WORDS_HOLDER *ll,const SETS *set1,const SETS *set2,const char *last_date) {
   if(!is_valid_date(last_date)){
       printf("Date %s", last_date);
       fperror("Date not valid in insert_node_ll_sorted");
   }
    ///If LL is empty
    if(ll->ptail == NULL && ll->phead == NULL){
        ///Add to head
        ll->phead = create_words_holder_node(set1, set2, last_date);
        ///Point ll->ptail to ll->phead
        ll->ptail = ll->phead;
        ll->nnodes++;
        return;
    }
    ///Search for position using binary search to insert in chronological order
    NODE_LL_WORDS_HOLDER *curr = ll->phead;;
    NODE_LL_WORDS_HOLDER *prev = NULL;
    ///Find current and prev position to add node in chronological order DESC
    while(curr != NULL && strcmp(curr->last_update_date, last_date) > 0){
        prev = curr;
        curr = curr->pnext;
    }
    insert_to_ll_given_pointers_node(ll, set1, set2, last_date, curr, prev);
}

void insert_to_ll_given_pointers_node(LL_WORDS_HOLDER *ll, const SETS *set1, const SETS *set2, const char *last_date, NODE_LL_WORDS_HOLDER *curr, NODE_LL_WORDS_HOLDER *prev){
    NODE_LL_WORDS_HOLDER *newn = create_words_holder_node(set1, set2, last_date);
    ///Insert to tail
    if (curr == NULL && prev != NULL) {
        ///point prev node to new node
        prev->pnext = newn;
        ///point ptail to new node
        ll->ptail = newn;
        ///point new node to previous node
        newn->pback = prev;
        ///point new node to NULL
        newn->pnext = NULL;
        ///Add to head
    } else if (curr->pback == NULL && prev == NULL){
        ///point head to new node
        ll->phead = newn;
        ///point current node to new node
        curr->pback = newn;
        ///point new node to current
        newn->pnext = curr;
        ///point new node to NULL
        newn->pback = NULL;
        ///Add between nodes
    } else {
        ///point previous node to new node
        prev->pnext= newn;
        ///point new node to current
        newn->pnext = curr;
        ///point current node to new node
        curr->pback = newn;
        ///point new node to pos node
        newn->pback = prev;
    }
    ll->nnodes++;
}


NODE_LL_WORDS_HOLDER *create_words_holder_node(const SETS *set1,const SETS *set2,const char *last_date) {
    /// Calloc to initialize to 0 or NULL vals in struct
    NODE_LL_WORDS_HOLDER *node = (NODE_LL_WORDS_HOLDER *) calloc(1,sizeof(NODE_LL_WORDS_HOLDER));
    if(node == NULL){
        fperror("Calloc NODE_LL_WORDS_HOLDER in create_words_holder_node");
    }
    ///Copy to node
    node->words_holder.s1 = *set1;
    node->words_holder.s2 = *set2;
    node->last_update_date = (char*) malloc(sizeof(char) * DATE_SIZE);
    if(node->last_update_date == NULL){
        fperror("last_update_date malloc in create_words_holder_node");
    }
    strcpy(node->last_update_date, last_date);

    return node;
}

void print_ll_words_holder(LL_WORDS_HOLDER *ll) {
    NODE_LL_WORDS_HOLDER *current = ll->phead;

    for (int i = 0; i < ll->nnodes; ++i) {
        printf("NODE: %d\n", i);
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

            prev = current->pback;  /// store pointer to the previous node
            free(current);
            current = prev;  /// Move to the previous node for the next iteration
        }
        free(ll);
}


void insert_node_ll_index(LL_WORDS_HOLDER *ll,const SETS *set1,const SETS *set2,const char *last_date, int index){
    if(index > ll->nnodes || index < 0){
        fperror("Index out of bounds in insert_node_ll_index");
    }
    if(!is_valid_date(last_date)){
        printf("Date %s", last_date);
        fperror("Date not valid in insert_node_ll_sorted");
    }
    ///If LL is empty
    if(ll->ptail == NULL && ll->phead == NULL){
        ll->phead = create_words_holder_node(set1, set2, last_date);
        ll->ptail = ll->phead;
        ll->nnodes++;
        return;
    }
    NODE_LL_WORDS_HOLDER *curr = NULL;
    NODE_LL_WORDS_HOLDER *prev = NULL;
    if(index != ll->nnodes){
        curr = ll->phead;
        for (int i = 0; i < index && curr != NULL; ++i) {
            prev = curr;
            curr = curr->pnext;
        }
        ///Use pointer to last node in LL_WORDS_HOLDER so don't need to
        ///traverse linked list
    }else{
        curr = NULL;
        prev = ll->ptail;
    }
    insert_to_ll_given_pointers_node(ll, set1, set2, last_date,curr, prev);
}


/**
 * Find midpoint of Linked List using fast_ptr and slow_ptr, fast_ptr advances two nodes at a time
 * and slow_ptr advances one node at a time so divides the search space in half at each step
 * O(N)
 */
NODE_LL_WORDS_HOLDER *find_mid_ll(NODE_LL_WORDS_HOLDER *lo, NODE_LL_WORDS_HOLDER *hi) {
    // If the linked list is empty
    if (lo == NULL) {
        return NULL;
    }

    NODE_LL_WORDS_HOLDER *slow_ptr = lo;
    NODE_LL_WORDS_HOLDER *fast_ptr = lo->pnext;
    //fast_ptr == NULL , and fast_ptr->pnext == NULL indicates that fast_ptr is the last node
    while (fast_ptr != NULL && fast_ptr->pnext != NULL) {
        fast_ptr = fast_ptr->pnext->pnext;
        slow_ptr = slow_ptr->pnext;
    }
    return slow_ptr;
}

void delete_ll_node_index(LL_WORDS_HOLDER *ll, int index) {
    if (ll->phead == NULL && ll->ptail == NULL){
        printf("EMPTY LL\n");
        return;
    }
    if (index >= ll->nnodes){
        printf("INDEX ALREADY REMOVED !!!\n");
        return;
    }

    NODE_LL_WORDS_HOLDER *pos = NULL;
    if (index != ll->nnodes){
        pos = ll->phead;
        ///Traverse LL to find node at given index to be deleted
        for (int i = 0; i < index && pos != NULL; ++i) {
            pos = pos->pnext;
        }
        ///Use pointer to last node in LL_WORDS_HOLDER so don't need to
        ///traverse linked list when deleting last node
    }else {
        pos = ll->ptail;
    }

    /// Remove between two nodes
    if (pos->pback != NULL && pos->pnext != NULL) {
        ///Point previous node to the next node of node to be deleted
        pos->pback->pnext = pos->pnext;
        ///Point next node of node to be deleted to prev node pointed also by node to be deleted
        pos->pnext->pback = pos->pback;
        /// Remove node in tail
    } else if (pos->pnext == NULL) {
        ///Point tail to prev node
        ll->ptail = pos->pback;
        ///Point prev node to NULL
        pos->pback->pnext = NULL;
        /// Remove node in head
    } else {
        ///Point head to next node
        ll->phead = pos->pnext;
        ///Point next node to NULL
        pos->pnext->pback = NULL;
    }

    free(pos->last_update_date);
    free(pos);
    ll->nnodes--;
}

/*
void find_word_ll(const LL_WORDS_HOLDER *ll, char **words, int W, int start_index_node, int end_index_node, const char *fn, bool flag) {
    ///Check if out of bounds
    if(start_index_node < 0 || end_index_node >= ll->nnodes){
        fperror("LO or HI out of bounds");
    }

    int *index_set1 = NULL,*index_set2 = NULL;
    NODE_LL_WORDS_HOLDER *lo_node;
    lo_node = ll->phead;

    for (int i = 0; i < start_index_node; ++i) {
        lo_node= lo_node->pnext;
    }

    for (int i = 0; i < W; ++i) {
        int word_length = (int) strlen(words[i]);
        //check if word is valid in ufp6
        if(is_ufp6(words[i], word_length) == -1) continue;
        int dfa[MAX_UFP6][BITS - 1];
        KMP (words[i], dfa);
        NODE_LL_WORDS_HOLDER *current = lo_node;
        for (int j = start_index_node; j <= end_index_node && current->pnext !=NULL; ++j) {
            index_set1 = search_KMP(&current->words_holder.s1,dfa ,word_length);
            index_set2 =  search_KMP(&current->words_holder.s2,dfa ,word_length);
            print_words_found_ll(current, index_set1, index_set2, j);
            if(flag == 1){
                write_words_found_in_ll_to_txt(current, index_set1, index_set2, fn, j);
            }
            free(index_set1);
            index_set1 = NULL;
            free(index_set2);
            index_set2 = NULL;
            current = current->pnext;
        }
    }
}*/

void find_words_ll(const LL_WORDS_HOLDER *ll, const char **words, const char *fn, int W, int start_index_node, int end_index_node, bool flag) {
    ///Check if out of bounds
    if(start_index_node < 0 || end_index_node >= ll->nnodes){
        fperror("LO or HI out of bounds");
    }

    int *arr_index_set1 = NULL,*arr_index_set2 = NULL;
    NODE_LL_WORDS_HOLDER *start_node = NULL;
    ///If only want to find in last node given words
   if (start_index_node != ll->nnodes - 1) {
       start_node = ll->phead;
       ///Get pointer to starting node given index
       for (int i = 0; i < start_index_node; ++i) {
           start_node = start_node->pnext;
       }
   }else{
       ///Use pointer to last node in LL_WORDS_HOLDER so don't need to
       ///traverse linked list to get pointer to last node
       start_node = ll->ptail;
   }

    for (int i = 0; i < W; ++i) {
        ///Calculate length of string
        int word_length =(int) strlen(words[i]);
        ///Check if word is valid in UFP6
        if(is_ufp6(words[i], word_length) == -1){
            printf("Word %s not valid in UFP6\n", words[i]);
            continue;
        }
        NODE_LL_WORDS_HOLDER *curr = start_node;
        for (int j = start_index_node; j <= end_index_node && curr != NULL; ++j) {
            ///Search for words in each set and store indexes in
            arr_index_set1 = search_word(&curr->words_holder.s1, words[i]);
            arr_index_set2 =  search_word(&curr->words_holder.s2, words[i]);
            if (arr_index_set1 == NULL && arr_index_set2 == NULL){
                printf("Word %s not found in node %d\n\n", words[i], j);
            }else {
                print_words_found_ll(curr, arr_index_set1, arr_index_set2, j);
                ///If flag set to 1 output found words and UFP6 to a txt file
                if (flag == 1 && fn != NULL){
                    write_words_found_in_ll_to_txt(curr, arr_index_set1, arr_index_set2, fn, j);
                }
            }
            free_index_arrays(arr_index_set1, arr_index_set2);
            curr = curr->pnext;
        }
    }
}

void print_words_found_ll(NODE_LL_WORDS_HOLDER *current, int *index_set1, int *index_set2, int j) {
    if (index_set1 != NULL){
        printf("LL NODE -> %d Set1 Match\n", j);
        print_found_words_and_ufp6(&current->words_holder.s1, index_set1);
    }

    if (index_set2 != NULL){
        printf("LL NODE -> %d Set2 Match\n", j);
        print_found_words_and_ufp6(&current->words_holder.s2, index_set2);
    }
}

void free_index_arrays(int *arr1, int *arr2){
    free(arr1);
    arr1 = NULL;
    free(arr2);
    arr2 = NULL;
}

void write_set_to_txt(const SETS *set, FILE *fp) {
    if(fp == NULL) fperror("Error opening file");
    ///write rowsize (size of words in set) to file
    fprintf(fp, "number_words = %d\n", set->rowsize);
    for (int i = 0; i < set->rowsize; i++) {
        //fwrite(set->matrix[i], sizeof(char), set->arr_word_size[i], fp);  // Write each row
        fprintf(fp, "%d-",  set->arr_word_size[i]);
        for (int j = 0; j < set->arr_word_size[i]; ++j) {
            fprintf(fp, "%c ",  set->matrix[i][j]);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "UFP6:\n");
    write_set_ufp6_to_txt(set, fp);
}

void save_both_sets_to_txt(const SETS *s1, const SETS *s2, char *filename) {
    FILE *fp = NULL;

    fp = fopen(filename, "a+");

    if (fp == NULL){
        fperror("fp in save_both_sets_to_txt");
    }

    write_set_to_txt(s1, fp);
    write_set_to_txt(s2, fp);

    fclose(fp);
}

int write_words_found_in_da_to_txt(const VAL_AD_WORDS_HOLDER *val_ad, const int *index_set1, const int *index_set2, const char *filename, int index_ad) {
    FILE *fp = fopen(filename, "a+");

    if (fp == NULL) {
        fperror("Opening file in write_words_found_to txt");
    }
    ///if found words in set1 or set2
    if (index_set1 != NULL || index_set2 != NULL){
        fprintf(fp, "INDEX %d\n", index_ad);
    }
    ///if found words in set1
    if (index_set1 != NULL){
        fprintf(fp, "->Words set 1\n");
        write_index_array_words_to_file(&val_ad->words_holder.s1, fp, index_set1);
    }
    ///if found words in set2
    if (index_set2 != NULL){
        fprintf(fp, "->Words set 2\n");
        write_index_array_words_to_file(&val_ad->words_holder.s2, fp, index_set2);
    }
    fclose(fp);
    return 0;
}

int write_words_found_in_ll_to_txt(const NODE_LL_WORDS_HOLDER *current, const int *index_set1, const int *index_set2, const char *filename, int index_ll) {
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        fperror("Opening file in write_words_found_to txt");
    }
    ///If found words in set1 or set2
    if (index_set1 != NULL || index_set2 != NULL){
        fprintf(fp, "NODE %d\n", index_ll);
    }
    ///If found words in set1
    if (index_set1 != NULL){
        fprintf(fp, "->Words set 1\n");
        write_index_array_words_to_file(&current->words_holder.s1, fp, index_set1);
    }
    ///if found words in set2
    if (index_set2 != NULL){
        fprintf(fp, "->Words set 2\n");
        write_index_array_words_to_file(&current->words_holder.s2, fp, index_set2);
    }
    fclose(fp);
    return 0;
}


void write_index_array_words_to_file(const SETS *set,FILE *fp,const int *array_index) {
    if(fp == NULL) fperror("Error opening file");
    ///count of indexes from the words found in set stored in first position of array
    for (int i = 1; i <= *array_index; i++) {
        fprintf(fp, "Row Index -> %d\n",  array_index[i]);
        fprintf(fp, "Word = %s |",  set->matrix[array_index[i]]);
      
        write_index_array_ufp6_to_file(set, fp, array_index, i);
        fputc('\n', fp);
    }
}

void write_index_array_ufp6_to_file(const SETS *set, FILE *fp, const int *array_index, int r) {
    if(fp == NULL) fperror("Error opening file");
    fprintf(fp," UFP6 = ");
    for (int i = 0; i < *(set->arr_ufp6_size + (*(array_index + r))); i++) {
        // fprintf(fp,"%d", *(*(set->matrix_ufp6 + (*(array_index + k))))+ i);
        fprintf(fp, "%d",  set->matrix_ufp6[array_index[r]][i]);
       // printf("%d", set->matrix_ufp6[array_index[r]][i]);
    }
}

int save_set_txt(const SETS *set, char *filename) {
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        fperror("Error opening file in save_set_txt");
    }

    write_set_to_txt(set, fp);

    fclose(fp);
    return 0;
}

void write_set_ufp6_to_txt(const SETS *set, FILE *fp) {
   if(fp == NULL) fperror("Error opening file");
    //fprintf(fp, "UFP6 encode:\n");
    for (int i = 0; i < set->rowsize ; ++i) {
        fprintf(fp,"%d-", *((*set).arr_ufp6_size + i));
        for (int j = 0; j < set->arr_ufp6_size[i]; j++) {
            fprintf(fp,"%d ", (*(*(set->matrix_ufp6 + i) + j)));
            //fprintf(fp, " %d", set->matrix_ufp6[i][j]);
        }
        fprintf(fp, "\n");
    }
}

void read_txt_to_set(SETS *set, FILE *fp) {
    if(fp == NULL) fperror("Error opening file");

    ///read rowsize from file
    fscanf(fp, "%*[^=]%*[=] %d", &set->rowsize);
    ///Initialize set
    sets_struct_init_v2(set, set->rowsize);

    /// Read set of words
    read_txt_words(set, fp);

    ///Read UFP from set
    read_ufp6_file_to_set(set, fp);
}

void read_txt_words(SETS *set, FILE *fp) {
    if(fp == NULL) fperror("Error opening file");
    for (int i = 0; i < set->rowsize; ++i) {
        fscanf(fp, "%d", &set->arr_word_size[i]);
        fscanf(fp, "%*[-]");
        ///Allocate memory for each row to store word in matrix given size
        calloc_col_word(&set->matrix[i],set->arr_word_size[i]);
        for (int j = 0; j < set->arr_word_size[i]; ++j) {
            fscanf(fp, " %c ",&set->matrix[i][j]);
        }
    }
}
/**
 * Function to initialize set while reading from file
 */
void sets_struct_init_v2(SETS *set, int num_words) {
    if(num_words <= 0) fperror("Invalid number of words");
    set->rowsize = num_words;
    ///Initialise array to hold each word size
    init_arr_word_size(set);
    ///Initialise array to hold each UFP6 size
    init_arr_ufp6_size(set);
    ///Initialize matrix words and UFP6 to num_words pointers
    calloc_matrix_words_and_ufp6(set, num_words);
}

void calloc_col_word(char **mat_row, int col_words_size) {
    *mat_row = (char*) calloc(col_words_size ,sizeof(char));
    if(*mat_row == NULL){
        fperror("Matrix col calloc in calloc_col_words");
    }
}

void read_ufp6_file_to_set(SETS *set, FILE *fp) {
    if(fp == NULL) fperror("Error opening file");
    ///read UFP6: to void
    fscanf(fp, "%*s");
    for (int i = 0; i < set->rowsize; ++i) {
        ///Read size of UFP6 representation
        fscanf(fp, "%d", &set->arr_ufp6_size[i]);
        fscanf(fp, "%*[-]");
        ///allocate for each row size of columns read from file
        calloc_col_ufp6(&set->matrix_ufp6[i], set->arr_ufp6_size[i]);
        for (int j = 0; j < set->arr_ufp6_size[i]; ++j) {
            ///Read UFP6 representation to set
            fscanf(fp, "%d",&set->matrix_ufp6[i][j]);
        }
    }
}

void calloc_col_ufp6(int **mat_encode_row, int col_words_size) {
    *mat_encode_row = (int*) calloc(col_words_size ,sizeof(int));
    if (*mat_encode_row == NULL) {
        fperror("Matrix col calloc in calloc_col_words");
    }
}

void write_ad_to_txt(const AD_WORDS_HOLDER *ad,const char *fn) {
    FILE *fp = NULL;

    fp = fopen(fn, "w");
    if (fp == NULL) {
        fperror("Opening file in write_ad_to_file");
    }
    ///Write size of elements in dynamic array
    fprintf(fp, "Number of elements: %d\n", ad->count);

    for (int i = 0; i < ad->count; ++i) {
        ///Write index of ad
        fprintf(fp, "\nIndex %d\n", i);
        fprintf(fp, "Last Update Date: %s\n", ad->array_val[i].last_update_date);
        ///Write both sets inside each index
        write_both_sets_to_txt(&ad->array_val[i].words_holder ,fp);
    }
    fclose(fp);
}

void write_both_sets_to_txt(const WORDS_HOLDER *wordsHolder, FILE *fp) {
    if(fp == NULL) fperror("Error opening file");

    fprintf(fp, "Words set: 1\n");
    write_set_to_txt(&wordsHolder->s1, fp);
    fprintf(fp, "Words set: 2\n");
    write_set_to_txt(&wordsHolder->s2, fp);
}

void read_from_txt_to_ad(AD_WORDS_HOLDER **ad,const char *fn, bool flag) {
    FILE *fp = NULL;

    fp = fopen(fn, "r");
    if(fp == NULL){
        fperror("Opening File in read_from_txt_to_ad");
    }
    ///Read size of elements from file and initialize dynamic array
    int num_elem = 0;
    ///%*[^:]%*[:] = read until : to void and after read : to void
    fscanf(fp, "%*[^:]%*[:] %d", &num_elem);
    *ad = dynamic_array_init(num_elem);

    for (int i = 0; i < (*ad)->size; ++i) {
        ///Read line to void
        fscanf(fp, "%*s");
        char date[DATE_SIZE];
        ///Read last update date
        fscanf(fp, "%*[^:]%*[:] %s",date);

        SETS set1 = {NULL, NULL, NULL, NULL, 0};
        read_txt_to_set(&set1, fp);

        SETS set2 = {NULL, NULL, NULL, NULL, 0};
        read_txt_to_set(&set2,fp);
        ///Read in chronological order ASC if set to 1
        if(flag == 1){
            insert_element_to_AD_in_order(*ad, &set1, &set2,date);
        }else{
            insert_element_to_index_AD(*ad,&set1, &set2,date,i);
        }
    }
    fclose(fp);
}

LL_WORDS_HOLDER *ll_init() {
    LL_WORDS_HOLDER *ll = NULL;
    ll = (LL_WORDS_HOLDER*) calloc(1, sizeof(LL_WORDS_HOLDER));
    if(ll == NULL){
        fperror("LL_WORDS_HOLDER calloc in ll_init");
    }
    return ll;
}

void write_ll_to_txt(const LL_WORDS_HOLDER *ll, const char *fn) {
    FILE *fp = NULL;

    fp = fopen(fn, "w");
    if (fp == NULL) {
        fperror("Opening file in write_ll_to_file");
    }
    ///Write size of elements in dynamic array
    fprintf(fp, "Number of nodes: %d\n", ll->nnodes);
    ///Pointer to traverse the ll from head to tail
    NODE_LL_WORDS_HOLDER *ncurr = ll->phead;
    int i = 0;
    while(ncurr != NULL){
        ///Write index of ad
        fprintf(fp, "\nNode %d\n", i);
        fprintf(fp, "Last Update Date: %s\n", ncurr->last_update_date);
        ///Write both sets inside each index
        write_both_sets_to_txt(&ncurr->words_holder, fp);
        ncurr = ncurr->pnext;
        i++;
    }
    fclose(fp);
}

void read_from_txt_to_ll(LL_WORDS_HOLDER *ll, const char *fn, bool flag) {
    FILE *fp = NULL;

    fp = fopen(fn, "r");
    if(fp == NULL){
        fperror("Opening File in read_from_txt_to_ad");
    }

    int num_nodes = 0;
    ///%*[^:]%*[:] = read until : to void and after read : to void
    fscanf(fp, "%*[^:]%*[:] %d", &num_nodes);

    for (int i = 0; i < num_nodes; ++i) {
        ///Read line to void
        fscanf(fp, "%*s");
        char date[DATE_SIZE] = " ";
        ///Read last update date
        fscanf(fp, "%*[^:]%*[:] %s",date);
        SETS set1 = {NULL, NULL, NULL, NULL, 0};
        read_txt_to_set(&set1, fp);
        SETS set2 = {NULL, NULL, NULL, NULL, 0};
        read_txt_to_set(&set2,fp);
        ///Read in chronological order DESC if set to 1
        if(flag == 1){
            insert_node_ll_sorted(ll, &set1, &set2,date);
        }else{
            insert_node_ll_index(ll, &set1, &set2,date, i);
        }
    }
    fclose(fp);
}


void write_ad_to_bin(const AD_WORDS_HOLDER *ad, const char *fn) {
    FILE *fp = NULL;

    fp = fopen(fn, "wb");
    if (fp == NULL) {
        fperror("Opening file in write_ad_to_file");
    }
    ///Write size of elements in dynamic array
    fwrite(&ad->count, sizeof(ad->count), 1,fp);

    for (int i = 0; i < ad->count; ++i) {
        //Write index of ad
        //fprintf(fp, "\nIndex %d\n", i);
        size_t date_length = strlen(ad->array_val[i].last_update_date) + 1; // + '\0'
        fwrite(ad->array_val[i].last_update_date, sizeof(char), date_length, fp);
        ///Write both sets inside each index
        write_both_sets_to_binfile(&ad->array_val[i].words_holder ,fp);
    }
    fclose(fp);
}


/// Write both Sets to bin file
void write_both_sets_to_binfile(const WORDS_HOLDER *wordsHolder, FILE *fp) {
    if(fp == NULL) fperror("Error opening file");
  
    write_set_to_binfile(&wordsHolder->s1, fp);
    write_set_to_binfile(&wordsHolder->s2, fp);
}


void write_set_to_binfile(const SETS *set, FILE *fp) {
    if(fp == NULL) fperror("Error opening file");

    ///write rowsize (size of words in set) to file
    fwrite(&set->rowsize, sizeof(set->rowsize), 1,fp);
    for (int i = 0; i < set->rowsize; i++) {
        ///Write sizeof each word
        fwrite(&set->arr_word_size[i],sizeof(set->arr_word_size[i]), 1, fp);
        for (int j = 0; j < set->arr_word_size[i]; ++j) {
            fwrite(&set->matrix[i][j],sizeof(set->matrix[i][j]), 1, fp);
        }
    }
    write_set_ufp6_to_binfile(set, fp);
}

void write_set_ufp6_to_binfile(const SETS *set, FILE *fp) {
    if(fp == NULL) fperror("Error opening file");
    //fprintf(fp, "UFP6 encode:\n");
    for (int i = 0; i < set->rowsize ; ++i) {
        ///Write size of UFP6 representation
        fwrite(&set->arr_ufp6_size[i],sizeof(set->arr_ufp6_size[i]),1, fp);
        for (int j = 0; j < set->arr_ufp6_size[i]; j++) {
            fwrite(&(set->matrix_ufp6[i][j]),sizeof(set->matrix_ufp6[i][j]), 1, fp);
        }
    }
}

void read_from_bin_to_ad(AD_WORDS_HOLDER **ad, const char *fn, bool flag) {
    FILE *fp = NULL;

    fp = fopen(fn, "rb");
    if(fp == NULL){
        fperror("Opening File in read_from_txt_to_ad");
    }
    /// Read size of elements from file and initialize dynamic array
    int num_elem = 0;
    fread(&num_elem,sizeof(num_elem),1,fp);
    *ad = dynamic_array_init(num_elem);

    for (int i = 0; i < (*ad)->size; ++i) {
        char date[DATE_SIZE] = " ";
        ///Read last update date
        fread(date,sizeof(char),DATE_SIZE,fp);

        SETS set1 = {NULL, NULL, NULL, NULL, 0};
        read_binfile_to_set(&set1, fp);
        SETS set2 = {NULL, NULL, NULL, NULL, 0};
        read_binfile_to_set(&set2,fp);
        ///Insert to Dynamic Array in chronological order ASC if set to 1
        if(flag == 1){
            insert_element_to_AD_in_order(*ad, &set1, &set2,date);
        }else{
            insert_element_to_index_AD(*ad,&set1, &set2,date,i);
        }
    }
    fclose(fp);
}

void read_binfile_to_set(SETS *set, FILE *fp) {
    if(fp == NULL) fperror("Error opening file");

    ///Read size of words from file
    fread(&set->rowsize, sizeof(set->rowsize),1, fp);

    sets_struct_init_v2(set, set->rowsize);

    ///Read set of words
    read_binfile_words(set, fp);
    ///Read ufp6 from set
    read_ufp6_binfile_to_set(set, fp);
}

void read_binfile_words(SETS *set, FILE *fp) {
    if(fp == NULL) fperror("Error opening file");
  
    for (int i = 0; i < set->rowsize; ++i) {
        ///Read word size to set
        fread(&set->arr_word_size[i], sizeof(set->arr_word_size[i]), 1, fp);
        ///Allocate memory for each row
        calloc_col_word(&set->matrix[i],set->arr_word_size[i]);
        for (int j = 0; j < set->arr_word_size[i]; ++j) {
            ///Read each char to matrix
            fread(&set->matrix[i][j], sizeof(char), 1, fp);
        }
    }
}


void read_ufp6_binfile_to_set(SETS *set, FILE *fp) {
    if(fp == NULL) fperror("Error opening file");

    for (int i = 0; i < set->rowsize; ++i) {
       ///Read size of UFP6 representation
        fread(&set->arr_ufp6_size[i],sizeof(int),1,fp);
        ///allocate for each row size of columns read from file
        calloc_col_ufp6(&set->matrix_ufp6[i], set->arr_ufp6_size[i]);
        for (int j = 0; j < set->arr_ufp6_size[i]; ++j) {
            fread(&set->matrix_ufp6[i][j], sizeof(set->matrix_ufp6[i][j]),1 ,fp);
        }
    }
}

void write_ll_to_binfile(const LL_WORDS_HOLDER *ll, const char *fn) {
    FILE *fp = NULL;

    fp = fopen(fn, "wb");
    if (fp == NULL) {
        fperror("Opening file in write_ll_to_file");
    }
    ///Write size of elements in dynamic array
    fwrite(&ll->nnodes, sizeof(int),1, fp);
    ///Pointer to traverse the ll from head to tail
    NODE_LL_WORDS_HOLDER *ncurr = ll->phead;
    int i = 0;
    while(ncurr != NULL){
        ///Write index of ad
        int len = (int) strlen(ncurr->last_update_date) + 1;
        fwrite(&len, sizeof(int), 1,fp);
        fwrite(ncurr->last_update_date, sizeof(char), len,fp);
        ///Write both sets inside each index
        write_both_sets_to_binfile(&ncurr->words_holder, fp);
        ncurr = ncurr->pnext;
        i++;
    }
    fclose(fp);
}

void read_from_binfile_to_ll(LL_WORDS_HOLDER *ll, const char *fn, bool flag) {
    FILE *fp = NULL;
    fp = fopen(fn, "rb");
    if(fp == NULL){
        fperror("Opening File in read_from_binfile_to_ll");
    }

    int num_nodes = 0;
   
    fread(&num_nodes, sizeof(num_nodes), 1, fp);
    printf("num_nodes %d\n", num_nodes);

    for (int i = 0; i < num_nodes; ++i) {
        char date[DATE_SIZE] = " ";
        ///Read last update date
        int len = 0;
        fread(&len, sizeof(int), 1, fp);
        fread(date, sizeof(char), len, fp);
        printf("%s\n", date);

        SETS set1 = {NULL, NULL, NULL, NULL, 0};
        read_binfile_to_set(&set1, fp);
        SETS set2 = {NULL, NULL, NULL, NULL, 0};
        read_binfile_to_set(&set2,fp);
        ///Read in chronological order DESC if set to 1
        if(flag == 1){
            insert_node_ll_sorted(ll, &set1, &set2,date);
        }else{
            insert_node_ll_index(ll, &set1, &set2,date, i);
        }
    }
    fclose(fp);
}

void write_words_found_to_txt_set_with_pattern(const SETS *set, const int *array_index_words_found_set, const char *filename, const char *pattern) {
    FILE *fp = fopen(filename, "a");
    if(fp == NULL){
        fperror("Opening file in write_words_found_to_txt_set_with_pattern");
    }
    fprintf(fp, "Pattern \"%s\" found in these words from set:\n", pattern);
    write_index_array_words_to_file(set, fp, array_index_words_found_set);

    fclose(fp);
}
