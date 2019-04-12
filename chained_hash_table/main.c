#include <stdio.h>
#include <stdlib.h>

//#include "chtbl.h"

void test_chtbl(void);
void test_chtbl_insert(void);
void test_chtbl_remove(void);
void test_chtbl_lookup(void);

int main(void)
{
        test_chtbl();
        return EXIT_SUCCESS;
}

void test_chtbl(void)
{
        test_chtbl_insert();
        test_chtbl_remove();
        test_chtbl_lookup();
}

void test_chtbl_insert(void)
{
        printf("%-30s ok\n", __func__);
}

void test_chtbl_remove(void)
{
        printf("%-30s ok\n", __func__);
}

void test_chtbl_lookup(void)
{
        printf("%-30s ok\n", __func__);
}
