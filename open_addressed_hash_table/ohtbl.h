#ifndef OHTBL_H
#define OHTBL_H

#include <stdlib.h>

typedef struct ohtbl {
        size_t positions;
        void *vacated;
        int (*h1)(const void *key);
        int (*h2)(const void *key);
        int (*compare)(const void *value1, const void *value2);
        void (*destroy)(void *data);
        size_t size;
        void **table;
} ohtbl_t;

/* Public Interface. ------------------------------------------------------ */

int ohtbl_init(ohtbl_t *htbl, size_t positions,
                int (*h1)(const void *key),
                int (*h2)(const void *key),
                int (*compare)(const void *value1, const void *value2),
                void (*destroy)(void *data));

void ohtbl_destroy(ohtbl_t *htbl);

int ohtbl_insert(ohtbl_t *htbl, const void *data);

int ohtbl_remove(ohtbl_t *htbl, void **data);

int ohtbl_lookup(const ohtbl_t *htbl, void **data);

/* Macros. ---------------------------------------------------------------- */

#define ohtbl_size(htbl) ((htbl)->size)

#endif
