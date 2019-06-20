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
static void sort(int array[], size_t size);

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
        int values[] = { 19, 9, 7, 15, 25, 20, 17, 10, 22, 12 };
        size_t size = sizeof values / sizeof values[0];

        fill(&heap, values, size);
        assert(heap_size(&heap) == size);
        assert(cmp_vals(&heap, values, size) == 0);
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
        int values[] = { 19, 9, 7, 15, 25, 20, 17, 10, 22, 12 };
        size_t size = sizeof values / sizeof values[0];

        fill(&heap, values, size);
        assert(heap_size(&heap) == size);
        assert(cmp_vals(&heap, values, size) == 0);
        heap_destroy(&heap);

        printf("%-30s ok\n", __func__);
}

void test_heap_extract(void)
{
        printf("%-30s ok\n", __func__);
}

static int compare(const void *value1, const void *value2)
{
        int v1 = *(int *) value1;
        int v2 = *(int *) value2;

        if (v1 < v2) {
                return -1;
        } else if (v2 > v1) {
                return 1;
        } else {
                return 0;
        }
}

static void fill(heap_t *heap, int values[], size_t size)
{
        int *data;
        for (size_t i = 0; i < size; i++) {
                data = (int *) malloc(sizeof(int));
                assert(data != NULL);
                *data = values[i];
                heap_insert(heap, data);
        }
}

static int cmp_vals(const heap_t *heap, int values[], size_t size)
{
        int heap_dup[size];

        // Copy heap values to array.
        for (size_t i = 0; i < size; i++) {
                heap_dup[i] = *(int *) heap->tree[i];
        }

        // Sort arrays.
        sort(heap_dup, size);
        sort(values, size);

        // Compare arrays.
        for (size_t i = 0; i < size; i++) {
                if (heap_dup[i] != values[i]) {
                        return -1;
                }
        }

        return 0;
}

static void sort(int array[], size_t size)
{
        size_t key;
        int temp;

        for (size_t i = 0; i < size - 1; i++) {
                key = i;
                for (size_t j = i + 1; j < size; j++) {
                        if (array[j] < array[key]) {
                                key = j;
                        }
                }
                if (key != i) {
                        temp = array[i];
                        array[i] = array[key];
                        array[key] = temp;
                }
        }
}
