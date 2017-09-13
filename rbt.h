#ifndef RBT_H_
#define RBT_H_

typedef enum { RED, BLACK } rbt_colour;
typedef struct rbt_node *rbt;

extern rbt   rbt_delete(rbt b, char *str);
extern rbt   rbt_free(rbt b);
extern void  rbt_inorder(rbt b);
extern rbt   rbt_insert(rbt b, char *str);
extern rbt   rbt_new();
extern void  rbt_preorder(rbt b);
extern int   rbt_search(rbt b, char *str);
extern rbt   black_root(rbt b, char *str);

#endif
