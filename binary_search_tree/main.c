#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "bstree.h"

void test_bstree(void);
void test_bstree_init(void);
void test_bstree_destroy(void);
void test_bstree_insert(void);
void test_bstree_lookup(void);
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
        assert(bstree_insert(&tree, data) == 0);
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
        assert(bstree_insert(&tree, data) == 0);
        tree_size++;
        assert(bstree_size(&tree) == tree_size);
        assert(*(int *) ((avlnode_t *) btree_data(btree_left(btree_root(&tree))))->data == value);
        assert(((avlnode_t *) btree_data(btree_root(&tree)))->factor == AVL_LEFT_HEAVY);
        assert(((avlnode_t *) btree_data(btree_left(btree_root(&tree))))->factor == AVL_BALANCED);

        data = (int *) malloc(sizeof(int));
        assert(data != NULL);
        value = 6;
        *data = value;
        assert(bstree_insert(&tree, data) == 0);
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
        assert(bstree_insert(&tree, data) == 1);
        assert(bstree_size(&tree) == tree_size);
        free(data);

        data = NULL;
        bstree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_bstree_lookup(void)
{
        bstree_t tree;
        bstree_init(&tree, compare, free);
        int values[] = { 9, 123, 41, 59, 7, 6, 1, 34 };
        const size_t tree_size = sizeof values / sizeof values[0];
        void *data = NULL;

        fill(&tree, values, tree_size);
        assert(tree.size == tree_size);

        // Check lookup of data not in the tree.
        int value = 1000;
        data = &value;
        assert(bstree_lookup(&tree, &data) == -1);

        // Check lookup of data in the tree.
        for (size_t i = 0; i < tree_size; i++) {
                data = &values[i];
                assert(bstree_lookup(&tree, &data) == 0);
                assert(*(int *) data == values[i]); 
        }
        data = NULL;
        bstree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_bstree_remove(void)
{
        bstree_t tree;
        int *data = NULL;
        int values[] = { 9, 123, 41, 59, 7, 6, 1, 34 };
        const size_t tree_size = sizeof values / sizeof values[0];

        // Check removing from the empty tree.
        bstree_init(&tree, compare, free);
        assert(bstree_remove(&tree, &values[0]) == -1);
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
        data = NULL;
        bstree_destroy(&tree);

        // Check removing elements from the tree which is not empty.
        bstree_init(&tree, compare, free);
        fill(&tree, values, tree_size);
        assert(bstree_size(&tree) == tree_size);
        for (size_t i = 0; i < tree_size; i++) {
                data = &values[i];
                // Check the data has been removed successfully.
                assert(bstree_remove(&tree, data) == 0);
                // Check there is no data after repeated search.
                assert(bstree_lookup(&tree, (void **) &data) == -1);
        }
        // Check the size is the same (removed elements are marked as hidden).
        assert(bstree_size(&tree) == tree_size);
        data = NULL;
        bstree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_bstree_destroy(void)
{
        bstree_t tree;
        bstree_init(&tree, compare, free);
        const int values[] = { 5, 4, 1, 7, 6, 8 };
        const size_t tree_size = sizeof values / sizeof values[0];
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
        data = NULL;
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
