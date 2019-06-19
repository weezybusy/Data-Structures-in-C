#include <stdlib.h>
#include <string.h>

#include "heap.h"

/* Define private macros used by the heap implementation. ----------------- */

#define heap_parent(npos) ((int ) (((npos) - 1) / 2))

#define heap_left(npos) (((npos) * 2) + 1)

#define heap_right(npos) (((npos) * 2) + 2)

/* Implementation. -------------------------------------------------------- */

void heap_init(heap_t *heap,
                int (*compare)(const void *value1, const void *value2),
                void (*destroy)(void *data))
{
        heap->size = 0;
        heap->compare = compare;
        heap->destroy = destroy;
        heap->tree = NULL;
}

void heap_destroy(heap_t *heap)
{
        if (heap->destroy != NULL) {
                for (size_t i = 0; i < heap->size; i++) {
                        // Call user-defined function to free allocated data.
                        heap->destroy(heap->tree[i]);
                }
        }

        // Free the storage allocated for heap.
        free(heap->tree);

        // No operations are allowed now, clear the structure.
        memset(heap, 0, sizeof(heap_t));
}

int heap_insert(heap_t *heap, const void *data)
{
        void *temp;
        int ipos;
        int ppos;

        // Allocate storage for the node.
        temp = (void **) realloc(heap->tree, (heap_size(heap) + 1) * sizeof (void *));
        if (temp == NULL) {
                return -1;
        } else {
                heap->tree = temp;
        }

        // Insert the node after the last node.
        heap->tree[heap_size(heap)] = (void *) data;

        // Heapify the tree by pushing the contents of the new node upward.
        ipos = heap_size(heap);
        ppos = heap_parent(ipos);

        while (ipos > 0 && heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0) {
                // Swap the contents of the current node and its parent.
                temp = heap->tree[ppos];
                heap->tree[ppos] = heap->tree[ipos];
                heap->tree[ipos] = temp;

                // Move up one level in the tree to continue heapifying.
                ipos = ppos;
                ppos = heap_parent(ipos);
        }

        // Adjust the size of the heap to account for the inserted node.
        heap->size++;

        return 0;
}

int heap_extract(heap_t *heap, void **data)
{
        return 0;
}
