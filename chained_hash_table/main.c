#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "chtbl.h"

#define BUCKETS 7

void test_chtbl(void);
void test_chtbl_insert(void);
void test_chtbl_remove(void);
void test_chtbl_lookup(void);

int compare(const void *value1, const void *value2);
int h(const void *key);
void display_chtbl(const chtbl_t *htbl);
void display_list(const list_t *list);
void chtbl_fill(chtbl_t *htbl, size_t size);

int main(void)
{
        test_chtbl();
        return EXIT_SUCCESS;
}

void test_chtbl(void)
{
        test_chtbl_insert();
        //test_chtbl_remove();
        //test_chtbl_lookup();
}

void test_chtbl_insert(void)
{
        chtbl_t htbl;
        int *data = NULL;
        size_t size = BUCKETS - 2;

        // Check insertion of smaller amount of elements than buckets.
        chtbl_fill(&htbl, size);
        assert(htbl.size == size);
        chtbl_destroy(&htbl);

        // Check insertion of the element already in table.
        chtbl_fill(&htbl, size);
        assert(htbl.size == size);
        data = (int *) malloc(sizeof(int));
        assert(data != NULL);
        *data = size - 1;
        assert(chtbl_insert(&htbl, (void *) data) == 1);
        assert(htbl.size == size);
        free(data);
        chtbl_destroy(&htbl);

        // Check insertion of exceeding amount of elements.
        size = 2 * BUCKETS;
        chtbl_fill(&htbl, size);
        assert(htbl.size == size);
        chtbl_destroy(&htbl);

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

int compare(const void *value1, const void *value2)
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

int h(const void *key)
{
        int value = *(int *) key;
        return value % BUCKETS;
}

void display_chtbl(const chtbl_t *htbl)
{
        for (size_t i = 0; i < BUCKETS; i++) {
                printf("bucket %zu:", i);
                display_list(&htbl->table[i]);
        }
}

void display_list(const list_t *list)
{
        if (list->head == NULL) {
                printf(" empty");
        }
        for (node_t *node = list->head; node != NULL; node = node->next) {
                printf(" %d", *(int *) node->data);
        }
        putchar('\n');
}

void chtbl_fill(chtbl_t *htbl, size_t size)
{
        int *data = NULL;
        chtbl_init(htbl, BUCKETS, h, compare, free);
        for (size_t i = 0; i < size; i++) {
                data = (int *) malloc(sizeof(int));
                assert(data != NULL);
                *data = i;
                assert(chtbl_insert(htbl, (void *) data) == 0);
        }
}
