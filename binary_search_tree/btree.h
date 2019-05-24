#ifndef BTREE_H
#define BTREE_H

#include <stdlib.h>

// Define a structure for binary tree nodes.
typedef struct _btnode {
        void *data;
        struct _btnode *left;
        struct _btnode *right;
} btnode_t;

// Define a structure for binary trees.
typedef struct btree {
        size_t size;
        int (*compare)(const void *value1, const void *value2);
        void (*destroy)(void *data);
        btnode_t *root;
} btree_t;

/* Public Interface. ------------------------------------------------------ */

void btree_init(btree_t *tree, void (*destroy)(void *data));

void btree_destroy(btree_t *tree);

int btree_insert_left(btree_t *tree, btnode_t *node, const void *data);

int btree_insert_right(btree_t *tree, btnode_t *node, const void *data);

void btree_remove_left(btree_t *tree, btnode_t *node);

void btree_remove_right(btree_t *tree, btnode_t *node);

int btree_merge(btree_t *merge, btree_t *left, btree_t *right, const void *data);

/* Macros. ---------------------------------------------------------------- */

#define btree_size(tree) ((tree)->size)

#define btree_root(tree) ((tree)->root)

#define btree_is_eob(node) ((node) == NULL)

#define btree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)

#define btree_data(node) ((node)->data)

#define btree_left(node) ((node)->left)

#define btree_right(node) ((node)->right)

#endif
