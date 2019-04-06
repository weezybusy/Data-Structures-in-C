#ifndef SET_H
#define SET_H

#include <stdlib.h>

#include "list.h"

/* Implement sets as linked lists. ---------------------------------------- */
typedef list_t set_t;

/* Public Interface. ------------------------------------------------------ */

void set_init(set_t *set,
                int (*compare)(const void *value1, const void *value2),
                void (*destroy)(void *data));

#define set_destroy list_destroy

int set_insert(set_t *set, const void *data);

int set_remove(set_t *set, void **data);

int set_union(set_t *setu, const set_t *set1, const set_t *set2);

int set_intersection(set_t *seti, const set_t *set1, const set_t *set2);

int set_difference(set_t *setd, const set_t *set1, const set_t *set2);

int set_is_member(const set_t *set, const void *data);

int set_is_subset(const set_t *set1, const set_t *set2);

int set_is_equal(const set_t *set1, const set_t *set2);

#define set_size(set) ((set)->size)

#endif
