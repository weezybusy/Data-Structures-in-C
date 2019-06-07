#include <stdlib.h>
#include <string.h>

#include "bstree.h"

/* Auxiliary functions. -------------------------------------------------- */

static void destroy_right(bstree_t *tree, btnode_t *node);

static void rotate_left(btnode_t **node)
{
        btnode_t *left;
        btnode_t *grandchild;

        left = btree_left(*node);

        if (((avlnode_t *) btree_data(left))->factor == AVL_LEFT_HEAVY) {
                // Perform an LL rotation.
                btree_left(*node) = btree_right(left);
                btree_right(left) = *node;
                ((avlnode_t *) btree_data(*node))->factor = AVL_BALANCED;
                ((avlnode_t *) btree_data(left))->factor = AVL_BALANCED;
                *node = left;
        } else {
                // Perform an LR rotation.
                grandchild = btree_right(left);
                btree_right(left) = btree_left(grandchild);
                btree_left(grandchild) = left;
                btree_left(*node) = btree_right(grandchild);
                btree_right(grandchild) = *node;

                switch (((avlnode_t *) btree_data(grandchild))->factor) {
                case AVL_LEFT_HEAVY:
                        ((avlnode_t *) btree_data(*node))->factor = AVL_RIGHT_HEAVY;
                        ((avlnode_t *) btree_data(left))->factor = AVL_BALANCED;
                        break;
                case AVL_BALANCED:
                        ((avlnode_t *) btree_data(*node))->factor = AVL_BALANCED;
                        ((avlnode_t *) btree_data(left))->factor = AVL_BALANCED;
                        break;
                case AVL_RIGHT_HEAVY:
                        ((avlnode_t *) btree_data(*node))->factor = AVL_BALANCED;
                        ((avlnode_t *) btree_data(left))->factor = AVL_LEFT_HEAVY;
                        break;
                default:
                        break;
                }

                ((avlnode_t *) btree_data(grandchild))->factor = AVL_BALANCED;
                *node = grandchild;
        }
}

static void rotate_right(btnode_t **node)
{
        btnode_t *right;
        btnode_t *grandchild;

        right = btree_right(*node);

        if (((avlnode_t *) btree_data(right))->factor == AVL_RIGHT_HEAVY) {
                // Perform RR rotation.
                btree_right(*node) = btree_left(right);
                btree_left(right) = *node;
                ((avlnode_t *) btree_data(*node))->factor = AVL_BALANCED;
                ((avlnode_t *) btree_data(right))->factor = AVL_BALANCED;
                *node = right;
        } else {
                // Perform RL rotation.
                grandchild = btree_left(right);
                btree_left(right) = btree_right(grandchild);
                btree_right(grandchild) = right;
                btree_right(*node) = btree_left(grandchild);
                btree_left(grandchild) = *node;

                switch (((avlnode_t *) btree_data(grandchild))->factor) {
                case AVL_LEFT_HEAVY:
                        ((avlnode_t *) btree_data(*node))->factor = AVL_BALANCED;
                        ((avlnode_t *) btree_data(right))->factor = AVL_RIGHT_HEAVY;
                        break;
                case AVL_BALANCED:
                        ((avlnode_t *) btree_data(*node))->factor = AVL_BALANCED;
                        ((avlnode_t *) btree_data(right))->factor = AVL_BALANCED;
                        break;
                case AVL_RIGHT_HEAVY:
                        ((avlnode_t *) btree_data(*node))->factor = AVL_LEFT_HEAVY;
                        ((avlnode_t *) btree_data(right))->factor = AVL_BALANCED;
                        break;
                default:
                        break;
                }

                ((avlnode_t *) btree_data(grandchild))->factor = AVL_BALANCED;
                *node = grandchild;
        }
}

