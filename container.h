#ifndef CONTAINER_H_
#define CONTAINER_H_

typedef enum { FLEX_ARRAY, RED_BLACK_TREE } container_t;
typedef struct containerrec *container;

extern container container_new(int i);
extern void      container_add(container c, char *word);
extern int       container_find(container c, char *word);
extern void      container_print(container c);
#endif
