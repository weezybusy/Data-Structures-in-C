#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "ohtbl.h"

void test_ohtbl(void);
void test_ohtbl_insert(void);
void test_ohtbl_remove(void);
void test_ohtbl_lookup(void);

int main(void)
{
        test_ohtbl();
        return EXIT_SUCCESS;
}

void test_ohtbl(void)
{
        test_ohtbl_insert();
        test_ohtbl_remove();
        test_ohtbl_lookup();
}

void test_ohtbl_insert(void)
{
        printf("%-30s ok\n", __func__);
}

void test_ohtbl_remove(void)
{
        printf("%-30s ok\n", __func__);
}

void test_ohtbl_lookup(void)
{
        printf("%-30s ok\n", __func__);
}
