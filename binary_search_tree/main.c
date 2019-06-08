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
//static void fill(bstree_t *tree, int values[], size_t n);

int main(void)
{
        test_bstree();
        return EXIT_SUCCESS;
}

void test_bstree(void)
{
        test_bstree_init();
        //test_bstree_destroy();
        test_bstree_insert();
        //test_bstree_remove();
}

void test_bstree_init(void)
{
        bstree_t tree;
        bstree_init(&tree, compare, free);
        assert(tree.size == 0);
        assert(tree.compare == compare);
        assert(tree.destroy == free);
        assert(tree.root == NULL);

        printf("%-30s ok\n", __func__);
}

void test_bstree_insert(void)
{
        bstree_t tree;
        bstree_init(&tree, compare, free);

        assert(bstree_size(&tree) == 0);

        int *data = (int *) malloc(sizeof(int));
        assert(data != NULL);
        *data = 5;
        bstree_insert(&tree, (void *) data);
        assert(bstree_size(&tree) == 1);
        // Add more values.

        bstree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_bstree_remove(void)
{
        printf("%-30s ok\n", __func__);
}

void test_bstree_destroy(void)
{
        bstree_t tree;
        bstree_init(&tree, compare, free);
        //fill(&tree, [values], size);

        bstree_destroy(&tree);
        printf("%-30s ok\n", __func__);
}

//static void fill(bstree_t *tree, int values[], size_t n)
//{
//        return;
//}

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
