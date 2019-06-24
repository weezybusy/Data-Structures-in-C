#include <stdlib.h>
#include <string.h>

#include "heap.h"

/* Define private macros used by the heap implementation. ----------------- */

#define heap_parent(npos) ((int) (((npos) - 1) / 2))

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
        size_t ipos;
        size_t ppos;

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
        void *save;
        void *temp;
        size_t ipos;
        size_t lpos;
        size_t rpos;
        size_t mpos;

        // Do not allow extraction from an empty heap.
        if (heap_size(heap) == 0) {
                return -1;
        }

        // Extract the node at the top of the heap.
        *data = heap->tree[0];

        // Adjust the storage used by the heap.
        save = heap->tree[heap_size(heap) - 1];

        if (heap_size(heap) - 1 > 0) {
                temp = (void **) realloc(heap->tree, (heap_size(heap) - 1) * sizeof (void *));
                if (temp == NULL) {
                        return -1;
                } else {
                        heap->tree = temp;
                }

                // Adjust the size of the heap to account for the extracted node.
                heap->size--;
        } else {
                // Manage the heap when extracting the last node.
                free(heap->tree);
                heap->tree = NULL;
                heap->size = 0;
                return 0;
        }

        // Copy the last node to the top.
        heap->tree[0] = save;

        // Heapify the tree by pushing the contents of the new top downward.
        ipos = 0;

        while (1) {
                // Select the child to swap with the current node.
                lpos = heap_left(ipos);
                rpos = heap_right(ipos);

                if (lpos < heap_size(heap) &&
                                heap->compare(heap->tree[lpos], heap->tree[ipos]) > 0) {
                        mpos = lpos;
                } else {
                        mpos = ipos;
                }

                if (rpos < heap_size(heap) &&
                                heap->compare(heap->tree[rpos], heap->tree[mpos]) > 0) {
                        mpos = rpos;
                }

                // When mpos is ipos, the heap property has been restored.
                if (mpos == ipos) {
                        break;
                } else {
                        // Swap the contents of the current node and the selected child.
                        temp = heap->tree[mpos];
                        heap->tree[mpos] = heap->tree[ipos];
                        heap->tree[ipos] = temp;

                        // Move down one level in the tree to continue heapifying.
                        ipos = mpos;
                }
        }

        return 0;
}
