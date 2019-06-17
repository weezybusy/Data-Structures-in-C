#ifndef HEAP_H
#define HEAP_H

/* Define a structure for heaps. ------------------------------------------ */

typedef struct heap_ {
        size_t size;
        int (*compare)(const void *value1, const void *value2);
        void (*destroy)(void *data);
        void **tree;
} heap_t;

/* Public interface. ------------------------------------------------------ */

void heap_init(heap_t *heap,
                int (*compare)(const void *value1, const void *value2),
                void (*destroy)(void *data));

void heap_destroy(heap_t *heap);

int heap_insert(heap_t *heap, const void *data);

int heap_extract(heap_t *heap, void **data);

/* Macros. ---------------------------------------------------------------- */

#define heap_size(heap) ((heap)->size)

#endif
