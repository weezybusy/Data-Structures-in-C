#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "ohtbl.h"

#define BUCKETS 7

void test_ohtbl(void);
void test_ohtbl_insert(void);
void test_ohtbl_remove(void);
void test_ohtbl_lookup(void);

int h1(const void *key);
int h2(const void *key);
int compare(const void *value1, const void *value2);
void ohtbl_fill(ohtbl_t *htbl, size_t size);

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
        int *ptr;
        int *tmp;
        int val;
        size_t size;

        // Check inserting into the empty table.
        ohtbl_t htbl;
        ohtbl_init(&htbl, BUCKETS, h1, h2, compare, free);
        assert(htbl.size == 0);
        size = htbl.size;
        ptr = NULL;
        tmp = NULL;
        val = 11;
        assert((ptr = (int *) malloc(sizeof(int))) != NULL);
        *ptr = val;
        assert(ohtbl_insert(&htbl, (void *) ptr) == 0);
        assert(htbl.size == ++size);
        tmp = ptr;
        assert(ohtbl_lookup(&htbl, (void **) &tmp) == 0);
        assert(*tmp == val);
        ohtbl_destroy(&htbl);

        // Insert elements without exceeding number of buckets.
        ohtbl_init(&htbl, BUCKETS, h1, h2, compare, free);
        assert(htbl.size == 0);
        size = htbl.size;
        ptr = NULL;
        tmp = NULL;
        for (int i = 0; i < BUCKETS - 1; i++) {
                assert((ptr = (int *) malloc(sizeof(int))) != NULL);
                *ptr = i;
                assert(ohtbl_insert(&htbl, (void *) ptr) == 0);
                assert(htbl.size == ++size);
                tmp = ptr;
                assert(ohtbl_lookup(&htbl, (void **) &tmp) == 0);
                assert(*tmp == i);
        }
        ohtbl_destroy(&htbl);

        // Insert elements exceeding number of buckets.
        ohtbl_init(&htbl, BUCKETS, h1, h2, compare, free);
        assert(htbl.size == 0);
        size = htbl.size;
        ptr = NULL;
        tmp = NULL;
        for (int i = 0; i < BUCKETS; i++) {
                assert((ptr = (int *) malloc(sizeof(int))) != NULL);
                *ptr = i;
                assert(ohtbl_insert(&htbl, (void *) ptr) == 0);
                assert(htbl.size == ++size);
                tmp = ptr;
                assert(ohtbl_lookup(&htbl, (void **) &tmp) == 0);
                assert(*tmp == i);
        }

        // Add exceeding elements.
        val = 11;
        assert((ptr = (int *) malloc(sizeof(int))) != NULL);
        *ptr = val;
        assert(ohtbl_insert(&htbl, (void *) ptr) == -1);
        assert(htbl.size == size);
        free(ptr);

        val = 22;
        assert((ptr = (int *) malloc(sizeof(int))) != NULL);
        *ptr = val;
        assert(ohtbl_insert(&htbl, (void *) ptr) == -1);
        assert(htbl.size == size);
        free(ptr);
        ohtbl_destroy(&htbl);

        printf("%-30s ok\n", __func__);
}

void test_ohtbl_remove(void)
{
        ohtbl_t htbl;
        int *ptr;
        int *tmp;
        int val;

        // Check removing from the empty table.
        ohtbl_init(&htbl, BUCKETS, h1, h2, compare, free);
        assert(htbl.size == 0);
        assert((ptr = (int *) malloc(sizeof(int))) != NULL);
        val = 11;
        *ptr = val;
        tmp = ptr;
        assert(ohtbl_remove(&htbl, (void **) &tmp) == -1);
        free(ptr);
        ohtbl_destroy(&htbl);

        // Remove every element from the full table.
        ohtbl_init(&htbl, BUCKETS, h1, h2, compare, free);
        assert(htbl.size == 0);
        ptr = NULL;
        tmp = NULL;
        ohtbl_fill(&htbl, BUCKETS);
        assert(htbl.size == BUCKETS);
        for (int i = 0; i < BUCKETS; i++) {
                assert((ptr = (int *) malloc(sizeof(int))) != NULL);
                *ptr = i;
                tmp = ptr;
                assert(ohtbl_remove(&htbl, (void **) &tmp) == 0);
                assert(htbl.size == (size_t) BUCKETS - i - 1);
                assert(*tmp == i);
                free(ptr);
                free(tmp);
        }
        assert(htbl.size == 0);
        ohtbl_destroy(&htbl);

        printf("%-30s ok\n", __func__);
}

void test_ohtbl_lookup(void)
{
        ohtbl_t htbl;
        int *ptr;
        int *tmp;
        int val;

        // Check lookup of the element in the empty table.
        ohtbl_init(&htbl, BUCKETS, h1, h2, compare, free);
        assert(htbl.size == 0);
        assert((ptr = (int *) malloc(sizeof(int))) != NULL);
        val = 11;
        *ptr = val;
        tmp = ptr;
        assert(ohtbl_lookup(&htbl, (void **) &tmp) == -1);
        free(ptr);
        ohtbl_destroy(&htbl);

        // Lookup of every element in the full table.
        ohtbl_init(&htbl, BUCKETS, h1, h2, compare, free);
        assert(htbl.size == 0);
        ptr = NULL;
        tmp = NULL;
        ohtbl_fill(&htbl, BUCKETS);
        assert(htbl.size == BUCKETS);
        for (int i = 0; i < BUCKETS; i++) {
                assert((ptr = (int *) malloc(sizeof(int))) != NULL);
                *ptr = i;
                tmp = ptr;
                assert(ohtbl_lookup(&htbl, (void **) &tmp) == 0);
                assert(htbl.size == BUCKETS);
                assert(*tmp == i);
                free(ptr);
        }
        ohtbl_destroy(&htbl);

        printf("%-30s ok\n", __func__);
}

int h1(const void *key)
{
        assert(key != NULL);
        return *(int *) key % BUCKETS;
}

int h2(const void *key)
{
        assert(key != NULL);
        return 1 + (*(int *) key % (BUCKETS - 2));
}

int compare(const void *value1, const void *value2)
{
        assert(value1 != NULL);
        assert(value2 != NULL);

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

void ohtbl_fill(ohtbl_t *htbl, size_t size)
{
        int *ptr = NULL;
        for (size_t i = 0; i < size; i++) {
                assert((ptr = (int *) malloc(sizeof(int))) != NULL);
                *ptr = i;
                assert(ohtbl_insert(htbl, (void *) ptr) != -1);
        }
}
