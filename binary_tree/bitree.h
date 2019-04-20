#ifndef BITREE_H
#define BITREE_H

#include <stdlib.h>

// Define a structure for binary tree nodes.
typedef struct btnode {
        void *data;
        struct btnode *left;
        struct btnode *right;
} btnode_t;

// Define a structure for binary trees.
typedef struct bitree {
        size_t size;
        int (*compare)(const void *value1, const void *value2);
        void (*destroy)(void *data);
        btnode_t *root;
} bitree_t;

/* Public Interface. ------------------------------------------------------ */

void bitree_init(bitree_t *tree, void (*destroy)(void *data));

void bitree_destroy(bitree_t *tree);

int bitree_insert_left(bitree_t *tree, btnode_t *node, const void *data);

int bitree_insert_right(bitree_t *tree, btnode_t *node, const void *data);

void bitree_remove_left(bitree_t *tree, btnode_t *node);

void bitree_remove_right(bitree_t *tree, btnode_t *node);

int bitree_merge(bitree_t *merge, bitree_t *left, bitree_t *right, const void *data);

/* Macros. ---------------------------------------------------------------- */

#define bitree_size(tree) ((tree)->size)

#define bitree_root(tree) ((tree)->root)

#define bitree_is_eob(node) ((node) == NULL)

#define bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)

#define bitree_data(node) ((node)->data)

#define bitree_left(node) ((node)->left)

#define bitree_right(node) ((node)->right)

#endif
