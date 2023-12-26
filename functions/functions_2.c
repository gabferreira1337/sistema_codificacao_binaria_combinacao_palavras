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

#define DYNAMIC_ARRAY_SIZE 1


int main_functions_2(int argc, char **argv) {

  /* // b)

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
    encode_matrix_words(&set2, sizes, dic);*/

   /* char *testDates[] = {
            "2023-11-25",
            "2023-11-24",
            "2022-12-01",
            "2023-01-15",
            "2022-08-10",
    };

    insert_element_to_AD_in_order(arr_din, set1, set2, testDates[1]);
    insert_element_to_AD_in_order(arr_din, set1, set2, testDates[4]);
    insert_element_to_AD_in_order(arr_din, set1, set2, testDates[3]);

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
    print_AD(arr_din);*/

    //free_dynamic_array(arr_din);

   /* encode_matrix_words(&set1, sizes,dic);

    print_matrix_char(&set1);
    print_matrix_char(&set2);

    freemem_set(&set1);
    freemem_set(&set2);

    exit(0);
*/
   // return 0;
}

AD_WORDS_HOLDER *dynamic_array_init(int size) {
    AD_WORDS_HOLDER *arr = (AD_WORDS_HOLDER*) calloc(1,sizeof(AD_WORDS_HOLDER));
    if(arr == NULL) {
        fperror("Dynamic_array_init array_val calloc");
    }
    //store size of array
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
    char *date_str = malloc(sizeof(char) * DATE_SIZE); // Adjust the size as needed
    strftime(date_str, DATE_SIZE, "%d/%m/%y", timeinfo);
    return date_str;
}

/**
 * @paragraph Insert element to AD in chronological order by date ASC
 * @paragraph function uses binary search to search for the position in AD where
 * new element will be inserted and adjusts the position of the other elements in AD before inserting
 * when array is full double the size of AD S
 * @paragraph This insertion function has a time complexity of O(2N +Dlog(N)) , Extra space O(1) (inplace)
 * Shifting elements O(N) , realloc O(N) , binary_search function O(Dlog(N)), insertion O(1)
 */
void insert_element_to_AD_in_order(AD_WORDS_HOLDER *ad_holder,SETS *s1,SETS *s2,const char *last_date) {
    /// Double the size when array is full
    if (ad_holder->count == ad_holder->size) {
        realloc_AD(ad_holder, ad_holder->size * 2);
    }

    int pos = bin_search_insert_pos(ad_holder, last_date);

    for (int i = ad_holder->count; i > pos; i--) {
        ad_holder->array_val[i] = ad_holder->array_val[i - 1];
    }
    insert_to_VAL_AD_WORDS_HOLDER(&ad_holder->array_val[pos],s1,s2,last_date);

    ad_holder->count++;
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
            //If elements are equal, insert at the current position
            return mid;
        }
    }
    // return insert position
    return lo;
}

/**
 * @paragraph Insert element to VAL_AD_WORDS_HOLDER
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
 * @paragraph function shifts elements to insert new element in the given index and fill VAl_AD_WORDS_HOLDER
 * with the values passes in the function
 * @paragraph This insertion function has a time complexity of O(2N + D)) , Extra space O(1) (inplace)
 * Shifting elements O(N) , realloc O(N) , insertion O(1), strcpy date O(D)
 */
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

    insert_to_VAL_AD_WORDS_HOLDER(&ad_holder->array_val[index], set1,set2,last_date);

    ad_holder->count++;
}


void delete_element_index(AD_WORDS_HOLDER *ad, int index) {
    ///halve the size when array is one-quarter full
    if (ad->count == (1/4 * ad->size)){
        realloc_AD(ad, ad->size / 2);
    }

    for (int i = index; i < ad->count; ++i) {
       ad->array_val[i] = ad->array_val[i + 1];
    }

    free(ad->array_val[ad->count].last_update_date);

    ad->count--;
}


