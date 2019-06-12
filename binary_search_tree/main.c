#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "bstree.h"

void test_bstree(void);
void test_bstree_init(void);
void test_bstree_destroy(void);
void test_bstree_insert(void);
void test_stree_lookup(void);
void test_bstree_remove(void);

static int compare(const void *value1, const void *value2);
static void fill(bstree_t *tree, const int values[], const size_t n);

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
        test_bstree_lookup();
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
        size_t tree_size = 0;
        int *data = NULL;
        int value;

        bstree_init(&tree, compare, free);
        data = (int *) malloc(sizeof(int));
        assert(data != NULL);
        value = 5;
        *data = value;
        // Check return value is correct.
        assert(bstree_insert(&tree, (void *) data) == 0);
        tree_size++;
        // Check tree size.
        assert(bstree_size(&tree) == tree_size);
        // Check the data is correct.
        assert(*(int *) ((avlnode_t *) btree_data(btree_root(&tree)))->data == value);
        // Check the balance factor.
        assert(((avlnode_t *) btree_data(btree_root(&tree)))->factor == AVL_BALANCED);

        data = (int *) malloc(sizeof(int));
        assert(data != NULL);
        value = 4;
        *data = value;
        assert(bstree_insert(&tree, (void *) data) == 0);
        tree_size++;
        assert(bstree_size(&tree) == tree_size);
        assert(*(int *) ((avlnode_t *) btree_data(btree_left(btree_root(&tree))))->data == value);
        assert(((avlnode_t *) btree_data(btree_root(&tree)))->factor == AVL_LEFT_HEAVY);
        assert(((avlnode_t *) btree_data(btree_left(btree_root(&tree))))->factor == AVL_BALANCED);

        data = (int *) malloc(sizeof(int));
        assert(data != NULL);
        value = 6;
        *data = value;
        assert(bstree_insert(&tree, (void *) data) == 0);
        tree_size++;
        assert(bstree_size(&tree) == tree_size);
        assert(*(int *) ((avlnode_t *) btree_data(btree_right(btree_root(&tree))))->data == value);
        assert(((avlnode_t *) btree_data(btree_root(&tree)))->factor == AVL_BALANCED);
        assert(((avlnode_t *) btree_data(btree_left(btree_root(&tree))))->factor == AVL_BALANCED);

        // Check inserting the data which is already in.
        data = (int *) malloc(sizeof(int));
        assert(data != NULL);
        value = 6;
        *data = value;
        assert(bstree_insert(&tree, (void *) data) == 1);
        assert(bstree_size(&tree) == tree_size);
        free(data);

        bstree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_stree_lookup(void)
{
        // TODO: create tests for lookup.
        printf("%-30s ok\n", __func__);
}

void test_bstree_remove(void)
{
        bstree_t tree;
        int *data;
        const int values[] = { 9, 123, 41, 59, 7, 6, 1, 34 };
        const size_t tree_size = sizeof(values)/sizeof(values[0]);

        // Check removing from the empty tree.
        bstree_init(&tree, compare, free);
        int value = 7;
        assert(bstree_remove(&tree, &value) == -1);
        bstree_destroy(&tree);

        // Check removing an element which is not in the tree.
        bstree_init(&tree, compare, free);
        fill(&tree, values, tree_size);
        assert(bstree_size(&tree) == tree_size);
        data = (int *) malloc(sizeof(int));
        assert(data != NULL);
        *data = 100;
        assert(bstree_remove(&tree, data) == -1);
        free(data);
        bstree_destroy(&tree);

        // Check removing elements from the tree which is not empty.
        bstree_init(&tree, compare, free);
        fill(&tree, values, tree_size);
        assert(bstree_size(&tree) == tree_size);

        // TODO: use bstree_lookup() for checking removed data.
        for (int i = tree_size - 1; i >= 0; i--) {
                assert(bstree_remove(&tree, &values[i]) == 0);
        }
        bstree_destroy(&tree);


        printf("%-30s ok\n", __func__);
}

void test_bstree_destroy(void)
{
        bstree_t tree;
        bstree_init(&tree, compare, free);
        const int values[] = { 5,4,1,7,6,8 };
        const size_t tree_size = sizeof(values)/sizeof(values[0]);
        fill(&tree, values, tree_size);
        assert(bstree_size(&tree) == tree_size);
        bstree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

static void fill(bstree_t *tree, const int values[], const size_t n)
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
