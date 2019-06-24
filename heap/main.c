#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

void test_heap(void);
void test_heap_init(void);
void test_heap_destroy(void);
void test_heap_insert(void);
void test_heap_extract(void);

static int compare(const void *value1, const void *value2);
static void fill(heap_t *heap, int values[], size_t size);
static int cmp_vals(const heap_t *heap, int values[], size_t size);

int main(void)
{
        test_heap();
        return EXIT_SUCCESS;
}

void test_heap(void)
{
        test_heap_init();
        test_heap_destroy();
        test_heap_insert();
        test_heap_extract();
}

void test_heap_init(void)
{
        heap_t heap;
        heap_init(&heap, compare, free);

        assert(heap.size == 0);
        assert(heap.tree == NULL);
        assert(heap.compare == compare);
        assert(heap.destroy == free);

        printf("%-30s ok\n", __func__);
}

void test_heap_destroy(void)
{
        heap_t heap;

        // Check destroying an empty heap.
        heap_init(&heap, compare, free);
        heap_destroy(&heap);
        assert(heap.size == 0);
        assert(heap.tree == NULL);
        assert(heap.compare == NULL);
        assert(heap.destroy == NULL);

        // Check destroying heap with some values.
        heap_init(&heap, compare, free);
        int orig_values[] = { 19, 9, 7, 15, 25, 20, 17, 10, 22, 12 };
        int heap_values[] = { 25, 22, 20, 19, 15, 7, 17, 9, 10, 12 };
        size_t size = sizeof orig_values / sizeof orig_values[0];

        fill(&heap, orig_values, size);
        assert(heap_size(&heap) == size);
        assert(cmp_vals(&heap, heap_values, size) == 0);
        heap_destroy(&heap);
        assert(heap.size == 0);
        assert(heap.tree == NULL);
        assert(heap.compare == NULL);
        assert(heap.destroy == NULL);

        printf("%-30s ok\n", __func__);
}

void test_heap_insert(void)
{
        heap_t heap;
        heap_init(&heap, compare, free);
        int orig_values[] = { 19, 9, 7, 15, 25, 20, 17, 10, 22, 12 };
        int heap_values[] = { 25, 22, 20, 19, 15, 7, 17, 9, 10, 12 };
        size_t size = sizeof orig_values / sizeof orig_values[0];
        int *data = NULL;

        // Fill the heap.
        for (size_t i = 0; i < size; i++) {
                data = (int *) malloc(sizeof(int));
                assert(data != NULL);
                *data = orig_values[i];
                heap_insert(&heap, data);
        }
        // Check the sizes match.
        assert(heap_size(&heap) == size);
        // Check the values match.
        assert(cmp_vals(&heap, heap_values, size) == 0);
        // Check that largest element is on the top of the heap.
        assert(*(int *) heap.tree[0] == 25);
        heap_destroy(&heap);

        printf("%-30s ok\n", __func__);
}

void test_heap_extract(void)
{
        heap_t heap;
        heap_init(&heap, compare, free);
        int orig_values[] = { 19, 9, 7, 15, 25 };
        int heap_values[] = { 25, 19, 7, 9, 15 };
        size_t size = sizeof orig_values / sizeof orig_values[0];
        int *data = NULL;

        fill(&heap, orig_values, size);
        assert(heap_size(&heap) == size);
        assert(cmp_vals(&heap, heap_values, size) == 0);

        for (size_t i = 0; i < size; i++) {
                heap_extract(&heap, (void **) &data);
                for (size_t j = 0; j < size - i - 1; j++) {
                        printf(" %d", *(int *) heap.tree[j]);
                }
                printf("\n");
                // TODO: make sense to create is_heapified() function to
                // check heap state after each extraction.
                free(data);
        }
        heap_destroy(&heap);

        printf("%-30s ok\n", __func__);
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

static void fill(heap_t *heap, int values[], size_t size)
{
        int *data = NULL;
        for (size_t i = 0; i < size; i++) {
                data = (int *) malloc(sizeof(int));
                assert(data != NULL);
                *data = values[i];
                heap_insert(heap, data);
        }
}

static int cmp_vals(const heap_t *heap, int values[], size_t size)
{
        for (size_t i = 0; i < size; i++) {
                if (*(int *) heap->tree[i] != values[i]) {
                        return -1;
                }
        }
        return 0;
}
