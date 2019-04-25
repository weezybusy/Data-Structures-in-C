#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "bitree.h"

void test_bitree(void);
void test_bitree_init(void);
void test_bitree_destroy(void);
void test_bitree_insert_left(void);
void test_bitree_insert_right(void);
void test_bitree_remove_left(void);
void test_bitree_remove_right(void);

void bitree_fill(bitree_t *tree, btnode_t *root, size_t depth);

int main(void)
{
        test_bitree();
        return EXIT_SUCCESS;
}

void test_bitree(void)
{
        test_bitree_init();
        test_bitree_destroy();
        test_bitree_insert_left();
        //test_bitree_insert_right();
        //test_bitree_remove_left();
        //test_bitree_remove_right();
}

void test_bitree_init(void)
{
        bitree_t tree;
        bitree_init(&tree, free);
        assert(tree.size == 0);
        assert(tree.destroy == free);
        assert(tree.compare == NULL);
        assert(tree.root == NULL);
        bitree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_bitree_destroy(void)
{
        bitree_t tree;
        bitree_init(&tree, free);
        size_t depth = 3;
        bitree_fill(&tree, tree.root, depth);
        bitree_destroy(&tree);
        assert(tree.size == 0);
        assert(tree.destroy == NULL);
        assert(tree.compare == NULL);
        assert(tree.root == NULL);

        printf("%-30s ok\n", __func__);
}

void test_bitree_insert_left(void)
{
        bitree_t tree;
        int *data = NULL;
        int value = 1;

        // Check insertion into an empty list.
        bitree_init(&tree, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(tree.size == 0);
        assert(bitree_insert_left(&tree, NULL, data) == 0);
        assert(tree.size == 1);
        bitree_destroy(&tree);

        // Check insertion in place of root.
        bitree_init(&tree, free);
        assert(tree.size == 0);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_left(&tree, NULL, data) == 0);
        assert(tree.size == 1);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_left(&tree, NULL, data) != 0);
        assert(tree.size == 1);
        free(data);
        bitree_destroy(&tree);

        // Check insertion of several elements.
        bitree_init(&tree, free);
        assert(tree.size == 0);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_left(&tree, NULL, data) == 0);
        assert(tree.size == 1);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_left(&tree, tree.root, data) == 0);
        assert(tree.size == 2);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_left(&tree, bitree_left(tree.root), data) == 0);
        assert(tree.size == 3);

        bitree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void bitree_fill(bitree_t *tree, btnode_t *root, size_t depth)
{
        int *data = NULL;
        int value = 1;

        if (depth == 0) {
                return;
        }

        if (root == NULL) {
                assert((data = (int *) malloc(sizeof(int))) != NULL);
                *data = value;
                bitree_insert_left(tree, NULL, data);
                bitree_fill(tree, tree->root, depth);
        } else {
                int *left = (int *) malloc(sizeof(int));
                int *right = (int *) malloc(sizeof(int));
                assert(left != NULL);
                assert(right != NULL);
                *left = ++value;
                *right = ++value;
                --depth;
                bitree_insert_left(tree, root, (void *) left);
                bitree_insert_right(tree, root, (void *) right);
                bitree_fill(tree, bitree_left(root), depth);
                bitree_fill(tree, bitree_right(root), depth);
        }
}
