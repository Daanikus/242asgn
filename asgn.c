/*All compiles together fine. Just need to create a working main method and run a few tests. May be a few more special methods to make outlined in Assignment


  To Do:

  -Add timing information
  -Make the program read another file and print out those that aren't
  found in out hash table.
  -Add comments
*/

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "container.h"
#include "flexarray.h"
#include "htable.h"
#include "mylib.h"

#define DEFAULT_CAP 3877


int main(int argc, char **argv){
    int i;
    FILE *infile;
    int notfound;
    int capacity;
    htable my_htable;
    const char *opstring = "rs:pih";
    char option;
    char word[256];

        if (NULL == (infile = fopen(argv[1], "r"))) {
        fprintf(stderr, "%s: can’t find file %s\n", argv[0], argv[1]);
        return EXIT_FAILURE;
    }

        
            
    while((option = getopt(argc, argv, opstring)) != EOF){
        switch(option){
            
            case 'r':
                printf("Using an rbt!\n");
                my_htable = htable_new(DEFAULT_CAP, 1);
                while(1 == fscanf(infile, "%s", word)){
                    for(i = 0; word[i]; i++){
                        word[i] = tolower(word[i]);
                    }
                    htable_insert(my_htable, word);
                }
               
                break;
               
            case 's':
                capacity = atoi(optarg);
                printf("Capacity chosen: %d\n", capacity);
                if(capacity < 1){
                    printf("Integer not larger than 1!");
                } else {
                    my_htable = htable_new(capacity, 0);
                    while(1 == fscanf(infile, "%s", word)){
                        htable_insert(my_htable, word);
                    }
                }
                break;
                
            case 'p':
                printf("Printing htable:\n");
                my_htable = htable_new(DEFAULT_CAP, 0);
                while(1 == fscanf(infile, "%s", word)){
                    for(i = 0; word[i]; i++){
                        word[i] = tolower(word[i]);
                    }
                    htable_insert(my_htable, word);
                }
                htable_print(my_htable, stdout);
                break;
                /*
            case 'i':
                
                fillstart = clock();
                my_htable = htable_new(DEFAULT_CAP, 0);
                while(1 == fscanf(infile, "%s", word)){
                    htable_insert(my_htable, word);
                }
                fillend = clock();
                filltime = (fillend - fillstart)/(double)CLOCKS_PER_SEC;

                
                
                Print info about how long it took to fill the htable,
                   how long it took to search the htable, and how many unknowns
                   were found eg.

                   Fill Time : 1.390000
                   Search Time : 0.0450000
                   Unknown Words : 8690
                */
            case 'h':
                fprintf(stderr, "Help:\nUse option 'r' to use the robust "
                        "chaining method of using a red-black tree.\nUse "
                        "option 's' followed by an integer greater than "
                        "0 to change the default htable size.\nUse option "
                        "'p' to print the contents of your hash table.\n"
                        "Use option 'i' to print out information about how "
                        "long it took to fill and search the hash table, "
                        "and how many unknown words were found.\nBy default "
                        "the program will use a hash table size of 3877 and "
                        "fill the table from the given file.");
                break;
                
            default:
                
                printf("default case\n");
                my_htable = htable_new(DEFAULT_CAP, 0);
                while(1 == fscanf(infile, "%s", word)){
                    htable_insert(my_htable, word);
                }
                break;                 
        }
    }


        printf("cases complete\n");
        while (getword(word, sizeof word, stdin) != EOF){
            if(htable_search(my_htable, word) == 0){ /* doesn't find because they're lower case */
                printf("%s\n", word);
                notfound++;
            }
        }
        
    
            
            
    return EXIT_SUCCESS; 
}
