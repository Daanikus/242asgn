/* may have to combine sortflexarray.h and flexarray.h to align with the
   assignment file list */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "flexarray.h"


struct flexarrayrec {
    int capacity;
    int itemcount;
    char **items;
};


/* Recursively uses binary search to find the given word from the search
   function.
   Returns -1 if array is empty
   Returns 0 if word not found
   Returns 1 if word is found
   takes a flex array, the word to be found, 0 and array size as params */
int is_present(flexarray f, char *word, int low, int high){
    int mid;
     
    if(NULL == f){
        return 0;
    }
    
    if(low > high){
        return 0;
    }
    
    mid = (low + high)/2;
    if(strcmp(f->items[mid], word) == 0){
        return 1;
    } else {
        if(strcmp(f->items[mid], word) < 0){
            return is_present(f, word, mid + 1, high);
        } else {
            return is_present(f, word, low, mid -1);
        }
    }

}

/* Calls the is_present method and prints which is appropriate */
int flex_search(flexarray f, char *word){
    return is_present(f, word, 0, f->itemcount);            
}

void print(flexarray f, int i){
    printf("%s", f->items[i]);
}

void visit(flexarray f, void z(flexarray f, int i)){
    int i;
    for(i = 0; i < f->itemcount; i++){
        z(f, i);
    }
}


flexarray flexarray_new() {
    int i;
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    for(i = 0; i < result->capacity; i++){
        result->items[i] = NULL;
    }
    return result;
}

void flexarray_append(flexarray f, char *word) {
    if (f->itemcount == f->capacity) {
        f->capacity += f->capacity; 
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    f->items[f->itemcount] = emalloc((strlen(word) + 1) * sizeof f->items[0][0]);
    strcpy(f->items[f->itemcount++], word); 
}

void flexarray_print(flexarray f) {
    int i;
    for (i = 0; i < f->itemcount; i++) {
        printf("%s\n", (f->items[i]));
    }
    /* a "for" loop to print out each cell of f->items */
}

void flexarray_sort(flexarray f) {
    int i;
    char *key = NULL;
    int j;
    int n = f->itemcount;

    /** Make the current index the key and then decrement the pointer. **/ 
    for (i = 1; i < n; i++){  
        key = f->items[i];       
        j = i - 1;
        
        /** Move elements of array that are greater than key to one postion
            ahead of current. **/
        while(j >= 0 && (strcmp(f->items[j], key) > 0)){
            f->items[j + 1] = f->items[j];
            j = j - 1;
        }
        f->items[j + 1] =  key;
    }
}

void flexarray_free(flexarray f) {
    int i;

    for(i = 0; i < f->itemcount; i++){
        if(f->items[i] != NULL){
            free(f->items[i]);
        }
    }
    free(f->items);
    free(f);
}