static void destroy_left(bstree_t *tree, btnode_t *node)
{
        btnode_t **position;

        // Do not allow destruction of an empty tree.
        if (btree_size(tree) == 0) {
                return;
        }

        // Determine where to destroy nodes.
        if (node == NULL) {
                position = &tree->root;
        } else {
                position = &node->left;
        }

        // Destroy the nodes.
        if (*position != NULL) {
                destroy_left(tree, *position);
                destroy_right(tree, *position);

                if (tree->destroy != NULL) {
                        // Call a user-defined function to free data.
                        tree->destroy(((avlnode_t *) (*position)->data)->data);
                }

                // Free the AVL data in the node, then free the node itself.
                free((*position)->data);
                free(*position);
                *position = NULL;

                // Adjust the size of the tree after destroying the node.
                tree->size--;
        }
}

static void destroy_right(bstree_t *tree, btnode_t *node)
{
        btnode_t **position;

        // Do not allow destruction of an empty tree.
        if (btree_size(tree) == 0) {
                return;
        }

        // Determine where to destroy nodes.
        if (node == NULL) {
                position = &tree->root;
        } else {
                position = &node->right;
        }

        // Destroy the nodes.
        if (*position != NULL) {
                destroy_left(tree, *position);
                destroy_right(tree, *position);

                if (tree->destroy != NULL) {
                        // Call a user-defined function to free data.
                        tree->destroy(((avlnode_t *) (*position)->data)->data);
                }

                // Free the AVL data in the node, then free the node itself.
                free((*position)->data);
                free(*position);
                *position = NULL;

                // Adjust the size of the tree after destroying the node.
                tree->size--;
        }
}

static int insert(bstree_t *tree, btnode_t **node, const void *data,
                int *balanced)
{
        avlnode_t *avl_data;
        int cmpval;
        int retval;

        // Insert the data into the tree.
        if (btree_is_eob(*node)) {
                // Handle insertion into an empty tree.
                avl_data = (avlnode_t *) malloc(sizeof(avlnode_t));
                if (avl_data == NULL) {
                        return -1;
                }

                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = 0;
                avl_data->data = (void *) data;

                return btree_insert_left(tree, *node, avl_data);
        } else {
                // Handle insertion into a tree that is not empty.
                cmpval = tree->compare(data, ((avlnode_t *) btree_data(*node))->data);

                if (cmpval < 0) {
                        // Move to the left.
                        if (btree_is_eob(btree_left(*node))) {
                                avl_data = (avlnode_t *) malloc(sizeof(avlnode_t));
                                if (avl_data == NULL) {
                                        return -1;
                                }

                                avl_data->factor = AVL_BALANCED;
                                avl_data->hidden = 0;
                                avl_data->data = (void *) data;

                                if (btree_insert_left(tree, *node, avl_data) != 0) {
                                        return -1;
                                }

                                *balanced = 0;
                        } else {
                                retval = insert(tree, &btree_left(*node), data, balanced);
                                if (retval != 0) {
                                        return retval;
                                }
                        }

                        // Ensure that the tree remains balanced.
                        if (!(*balanced)) {
                                switch (((avlnode_t *) btree_data(*node))->factor) {
                                case AVL_LEFT_HEAVY:
                                        rotate_left(node);
                                        *balanced = 1;
                                        break;
                                case AVL_BALANCED:
                                        ((avlnode_t *) btree_data(*node))->factor = AVL_LEFT_HEAVY;
                                        break;
                                case AVL_RIGHT_HEAVY:
                                        ((avlnode_t *) btree_data(*node))->factor = AVL_BALANCED;
                                        *balanced = 1;
                                        break;
                                default:
                                        break;
                                }
                        }
                } else if (cmpval > 0) {
                        // Move to the right.
                        if (btree_is_eob(btree_right(*node))) {
                                avl_data = (avlnode_t *) malloc(sizeof(avlnode_t));
                                if (avl_data == NULL) {
                                        return -1;
                                }

                                avl_data->factor = AVL_BALANCED;
                                avl_data->hidden = 0;
                                avl_data->data = (void *) data;

                                if (btree_insert_right(tree, *node, avl_data) != 0) {
                                        return -1;
                                }

                                *balanced = 0;
                        } else {
                                retval = insert(tree, &btree_right(*node), data, balanced);
                                if (retval != 0) {
                                        return retval;
                                }
                        }

                        // Ensure that the tree remains balanced.
                        if (!(*balanced)) {
                                switch (((avlnode_t *) btree_data(*node))->factor) {
                                case AVL_LEFT_HEAVY:
                                        ((avlnode_t *) btree_data(*node))->factor = AVL_BALANCED;
                                        *balanced = 1;
                                        break;
                                case AVL_BALANCED:
                                        ((avlnode_t *) btree_data(*node))->factor = AVL_RIGHT_HEAVY;
                                        break;
                                case AVL_RIGHT_HEAVY:
                                        rotate_right(node);
                                        *balanced = 1;
                                        break;
                                default:
                                        break;
                                }
                        }
                } else {
                        // Handle finding a copy of the data.
                        if (!((avlnode_t *) btree_data(*node))->hidden) {
                                // Do nothing since the data is in the tree and not hidden.
                                return 1;
                        } else {
                                // Insert the new data an mark it as not hidden.
                                if (tree->destroy != NULL) {
                                        // Destroy the hidden data since it is being balanced.
                                        tree->destroy(((avlnode_t *) btree_data(*node))->data);
                                }

                                ((avlnode_t *) btree_data(*node))->data = (void *) data;
                                ((avlnode_t *) btree_data(*node))->hidden = 0;
                                
                                // Do not rebalance because the tree structure is unchanged.
                                *balanced = 1;
                        }
                }

        }
        return 0;
}

