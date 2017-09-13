#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rbt.h"
#include "mylib.h"
#include "container.h"



struct rbt_node {
    char *key;
    rbt_colour colour;
    rbt left;
    rbt right;
    int frequency;
};

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) (NULL != (x) && (RED == (x)->colour))

rbt rbt_new() {
    return NULL;
}

           
static rbt right_rotate(rbt b){
    rbt temp;

    temp = b;
    b = b->left;
    temp->left = b->right;
    b->right = temp;

    return b;
}

static rbt left_rotate(rbt b){
    rbt temp;

    temp = b;
    b = b->right;
    temp->right = b->left;
    b->left = temp;

    return b;
}

static rbt case3(rbt b){
    b = right_rotate(b);
    b->colour = BLACK;
    b->right->colour = RED;
    return b;
}

static rbt case2(rbt b){
    b->left = left_rotate(b->left);
    b = case3(b);
    return b;
}

static rbt case1(rbt b){
    b->colour = RED;
    b->left->colour = BLACK;
    b->right->colour = BLACK;
    return b;
}

rbt black_root(rbt b, char *word){
    b = rbt_insert(b, word);
    b->colour = BLACK;
    return b;
}

static rbt rbt_fix(rbt b){
    
    if(IS_RED(b->left)){
        if(IS_RED(b->left->left)){
            if(IS_RED(b->right)){
                b = case1(b);
            } else {
                b = case3(b);
            }
        }
        if(IS_RED(b->left->right)){
            if(IS_RED(b->right)){
                b = case1(b);
            } else {
                b = case2(b);
            }
        }    
    }

    if(IS_RED(b->right)){
        if(IS_RED(b->right->right)){
            if(IS_RED(b->left)){
                b = case1(b);
            } else {
                b = left_rotate(b);
                b->colour = BLACK;
                b->left->colour = RED;
            }
        }
        if(IS_RED(b->right->left)){
            if(IS_RED(b->left)){
                b = case1(b);
            } else {
                b->right = right_rotate(b->right);
                b = left_rotate(b);
                b->colour = BLACK;
                b->left->colour = RED;
            }
        }
    }

    return b;
}

int rbt_search(rbt b, char *key){
    int comparison;
    
    if (b == NULL){
        return 0; 
    }

    comparison = strcmp(b->key, key);

    if (comparison > 0){
        return rbt_search(b->left, key);
    } else if(comparison < 0){
        return rbt_search(b->right, key);
    }
    return 1;
}

rbt rbt_insert(rbt b, char *word){
    int comparison;
    if (b == NULL){
        b = emalloc(sizeof * b);
        b->key = emalloc((strlen(word) + 1) *   sizeof b->key[0]);
        strcpy(b->key, word);
        
        b->left = rbt_new();
        b->right = rbt_new();

        b->colour = RED;
        
        b->frequency = 1;
        return b = rbt_fix(b);
        
    } else{
        comparison = strcmp(b->key, word);
        
        if (comparison > 0){
            b->left = rbt_insert(b->left, word);
        }
        if (comparison <= 0){
            b->right = rbt_insert(b->right, word);
        }
        return b = rbt_fix(b);
    }
}


void  rbt_inorder(rbt b){
    if (b == NULL){
        return; 
    }
    rbt_inorder(b->left);
    printf("%s: %s\n", b->colour == RED ? "red" : "black",b->key);
    rbt_inorder(b->right);
}

void  rbt_preorder(rbt b){
    if (b == NULL){
        return; 
    }
    printf("%s: %s, ", b->colour == RED ? "red" : "black",b->key);
    rbt_preorder(b->left);
    rbt_preorder(b->right);
}

rbt rbt_delete(rbt b, char *word){
    int comparison;
    rbt successor;
    char *temp;
    rbt temp_rbt;
    
    if(b == NULL){
        return b;
    }else{
        comparison = strcmp(b->key, word);
        if(comparison == 0){

            if((b->left != NULL) && (b->right != NULL)){
                successor = b->right;
                while (successor != NULL){
                    successor = successor->left;
                    if (successor->left == NULL){
                        break;
                    }
                }
          
                temp = b->key;
                b->key = successor->key;
                successor->key = temp;
                
                b->right = rbt_delete(b->right, word);
                return b; 
            }
            
            if((b->left == NULL) && (b->right == NULL)){
                free(b->key);
                free(b);
                b = NULL;
                return b;
            }
      

            if (b->left == NULL){
                fprintf(stderr, "left child is null\n");
                b = b->right;
                temp_rbt = b->right;
                free(b->key);
                free(b);
                return temp_rbt;
            }
            if (b->right == NULL){
                fprintf(stderr, "right child is null\n");
                temp_rbt = b->left;
                free(b->key);
                free(b);
                return temp_rbt;
            }
            
            b = NULL;
            return b; 
        }
        if(comparison > 0){
            b->left = rbt_delete(b->left, word);
        }
        if(comparison < 0){
            b->right = rbt_delete(b->right, word);
        }
        
        return b;      
    }
}

rbt rbt_free(rbt b){
    if(b->left != NULL)
        free(b->left);
    
    if(b->right != NULL)
        free(b->right);
    
    free(b->key);
    free(b);
    return b;
}
