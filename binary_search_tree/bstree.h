#ifndef BSTREE_H
#define BSTREE_H

#include "btree.h"

/* Define balance factors for AVL trees. ---------------------------------- */

#define AVL_LEFT_HEAVY   1
#define AVL_BALANCED     0
#define AVL_RIGHT_HEAVY -1

/* Define a structure for nodes in AVL trees. ----------------------------- */

typedef struct _avlnode {
        void *data;
        int hidden;
        int factor;
} avlnode_t;

/* Implement binary search trees as binary trees. ------------------------- */

typedef btree_t bstree_t;

/* Public Interface. ------------------------------------------------------ */

void bstree_init(bstree_t *tree,
                int (*compare)(const void *key1, const void *key2),
                void (*destroy)(void *data));

void bstree_destroy(bstree_t *tree);

int bstree_insert(bstree_t *tree, const void *data);

int bstree_remove(bstree_t *tree, const void *data);

int bstree_lookup(bstree_t *tree, void **data);

/* Macros. ---------------------------------------------------------------- */

#define bstree_size(tree) ((tree)->size)

#endif
