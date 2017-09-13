#include <stdlib.h>
#include <stdio.h>

#include "mylib.h"
#include "rbt.h"
#include "flexarray.h"
#include "container.h"

struct containerrec {
    container_t type;
    void *contents;
};


container container_new(int i){
    container c = emalloc(sizeof *c);
    if(i == 1){
        c->type = RED_BLACK_TREE;
        c->contents = rbt_new();
    } else if(i == 0){
        c->type = FLEX_ARRAY;
        c->contents = flexarray_new();
    } else {
        printf("Incorrect continer type");
    }
    return c;

}


void container_add(container c, char *word){
    if(c->type == RED_BLACK_TREE){
        c->contents = black_root(c->contents, word);
    } else {
        flexarray_append(c->contents, word);
    }
}

int container_find(container c, char *word){
    if(c->type == RED_BLACK_TREE){
        return rbt_search(c->contents, word);
    }
    if(c->type == FLEX_ARRAY){
        return flex_search(c->contents, word);
    }

    else return 0;
}

void container_print(container c){
    if(c->type == RED_BLACK_TREE){
        rbt_preorder(c->contents);
    } else {
        flexarray_print(c->contents);
    }
}
        
        

