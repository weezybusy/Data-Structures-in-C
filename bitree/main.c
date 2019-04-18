#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//'#include "bitree.h"

void test_bitree(void);
void test_bitree_insert_left(void);
void test_bitree_insert_right(void);
void test_bitree_remove_left(void);
void test_bitree_remove_right(void);

int main(void)
{
        test_bitree();
        return EXIT_SUCCESS;
}

void test_bitree(void)
{
        test_bitree_insert_left();
        test_bitree_insert_right();
        test_bitree_remove_left();
        test_bitree_remove_right();
}

void test_bitree_insert_left(void)
{
        printf("%-30s ok\n", __func__);
}

void test_bitree_insert_right(void)
{
        printf("%-30s ok\n", __func__);
}

void test_bitree_remove_left(void)
{
        printf("%-30s ok\n", __func__);
}

void test_bitree_remove_right(void)
{
        printf("%-30s ok\n", __func__);
}
