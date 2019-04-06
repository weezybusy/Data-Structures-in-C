#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "set.h"

void set_init(set_t *set,
                int (*compare)(const void *value1, const void *value2),
                void (*destroy)(void *data))
{
        list_init(set, destroy);
        set->compare = compare;
}

int set_insert(set_t *set, const void *data)
{
        if (set_is_member(set, data)) {
                return 1;
        }
        return list_insert_next(set, list_tail(set), data);
}

int set_remove(set_t *set, void **data)
{
        node_t *prev = NULL;
        node_t *node = list_head(set);

        while (node != NULL) {
                if (set->compare(*data, list_data(node)) == 0) {
                        break;
                }
                prev = node;
                node = list_next(node);
        }

        if (node == NULL) {
                return -1;
        }

        return list_remove_next(set, prev, data);
}

int set_union(set_t *setu, const set_t *set1, const set_t *set2)
{
        node_t *node = NULL;
        void *data = NULL;

        set_init(setu, set1->compare, NULL);

        for (node = list_head(set1); node != NULL; node = list_next(node)) {
                data = list_data(node);
                if (list_insert_next(setu, list_tail(setu), data) != 0) {
                        set_destroy(setu);
                        return -1;
                }
        }

        for (node = list_head(set2); node != NULL; node = list_next(node)) {
                if (set_is_member(set1, list_data(node))) {
                        continue;
                } 
                data = list_data(node);
                if (list_insert_next(setu, list_tail(setu), data) != 0) {
                        set_destroy(setu);
                        return -1;
                }
        }

        return 0;
}

int set_intersection(set_t *setu, const set_t *set1, const set_t *set2)
{
        void *data = NULL;
        set_init(setu, set1->compare, NULL);

        for (node_t *node = list_head(set1); node != NULL; node = list_next(node)) {
                data = list_data(node);
                if (set_is_member(set2, data)) {
                        if (list_insert_next(setu, list_tail(setu), data) != 0) {
                                set_destroy(setu);
                                return -1;
                        }
                }
        }

        return 0;
}

int set_difference(set_t *setd, const set_t *set1, const set_t *set2)
{
        void *data = NULL;
        set_init(setd, set1->compare, NULL);

        for (node_t *node = list_head(set1); node != NULL; node = list_next(node)) {
                data = list_data(node);
                if (!set_is_member(set2, data)) {
                        if (list_insert_next(setd, list_tail(setd), data) != 0) {
                                set_destroy(setd);
                                return -1;
                        }
                }
        }

        return 0;
}

int set_is_member(const set_t *set, const void *data)
{
        for (node_t *node = list_head(set); node != NULL; node = list_next(node)) {
                if (set->compare(list_data(node), data) == 0) {
                        return 1;
                }
        }
        return 0;
}

int set_is_subset(const set_t *set1, const set_t *set2)
{
        if (set_size(set1) > set_size(set2)) {
                return 0;
        }

        for (node_t *node = list_head(set1); node != NULL; node = list_next(node)) {
                if (!set_is_member(set2, list_data(node))) {
                        return 0;
                }
        }

        return 1;
}

int set_is_equal(const set_t *set1, const set_t *set2)
{
        if (set_size(set1) != set_size(set2)) {
                return 0;
        }

        return set_is_subset(set1, set2);
}
