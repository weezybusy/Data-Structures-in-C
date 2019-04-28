#include <stdlib.h>
#include <string.h>

#include "btree.h"

void btree_init(btree_t *tree, void (*destroy)(void *data))
{
        tree->size = 0;
        tree->compare = NULL;
        tree->destroy = destroy;
        tree->root = NULL;
}

void btree_destroy(btree_t *tree)
{
        // Remove all the nodes from the tree.
        btree_remove_left(tree, NULL);

        // No operations are allowed now, clear the structure as a precaution.
        memset(tree, 0, sizeof(btree_t));
}

int btree_insert_left(btree_t *tree, bt_node_t *node, const void *data)
{
        bt_node_t *new_node = NULL;
        bt_node_t **position = NULL;

        // Determine where to insert the node.
        if (node == NULL) {
                // Allow insertion at the root only in an empty tree.
                if (btree_size(tree) > 0) {
                        return -1;
                }
                position = &tree->root;
        } else {
                // Normally allow insertion only at the end of a branch.
                if (btree_left(node) != NULL) {
                        return -1;
                }
                position = &node->left;
        }

        // Allocate storage for the node.
        new_node = (bt_node_t *) malloc(sizeof(bt_node_t));
        if (new_node == NULL) {
                return -1;
        }

        // Insert the node into the tree.
        new_node->data = (void *) data;
        new_node->left = NULL;
        new_node->right = NULL;
        *position = new_node;

        // Adjust the size of the tree to account for the inserted node.
        tree->size++;

        return 0;
}

int btree_insert_right(btree_t *tree, bt_node_t *node, const void *data)
{
        bt_node_t *new_node = NULL;
        bt_node_t **position = NULL;

        // Determine where to insert the node.
        if (node == NULL) {
                // Allow insertion at the root only in an empty tree.
                if (btree_size(tree) > 0) {
                        return -1;
                }
                position = &tree->root;
        } else {
                // Normally allow insertion only at the end of a branch.
                if (btree_right(node) != NULL) {
                        return -1;
                }
                position = &node->right;
        }

        // Allocate storage for the node.
        new_node = (bt_node_t *) malloc(sizeof(bt_node_t));
        if (new_node == NULL) {
                return -1;
        }

        // Insert the node into the tree.
        new_node->data = (void *) data;
        new_node->left = NULL;
        new_node->right = NULL;
        *position = new_node;

        // Adjust the size of the tree to account for the inserted node.
        tree->size++;

        return 0;
}

void btree_remove_left(btree_t *tree, bt_node_t *node)
{
        bt_node_t **position;

        // Do not allow removal from an empty tree.
        if (btree_size(tree) == 0) {
                return;
        }

        // Determine where to remove nodes.
        if (node == NULL) {
                position = &tree->root;
        } else {
                position = &node->left;
        }

        // Remove nodes.
        if (*position != NULL) {
                btree_remove_left(tree, *position);
                btree_remove_right(tree, *position);
                if (tree->destroy != NULL) {
                        // Call a user-defined function to free data.
                        tree->destroy((*position)->data);
                }
                free(*position);
                *position = NULL;

                // Adjust the size of the tree.
                tree->size--;
        }
}

void btree_remove_right(btree_t *tree, bt_node_t *node)
{
        bt_node_t **position;

        // Do not allow removal from an empty tree.
        if (btree_size(tree) == 0) {
                return;
        }

        // Determine where to remove nodes.
        if (node == NULL) {
                position = &tree->root;
        } else {
                position = &node->right;
        }

        // Remove nodes.
        if (*position != NULL) {
                btree_remove_left(tree, *position);
                btree_remove_right(tree, *position);
                if (tree->destroy != NULL) {
                        // Call a user-defined function to free data.
                        tree->destroy((*position)->data);
                }
                free(*position);
                *position = NULL;

                // Adjust the size of the tree.
                tree->size--;
        }
}

int btree_merge(btree_t *merge, btree_t *left, btree_t *right, const void *data)
{
        // Initialize the merged tree.
        btree_init(merge, left->destroy);

        // Insert the data for the root node of the merged tree.
        if (btree_insert_left(merge, NULL, data) != 0) {
                btree_destroy(merge);
                return -1;
        }

        // Merge the two binary trees into a single binary tree.
        btree_root(merge)->left = btree_root(left);
        btree_root(merge)->right = btree_root(right);

        // Adjust the size of the binary tree.
        merge->size = merge->size + btree_size(left) + btree_size(right);

        // Do not let the original trees access the merged nodes.
        left->root = NULL;
        left->size = 0;
        right->root = NULL;
        right->size = 0;

        return 0;
}
