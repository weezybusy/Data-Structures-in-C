#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "chtbl.h"

int chtbl_init(chtbl_t *htbl, size_t buckets, int (*h)(const void *key),
                int (*compare)(const void *value1, const void *value2),
                void (*destroy)(void *data))
{
        htbl->table = (list_t *) malloc(buckets * sizeof(list_t));
        if (htbl->table == NULL) {
                return -1;
        }

        htbl->buckets = buckets;
        for (size_t i = 0; i < htbl->buckets; i++) {
                list_init(&htbl->table[i], destroy);
        }
        htbl->h = h;
        htbl->compare = compare;
        htbl->destroy = destroy;
        htbl->size = 0;

        return 0;
}

void chtbl_destroy(chtbl_t *htbl)
{
        // Destroy buckets.
        for (size_t i = 0; i < htbl->size; i++) {
                list_destroy(&htbl->table[i]);
        }

        // Free the storage allocated for the hash table.
        free(htbl->table);

        // No operations are alowed now, clear the structure as a protection.
        memset(htbl, 0, sizeof(chtbl_t));
}

int chtbl_insert(chtbl_t *htbl, const void *data)
{
        void *tmp;
        size_t bucket;
        int retval;

        // Do nothing if the data is already in the table.
        tmp = (void *) data;
        if (chtbl_lookup(htbl, &tmp) == 0) {
                return 1;
        }

        // Hash the key.
        bucket = htbl->h(data) % htbl->buckets;

        // Insert the data into the bucket.
        retval = list_insert_next(&htbl->table[bucket], NULL, data);
        if (retval == 0) {
                htbl->size++;
        }

        return retval;
}

int chtbl_remove(chtbl_t *htbl, void **data)
{
        node_t *curr;
        node_t *prev;
        size_t bucket;

        // Hash the key.
        bucket = htbl->h(*data) % htbl->buckets;

        // Search for the data in the bucket.
        prev = NULL;
        for (curr = list_head(&htbl->table[bucket]); curr != NULL;
                        curr = list_next(curr)) {
                if (htbl->compare(*data ,list_data(curr)) == 0) {
                        // Remove the data from the bucket.
                        if (list_remove_next(&htbl->table[bucket],
                                                prev, data) == 0) {
                                htbl->size--;
                                return 0;
                        } else {
                                return -1;
                        }
                }
                prev = curr;
        }
        return -1;
}

int chtbl_lookup(const chtbl_t *htbl, void **data)
{
        node_t *node;
        size_t bucket;

        // Hash the key.
        bucket = htbl->h(*data) % htbl->buckets;

        // Search for the data in the bucket.
        for (node = list_head(&htbl->table[bucket]); node != NULL;
                        node = list_next(node)) {
                if (htbl->compare(*data ,list_data(node)) == 0) {
                        *data = list_data(node);
                        return 0;
                }
        }
        return -1;
}