void find_word_ad(const AD_WORDS_HOLDER *arr,const char **words,int W, int lo, int hi,const char *fn,bool flag) {
    if(lo < 0 || hi >= arr->count){
        fperror("LO or HI out of bounds");
    }
    int *index_set1 = NULL,*index_set2 = NULL;
    for (int i = 0; i < W; ++i) {
        ///Calculate length of string
        int word_length =(int) strlen(words[i]);
        ///Check if word is valid in ufp6
        if(is_ufp6(words[i], word_length) == -1) continue;
        int dfa[MAX_UFP6][BITS - 1];
        KMP (words[i], dfa);
            for (int j = lo; j <= hi; ++j) {
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
    //if ll empty
    if(ll->ptail == NULL && ll->phead == NULL){
        ll->phead = create_words_holder_node(ll, NULL,set1, set2, last_date);
        ll->ptail = ll->phead;
        ll->nnodes++;
        return;
    }

    //bin search
    NODE_LL_WORDS_HOLDER *pos = bin_search_pos_ll(ll, last_date);
    NODE_LL_WORDS_HOLDER *temp;
        //add to tail
        if (pos == NULL) {
            ll->ptail->pnext = create_words_holder_node(ll, pos, set1, set2, last_date);
            //point new node to back node
            ll->ptail->pnext->pback = ll->ptail;
            //point back node to new node
            ll->ptail = ll->ptail->pnext;
            //point new node to NULL
            ll->ptail->pnext = NULL;
        } else if (pos->pback == NULL && strcmp(last_date,pos->last_update_date) < 0){
            //add to head // && strcmp() because binsearch of pos when searching
            //for a position it returns the left side note and we need to add to the left
            ll->phead = create_words_holder_node(ll, pos, set1, set2, last_date);
            pos->pback = ll->phead;
            ll->phead->pnext = pos;
        } else {
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

//Even if runtime is O(n), we only do O(log n) total comparisons (one per step of bs).
//Binary search to find  position where the new node should be added (in chronological order ASC)
//When LL is empty or when the date is higher than all the dates inside LL returns NULL,
//When newdate is the lowest date the function returns a pointer to the first node
//When newdate is between two dates the function returns a pointer to the left node
//Example 1: node1->lastdate 20-01-2023   node2->lastdate 23-01-2023   newdate = 22-01-2023 this functions returns node1 so add to left
//Example 2: node1->lastdate 20-01-2023 newdate = 19-01-2023 this function returns node1 so we add
NODE_LL_WORDS_HOLDER *bin_search_pos_ll(LL_WORDS_HOLDER *ll, char *date) {
    NODE_LL_WORDS_HOLDER *lo = ll->phead;
    NODE_LL_WORDS_HOLDER *hi = ll->ptail;
    NODE_LL_WORDS_HOLDER *mid = NULL;

    while (lo != NULL && hi != NULL) {
        // Find middle
         mid = find_mid_ll(lo, hi);

        // If empty
        if (mid == NULL){
            return NULL;
        }

        int cmp = strcmp(mid->last_update_date, date);

        // If value is present at middle
        if (cmp < 0){
            lo = mid->pnext;
        }else if (cmp > 0){
            hi = mid->pback;
        }else{
            return mid;
        }
    }
    return lo;
}


NODE_LL_WORDS_HOLDER *create_words_holder_node(LL_WORDS_HOLDER *ll, NODE_LL_WORDS_HOLDER *pos, SETS *set1, SETS *set2, char *last_date) {
    // calloc to initialize to 0 or NULL
    NODE_LL_WORDS_HOLDER *node = (NODE_LL_WORDS_HOLDER *) calloc(1,sizeof(NODE_LL_WORDS_HOLDER));
    if(node == NULL){
        fperror("Calloc NODE_LL_WORDS_HOLDER");
        // exit(0);
    }

    node->words_holder.s1 = *set1;
    node->words_holder.s2 = *set2;
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
        pos->pnext = ll->phead;//ver isto
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
    //fast_ptr == NULL , end fast_ptr->pnext == NULL indicate that fast_ptr is the last node
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
}

void find_word_ll(const LL_WORDS_HOLDER *ll, char **words, int W, int lo, int hi, const char *fn, bool flag) {
    //Check if out of bounds
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
        int word_length = (int) strlen(words[i]);
        //check if word is valid in ufp6
        if(is_ufp6(words[i], word_length) == -1) continue;
        int dfa[MAX_UFP6][BITS];
        KMP (words[i], dfa);
        NODE_LL_WORDS_HOLDER *current = lo_node;
        for (int j = lo; j <= hi && current->pnext !=NULL; ++j) {
            index_set1 = search_KMP(&current->words_holder.s1,dfa ,word_length);
            index_set2 =  search_KMP(&current->words_holder.s2,dfa ,word_length);
            print_words_found_ll(current, index_set1, index_set2, j);
            if(flag == 1){
                write_words_found_to_txt(current, index_set1, index_set2,fn, j);
            }
            free(index_set1);
            index_set1 = NULL;
            free(index_set2);
            index_set2 = NULL;
            current = current->pnext;
        }
    }
}

void print_words_found_ll(NODE_LL_WORDS_HOLDER *current, int *index_set1, int *index_set2, int j) {
    if (index_set1 != NULL){
        printf("LL NODE -> %d Set1 Match ", j);
        print_found_words_and_ufp6(&current->words_holder.s1, index_set1);
    }

    if (index_set2 != NULL){
        printf("LL NODE -> %d Set2 Match, ", j);
        print_found_words_and_ufp6(&current->words_holder.s2, index_set2);
    }
}

void write_set_to_txt(const SETS *set, FILE *fp) {
    //write rowsize (number of words in set) to file
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

int write_words_found_to_txt(const NODE_LL_WORDS_HOLDER *current,const int *index_set1,const int *index_set2,const char *filename, int index_ll) {
    FILE *fp = fopen(filename, "a+");

    if (fp == NULL) {
        fperror("Opening file in write_words_found_to txt");
    }
    //if found words in set1 or set2
    if (index_set1 != NULL || index_set2 != NULL){
        fprintf(fp, "NODE %d\n", index_ll);
    }
    //if found words in set1
    if (index_set1 != NULL){
        fprintf(fp, "->Words set 1\n");
        write_index_array_words_to_file(&current->words_holder.s1, fp, index_set1);
    }
    //if found words in set2
    if (index_set2 != NULL){
        fprintf(fp, "->Words set 2\n");
        write_index_array_words_to_file(&current->words_holder.s2, fp, index_set2);
    }
    fclose(fp);
    return 0;
}

void write_index_array_words_to_file(const SETS *set,FILE *fp,const int *array_index) {
    //count of indexes from the words found in set stored in first position of array
    for (int i = 1; i <= *array_index; i++) {
        fprintf(fp, "Index -> %d\n",  array_index[i]);
        fprintf(fp, "Word = %s |",  set->matrix[array_index[i]]);
      
        write_index_array_ufp6_to_file(set, fp, array_index, i);
        fputc('\n', fp);
    }
}

void write_index_array_ufp6_to_file(const SETS *set, FILE *fp, const int *array_index, int r) {
    fprintf(fp," UFP6 = ");
    for (int i = 0; i < *(set->arr_ufp6_size + (*(array_index + r))); i++) {
        // fprintf(fp,"%d", *(*(set->matrix_ufp6 + (*(array_index + k))))+ i);
        fprintf(fp, "%d",  set->matrix_ufp6[array_index[r]][i]);
       // printf("%d", set->matrix_ufp6[array_index[r]][i]);
    }
}

int save_set_txt(const SETS *set, char *filename) {
    FILE *fp = fopen(filename, "a+");

    if (fp == NULL) {
        fperror("Error opening file in save_set_txt");
    }

    write_set_to_txt(set, fp);

    fclose(fp);

    return 0;
}

void write_set_ufp6_to_txt(const SETS *set, FILE *fp) {
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
    //read rowsize from file
    fscanf(fp, "%*[^=]%*[=] %d", &set->rowsize);
    sets_struct_init_v2(set, set->rowsize);

    // Read set of words
    read_txt_words(set, fp);

    //Read ufp6 from set
    //UFP6: read for void
    read_ufp6_file_to_set(set, fp);
}

void read_txt_words(SETS *set, FILE *fp) {
    for (int i = 0; i < set->rowsize; ++i) {
        fscanf(fp, "%d", &set->arr_word_size[i]);
        fscanf(fp, "%*[-]");
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
    set->rowsize = num_words;
    init_arr_word_size(set);
    set->arr_ufp6_size = (int*) calloc(set->rowsize, sizeof(int));
    set->matrix_ufp6 =(int**) calloc(set->rowsize, sizeof(int*));
    set->matrix = (char**) calloc(set->rowsize, sizeof(char*));
}

void calloc_col_word(char **mat_row, int col_words_size) {
    *mat_row = (char*) calloc(col_words_size ,sizeof(char));
    if(*mat_row == NULL){
        fperror("Matrix col calloc in calloc_col_words");
    }
}

void read_ufp6_file_to_set(SETS *set, FILE *fp) {
    //read UFP6: to void
    fscanf(fp, "%*s");
    for (int i = 0; i < set->rowsize; ++i) {
        fscanf(fp, "%d", &set->arr_ufp6_size[i]);
        fscanf(fp, "%*[-]");
        //allocate for each row number of columns read from file
        calloc_col_ufp6(&set->matrix_ufp6[i], set->arr_ufp6_size[i]);
        for (int j = 0; j < set->arr_ufp6_size[i]; ++j) {
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
    //write mode
    fp = fopen(fn, "w");

    if (fp == NULL) {
        fperror("Opening file in write_ad_to_file");
    }
    //Write number of elements in dynamic array
    fprintf(fp, "Number of elements: %d\n", ad->count);

    for (int i = 0; i < ad->count; ++i) {
        //Write index of ad
        fprintf(fp, "\nIndex %d\n", i);
        fprintf(fp, "Last Update Date: %s\n", ad->array_val[i].last_update_date);
        //Write both sets inside each index
        write_both_sets_to_txt(&ad->array_val[i].words_holder ,fp);
    }
    fclose(fp);
}

void write_both_sets_to_txt(const WORDS_HOLDER *wordsHolder, FILE *fp) {
    fprintf(fp, "Words set: 1\n");
    write_set_to_txt(&wordsHolder->s1, fp);
    fprintf(fp, "Words set: 2\n");
    write_set_to_txt(&wordsHolder->s2, fp);
}

void read_from_txt_to_ad(AD_WORDS_HOLDER **ad,const char *fn, bool flag) {
    FILE *fp = NULL;
    //read mode
    fp = fopen(fn, "r");

    if(fp == NULL){
        fperror("Opening File in read_from_txt_to_ad");
    }
    // Read number of elements from file and initialize dynamic array
    int num_elem = 0;
    //%*[^:]%*[:] = read until : to void and after read : to void
    fscanf(fp, "%*[^:]%*[:] %d", &num_elem);
    *ad = dynamic_array_init(num_elem);

    for (int i = 0; i < (*ad)->size; ++i) {
        //Read line to void
        fscanf(fp, "%*s");
        char date[DATE_SIZE];
        //Read last update date
        fscanf(fp, "%*[^:]%*[:] %s",date);

        SETS set1 = {NULL, NULL, NULL, NULL, 0,0};
        read_txt_to_set(&set1, fp);

        SETS set2 = {NULL, NULL, NULL, NULL, 0,0};
        read_txt_to_set(&set2,fp);
        //Read in chronological order if set to 1
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
    //write mode
    fp = fopen(fn, "w");

    if (fp == NULL) {
        fperror("Opening file in write_ll_to_file");
    }
    //Write number of elements in dynamic array
    fprintf(fp, "Number of nodes: %d\n", ll->nnodes);
    //Pointer to traverse the ll from head to tail
    NODE_LL_WORDS_HOLDER *ncurr = ll->phead;
    int i = 0;
    while(ncurr != NULL){
        //Write index of ad
        fprintf(fp, "\nNode %d\n", i);
        fprintf(fp, "Last Update Date: %s\n", ncurr->last_update_date);
        //Write both sets inside each index
        write_both_sets_to_txt(&ncurr->words_holder, fp);
        ncurr = ncurr->pnext;
        i++;
    }
    fclose(fp);
}

void read_from_txt_to_ll(LL_WORDS_HOLDER *ll, const char *fn, bool flag) {
    FILE *fp = NULL;
    //read mode
    fp = fopen(fn, "r");

    if(fp == NULL){
        fperror("Opening File in read_from_txt_to_ad");
    }

    int num_nodes = 0;
    //%*[^:]%*[:] = read until : to void and after read : to void
    fscanf(fp, "%*[^:]%*[:] %d", &num_nodes);

    for (int i = 0; i < num_nodes; ++i) {
        //Read line to void
        fscanf(fp, "%*s");
        char date[DATE_SIZE];
        //Read last update date
        fscanf(fp, "%*[^:]%*[:] %s",date);

        SETS set1 = {NULL, NULL, NULL, NULL, 0,0};
        read_txt_to_set(&set1, fp);

        SETS set2 = {NULL, NULL, NULL, NULL, 0,0};
        read_txt_to_set(&set2,fp);
        //Read in chronological order if set to 1
        if(flag == 1){
            insert_node_ll_sorted(ll, &set1, &set2,date);
        }else{
            insert_node_ll_index(ll, &set1, &set2,date, i);
        }
    }
    fclose(fp);
}

// Typing in binary into a file
void write_ad_to_bin(const AD_WORDS_HOLDER *ad, const char *fn) {
    FILE *fp = NULL;
    //write mode
    fp = fopen(fn, "wb");

    if (fp == NULL) {
        fperror("Opening file in write_ad_to_file");
    }
    //Write number of elements in dynamic array
    fwrite(&ad->count, sizeof(ad->count), 1,fp);

    for (int i = 0; i < ad->count; ++i) {
        //Write index of ad
        //fprintf(fp, "\nIndex %d\n", i);
        fwrite(ad->array_val[i].last_update_date, sizeof(ad->array_val[i].last_update_date), strlen(ad->array_val[i].last_update_date), fp);
        //Write both sets inside each index
        write_both_sets_to_binfile(&ad->array_val[i].words_holder ,fp);
    }
    fclose(fp);
}


// Writting both Sets into the bin file, ww'll call this in write ad to bin

void write_both_sets_to_binfile(const WORDS_HOLDER *wordsHolder, FILE *fp) {
    //fprintf(fp, "Words set: 1\n");
    write_set_to_binfile(&wordsHolder->s1, fp);
    //fprintf(fp, "Words set: 2\n");
    write_set_to_binfile(&wordsHolder->s2, fp);
}

// Will be called inside the write_both_sets_to_binfile
void write_set_to_binfile(const SETS *set, FILE *fp) {
    //write rowsize (number of words in set) to file
    fwrite(&set->rowsize, sizeof(set->rowsize), 1,fp);
    for (int i = 0; i < set->rowsize; i++) {
        //fwrite(set->matrix[i], sizeof(char), set->arr_word_size[i], fp);  // Write each row
        fwrite(&set->arr_word_size[i],sizeof(set->arr_word_size[i]), 1, fp);
        for (int j = 0; j < set->arr_word_size[i]; ++j) {
            fwrite(&set->matrix[i][j],sizeof(set->matrix[i][j]), 1, fp);
        }
        //(fp, "\n");
    }
   // fprintf(fp, "UFP6:\n");
    write_set_ufp6_to_binfile(set, fp);
}

void write_set_ufp6_to_binfile(const SETS *set, FILE *fp) {
    //fprintf(fp, "UFP6 encode:\n");
    for (int i = 0; i < set->rowsize ; ++i) {
        fwrite(&set->arr_ufp6_size[i],sizeof(set->arr_ufp6_size[i]),1, fp);
        //fwrite(&set->arr_ufp6_size[i],sizeof(set->arr_ufp6_size[i]) ,1, stdout);
        for (int j = 0; j < set->arr_ufp6_size[i]; j++) {
            fwrite(&(set->matrix_ufp6[i][j]),sizeof(set->matrix_ufp6[i][j]), 1, fp);
        }
    }
}

void read_from_bin_to_ad(AD_WORDS_HOLDER **ad, const char *fn, bool flag) {
    FILE *fp = NULL;
    //read mode
    fp = fopen(fn, "rb");

    if(fp == NULL){
        fperror("Opening File in read_from_txt_to_ad");
    }
    // Read number of elements from file and initialize dynamic array
    int num_elem = 0;
    //%*[^:]%*[:] = read until : to void and after read : to void
    //fscanf(fp, "%*[^:]%*[:] %d", &num_elem);
    fread(&num_elem,sizeof(num_elem),1,fp);
    *ad = dynamic_array_init(num_elem);

    for (int i = 0; i < (*ad)->size; ++i) {
        //Read line to void
        //fscanf(fp, "%*s");
        char date[DATE_SIZE];
        //Read last update date
        //fscanf(fp, "%*[^:]%*[:] %s",date);
        fread(date,sizeof(date),DATE_SIZE,fp);
        printf("sate %s\n", date);

        SETS set1 = {NULL, NULL, NULL, NULL, 0,0};
        read_binfile_to_set(&set1, fp);

        SETS set2 = {NULL, NULL, NULL, NULL, 0,0};
        read_binfile_to_set(&set2,fp);
        //Read in chronological order if set to 1
        if(flag == 1){
            insert_element_to_AD_in_order(*ad, &set1, &set2,date);
        }else{
            insert_element_to_index_AD(*ad,&set1, &set2,date,i);
        }
    }
    fclose(fp);
}

void read_binfile_to_set(SETS *set, FILE *fp) {
    //read rowsize from file
    //fscanf(fp, "%*[^=]%*[=] %d", &set->rowsize);
    fread(&set->rowsize, sizeof(set->rowsize),1, fp);
    printf("set %d\n", set->rowsize);

    sets_struct_init_v2(set, set->rowsize);

    // Read set of words
    read_binfile_words(set, fp);

    //Read ufp6 from set
    read_ufp6_binfile_to_set(set, fp);
}

void read_binfile_words(SETS *set, FILE *fp) {
    for (int i = 0; i < set->rowsize; ++i) {
        fread(&set->arr_word_size[i], sizeof(set->arr_word_size[i]), 1, fp);
        calloc_col_word(&set->matrix[i],set->arr_word_size[i]);
        for (int j = 0; j < set->arr_word_size[i]; ++j) {
            //fscanf(fp, "%c",&set->matrix[i][j]);
            fread(&set->matrix[i][j], sizeof(&set->matrix[i][j]), 1, fp);
        }
    }
}

// Reading from a binaryfile into a set
void read_ufp6_binfile_to_set(SETS *set, FILE *fp) {
    //read UFP6: to void
   // fscanf(fp, "%*s");
    for (int i = 0; i < set->rowsize; ++i) {
       // fscanf(fp, "%d", &set->arr_ufp6_size[i]);
        fread(&set->arr_ufp6_size[i],sizeof(set->arr_ufp6_size),1,fp);
        //fscanf(fp, "%*[-]");
        //allocate for each row number of columns read from file
        calloc_col_ufp6(&set->matrix_ufp6[i], set->arr_ufp6_size[i]);
        for (int j = 0; j < set->arr_ufp6_size[i]; ++j) {
            //fscanf(fp, "%d",&set->matrix_ufp6[i][j]);
            fread(&set->matrix_ufp6[i][j], sizeof(set->matrix_ufp6[i][j]),1 ,fp);
        }
    }
}

void write_ll_to_binfile(const LL_WORDS_HOLDER *ll, const char *fn) {
    FILE *fp = NULL;
    //write mode
    fp = fopen(fn, "wb");

    if (fp == NULL) {
        fperror("Opening file in write_ll_to_file");
    }
    //Write number of elements in dynamic array
    //fprintf(fp, "Number of nodes: %d\n", ll->nnodes);
    fwrite(&ll->nnodes, sizeof(ll->nnodes),1, fp);
    //Pointer to traverse the ll from head to tail
    NODE_LL_WORDS_HOLDER *ncurr = ll->phead;
    int i = 0;
    while(ncurr != NULL){
        //Write index of ad
        //fprintf(fp, "\nNode %d\n", i);
        fwrite(ncurr->last_update_date, sizeof(ncurr->last_update_date), strlen(ncurr->last_update_date),fp);
        //Write both sets inside each index
        write_both_sets_to_binfile(&ncurr->words_holder, fp);
        ncurr = ncurr->pnext;
        i++;
    }
    fclose(fp);
}

void read_from_binfile_to_ll(LL_WORDS_HOLDER *ll, const char *fn, bool flag) {
    FILE *fp = NULL;
    //read mode
    fp = fopen(fn, "rb");

    if(fp == NULL){
        fperror("Opening File in read_from_txt_to_ad");
    }

    int num_nodes = 0;
    //%*[^:]%*[:] = read until : to void and after read : to void
    //fscanf(fp, "%*[^:]%*[:] %d", &num_nodes);
    fread(&num_nodes, sizeof(num_nodes), 1, fp);
    printf("num_nodes %d\n", num_nodes);

    for (int i = 0; i < num_nodes; ++i) {
        //Read line to void
        //fscanf(fp, "%*s");
        char date[DATE_SIZE];
        //Read last update date
       // fscanf(fp, "%*[^:]%*[:] %s",date);
        fread(date, sizeof(date), DATE_SIZE, fp);

        SETS set1 = {NULL, NULL, NULL, NULL, 0,0};
        read_binfile_to_set(&set1, fp);

        SETS set2 = {NULL, NULL, NULL, NULL, 0,0};
        read_binfile_to_set(&set2,fp);
        //Read in chronological order if set to 1
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
