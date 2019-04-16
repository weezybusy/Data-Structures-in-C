#include <stdlib.h>
#include <string.h>

#include "ohtbl.h"

/* Reserve a sentinel memory address for vacated elements. */
static char vacated;

int ohtbl_init(ohtbl_t *htbl, size_t positions,
                int (*h1)(const void *key),
                int (*h2)(const void *key),
                int (*compare)(const void *value1, const void *value2),
                void (*destroy)(void *data))
{
        htbl->table = (void **) malloc(positions * sizeof(void *));
        if (htbl->table == NULL) {
                return -1;
        }
        htbl->positions = positions;
        for (size_t i = 0; i < htbl->positions; i++) {
                htbl->table[i] = NULL;
        }
        htbl->vacated = &vacated;
        htbl->h1 = h1;
        htbl->h2 = h2;
        htbl->compare = compare;
        htbl->destroy = destroy;
        htbl->size = 0;

        return 0;
}

void ohtbl_destroy(ohtbl_t *htbl)
{
        if (htbl->destroy != NULL) {
                for (size_t i = 0; i < htbl->positions; i++) {
                        if (htbl->table[i] != NULL &&
                                        htbl->table[i] != htbl->vacated) {
                                htbl->destroy(htbl->table[i]);
                        }
                }
        }
        free(htbl->table);
        memset(htbl, 0, sizeof(ohtbl_t));
}

int ohtbl_insert(ohtbl_t *htbl, const void *data)
{
        if (htbl->size == htbl->positions) {
                return -1;
        }

        void *tmp = (void *) data;
        if (ohtbl_lookup(htbl, (void **) &tmp) == 0) {
                return 1;
        }

        // Use double hashing to hash the key.
        for (size_t i = 0; i < htbl->positions; i++) {
                size_t pos = (htbl->h1(data) + (i * htbl->h2(data))) % htbl->positions;
                if (htbl->table[pos] == NULL || htbl->table[pos] == htbl->vacated) {
                        // Insert the data into the table.
                        htbl->table[pos] = (void *) data;
                        htbl->size++;
                        return 0;
                }
        }
        // Return that the hash functions were selected incorrectly.
        return -1;
}

int ohtbl_remove(ohtbl_t *htbl, void **data)
{
        // Use double hashing to hash key.
        for (size_t i = 0; i < htbl->positions; i++) {
                size_t pos = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;
                if (htbl->table[pos] == NULL) {
                        // Return that data was not found.
                        return -1;
                } else if (htbl->table[pos] == htbl->vacated) {
                        // Search beyond vacated positions.
                        continue;
                } else if (htbl->compare(htbl->table[pos], *data) == 0) {
                        // Pass back the data from the table.
                        *data = htbl->table[pos];
                        htbl->table[pos] = htbl->vacated;
                        htbl->size--;
                        return 0;
                }
        }
        // Return that the data was not found.
        return -1;
}

int ohtbl_lookup(const ohtbl_t *htbl, void **data)
{
        // Use double hashing to hash key.
        for (size_t i = 0; i < htbl->positions; i++) {
                size_t pos = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;
                if (htbl->table[pos] == NULL) {
                        // Return that data was not found.
                        return -1;
                } else if (htbl->table[pos] == htbl->vacated) {
                        // Search beyond vacated positions.
                        continue;
                } else if (htbl->compare(htbl->table[pos], *data) == 0) {
                        // Pass back the data from the table.
                        *data = htbl->table[pos];
                        return 0;
                }
        }
        // Return that the data was not found.
        return -1;
}
