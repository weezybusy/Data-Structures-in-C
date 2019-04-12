#ifndef CHTBL_H
#define CHTBL_H

#include <stdlib.h>

#include "list.h"

typedef struct chtbl {
        size_t buckets;
        int (*h)(const void *key);
        int (*compare)(const void *value1, const void *value2);
        void (*destroy)(void *data);
        size_t size;
        list_t *table;
} chtbl_t;

/* Public Interface. ------------------------------------------------------ */

int chtbl_init(chtbl_t *htbl, size_t buckets, int (*h)(const void *key),
                int (*compare)(const void *value1, const void *value2),
                void (*destroy)(void *data));

void chtbl_destroy(chtbl_t *htbl);

int chtbl_insert(chtbl_t *htbl, const void *data);

int chtbl_remove(chtbl_t *htbl, void **data);

int chtbl_lookup(const chtbl_t *htbl, void **data);

/* Macros. ---------------------------------------------------------------- */

#define chtbl_size(htbl) ((htbl)->size)

#endif