static int hide(bstree_t *tree, btnode_t *node, const void *data)
{
        int cmpval;
        int retval = 0;

        if (btree_is_eob(node)) {
                // Return that the data was not found.
                return -1;
        }

        cmpval = tree->compare(data, ((avlnode_t *) btree_data(node))->data);

        if (cmpval < 0) {
                // Move to the left.
                retval = hide(tree, btree_left(node), data);
        } else if (cmpval > 0) {
                // Move to the right.
                retval = hide(tree, btree_right(node), data);
        } else {
                // Mark the node as hidden.
                ((avlnode_t *) btree_data(node))->hidden = 1;
                retval = retval;
        }

        return retval;
}

static int lookup(bstree_t *tree, btnode_t *node, void **data)
{
        int cmpval;
        int retval = 0;

        if (btree_is_eob(node)) {
                // Return that the data was not found.
                return -1;
        }

        cmpval = tree->compare(*data, ((avlnode_t *) btree_data(node))->data);

        if (cmpval < 0) {
                // Move to the left.
                retval = lookup(tree, btree_left(node), data);
        } else if (cmpval < 0) {
                // Move to the right.
                retval = lookup(tree, btree_right(node), data);
        } else {
                if (!((avlnode_t *) btree_data(node))->hidden) {
                        // Pass back the data from the tree.
                        *data = ((avlnode_t *) btree_data(node))->data;
                } else {
                        // Retrun that the data was not found.
                        retval = -1;
                }
        }

        return retval;
}

/* Public interface implementation. --------------------------------------- */

void bstree_init(bstree_t *tree,
                int (*compare)(const void *key1, const void *key2),
                void (*destroy)(void *data))
{
        // Initialize the tree.
        btree_init(tree, destroy);
        tree->compare = compare;
}

void bstree_destroy(bstree_t *tree)
{
        // Destroy all nodes in the tree.
        destroy_left(tree, NULL);

        // No operations are allowed now, clear the structure.
        memset(tree, 0, sizeof(bstree_t));
}

int bstree_insert(bstree_t *tree, const void *data)
{
        int balanced = 0;
        return insert(tree, &btree_root(tree), data, &balanced);
}

int bstree_remove(bstree_t *tree, const void *data)
{
        return hide(tree, btree_root(tree), data);
}

int bstree_lookup(bstree_t *tree, void **data)
{
        return lookup(tree, btree_root(tree), data);
}
