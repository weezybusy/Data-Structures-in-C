#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "bstree.h"

void test_bstree(void);
void test_bstree_init(void);
void test_bstree_destroy(void);
void test_bstree_insert(void);
void test_bstree_remove(void);

static int compare(const void *value1, const void *value2);
static void fill(bstree_t *tree, int values[], size_t n);

int main(void)
{
        test_bstree();
        return EXIT_SUCCESS;
}

void test_bstree(void)
{
        test_bstree_init();
        test_bstree_destroy();
        test_bstree_insert();
        test_bstree_remove();
}

void test_bstree_init(void)
{
        bstree_t tree;
        bstree_init(&tree, compare, free);
        assert(tree.size == 0);
        assert(tree.compare == compare);
        assert(tree.destroy == free);
        assert(tree.root == NULL);
        bstree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_bstree_insert(void)
{
        bstree_t tree;
        bstree_init(&tree, compare, free);
        size_t tree_size = bstree_size(&tree);
        int *data = NULL;

        data = (int *) malloc(sizeof(int));
        assert(data != NULL);
        int val = 5;
        *data = val;
        bstree_insert(&tree, (void *) data);
        tree_size++;

        // Check tree size.
        assert(bstree_size(&tree) == tree_size);
        // Check the data is correct.
        assert(*(int *) ((avlnode_t *) btree_data(btree_root(&tree)))->data == val);
        // Check the balance factor.
        assert(((avlnode_t *) btree_data(btree_root(&tree)))->factor == AVL_BALANCED);

        data = (int *) malloc(sizeof(int));
        assert(data != NULL);
        val = 4;
        *data = val;
        bstree_insert(&tree, (void *) data);
        tree_size++;

        assert(bstree_size(&tree) == tree_size);
        assert(*(int *) ((avlnode_t *) btree_data(btree_left(btree_root(&tree))))->data == val);
        assert(((avlnode_t *) btree_data(btree_root(&tree)))->factor == AVL_LEFT_HEAVY);
        assert(((avlnode_t *) btree_data(btree_left(btree_root(&tree))))->factor == AVL_BALANCED);

        data = (int *) malloc(sizeof(int));
        assert(data != NULL);
        val = 6;
        *data = val;
        bstree_insert(&tree, (void *) data);
        tree_size++;

        assert(bstree_size(&tree) == tree_size);
        assert(*(int *) ((avlnode_t *) btree_data(btree_right(btree_root(&tree))))->data == val);
        assert(((avlnode_t *) btree_data(btree_root(&tree)))->factor == AVL_BALANCED);
        assert(((avlnode_t *) btree_data(btree_left(btree_root(&tree))))->factor == AVL_BALANCED);


        // TODO: Check inserting the data which is already in.

        bstree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_bstree_remove(void)
{
        // TODO: Check removing from the empty tree.
        bstree_t tree;
        bstree_init(&tree, compare, free);
        bstree_destroy(&tree);

        // TODO: Check removing elements from the tree which is not empty.
        bstree_t tree;
        bstree_init(&tree, compare, free);
        size_t size = 7;
        fill(&tree, (int[]){9, 123, 41, 59, 7, 6, 1, 34}, size);
        assert(bstree_size(&tree) == size);
        bstree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_bstree_destroy(void)
{
        bstree_t tree;
        bstree_init(&tree, compare, free);
        size_t size = 6;
        fill(&tree, (int[]){5,4,1,7,6,8}, size);
        assert(bstree_size(&tree) == size);
        bstree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

static void fill(bstree_t *tree, int values[], size_t n)
{
        int *data = NULL;

        for (size_t i = 0; i < n; i++) {
                assert((data = (int *) malloc(sizeof(int))) != NULL);
                *data = values[i];
                bstree_insert(tree, (void *) data);
        }
}

static int compare(const void *value1, const void *value2)
{
        int v1 = *(int *) value1;
        int v2 = *(int *) value2;

        if (v1 < v2) {
                return -1;
        } else if (v1 > v2) {
                return 1;
        } else {
                return 0;
        }
}
