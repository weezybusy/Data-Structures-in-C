#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "bstree.h"

void test_bstree(void);
void test_bstree_init(void);
void test_bstree_destroy(void);
void test_bstree_insert(void);
void test_bstree_remove(void);

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
        printf("%-30s ok\n", __func__);
}

void test_bstree_destroy(void)
{
        printf("%-30s ok\n", __func__);
}

void test_bstree_insert(void)
{
        printf("%-30s ok\n", __func__);
}

void test_bstree_remove(void)
{
        printf("%-30s ok\n", __func__);
}
