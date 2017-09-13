#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"
#include "container.h"

/* default table size should be 3877 */

struct htablerec {
    int capacity;
    int num_keys;
    int *frequency;
    container *keys;
    int type;
};

/* quick way to double hash. this method is called when inserting and searching
   returns the key double hashed */
static unsigned int htable_step(htable h, unsigned int i_key){
    return 1 + (i_key % (h->capacity -1));
}

/* turns a word into an integer, given to us in lab 12
   returns result, the integer, paramter is the word to be transformed*/
static unsigned int htable_word_to_int(char *word){
    unsigned int result = 0;

    while(*word != '\0') {
        result = (*word++ + 31 * result);
    }

    return result;
}
    
/* creates a new hash table allocating memory for the entire table, the
   frequency and the keys. All keys are set to NULL and all frequencies
   set to 0. Takes param capacity which is the default size of the htable
   returns the newly constructed empty htable */
htable htable_new(int capacity, int type) {
    int i;
    htable result = emalloc(sizeof *result);
    result->type = type;
    result->num_keys = 0;
    result->capacity = capacity;
    result->frequency = emalloc(result->capacity * sizeof result->frequency[0]);
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    for(i = 0; i < capacity; i++){
        result->keys[i] = NULL;
        result->frequency[i] = 0;
    }
    return result;
}

/* frees all memory. First all the individual keys, then the empty keys array,
   then frequency array. We don't need to empty each individual frequency
   because they are integers. Then frees the intire table. Param is the htable
   to be freed */
void htable_free(htable h){
    int i;

    for(i = 0; i < h->capacity; i++){
        if(h->keys[i] != NULL){
            free(h->keys[i]);
        }   
    }
    free(h->keys);
    free(h->frequency);
    free(h);
}

/* inserts a word into the htable. turns the word into an integer which will be
   the key. if collision, increases collisions and rehashes, creating a new
   key. Returns 1 for successful first time insert, if word is already there
   returns frequency of that word. If no free space returns 0.
   Param h table is htable to be inserted in, word is the word to be inserted */

int htable_insert(htable h, char *word){
    int index;
    int collisions = 0;
    index = (htable_word_to_int(word)) % h->capacity;
    index = (index + collisions *htable_step(h, collisions))%h->capacity;      
    do {        
        if(h->keys[index] == NULL){
            h->keys[index] = container_new(h->type);
            container_add(h->keys[index], word);
            h->frequency[index]++;
            return 1;
        }
        if(h->keys[index] != NULL){
            container_add(h->keys[index], word);
        
            if(container_find(h->keys[index], word) == 1){
                h->frequency[index]++;;
                return h->frequency[index];
            }

            collisions++;
            index = (index+ htable_step(h, collisions))% h->capacity;
            
        }
   
    } while(collisions < h->capacity);
    
    return 0;
}


/* prints words as long as the position has something in it and we don't exceed
   the capacity. Param htable is the htable to be printed, stream is std out
   (i think) */
void htable_print(htable h, FILE *stream){
    int i;
 
    for(i = 0; i < h->capacity; i++){
        if(h->frequency[i] != 0){
            fprintf(stream, "Index: %d, ", i);
            fprintf(stream, "Frequency: %d\n", h->frequency[i]);
            container_print(h->keys[i]);
            printf("\n");
        }
    }
}

/* searches htable for a word. turns word into an integer using same insertion
   method of rehashing until word is found. returns frequency of word if found
   returns 0 if not found. */
int htable_search(htable h, char *word){
    int collisions = 0;
    int index = (htable_word_to_int(word)) % h->capacity;
    index = (index + collisions *htable_step(h, collisions))%h->capacity;
    if(h->keys[index] == NULL){
        return 0;
    } else {
    return container_find(h->keys[index], word);
    }
}


    
    
