#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/* Define structure for linked list elements. ----------------------------- */
typedef struct _node {
        void *data;
        struct _node *next;
} node_t;

/* Define structure for linked lists. ------------------------------------- */
typedef struct _list {
        size_t size;
        int (*compare)(const void *value1, const void *value2);
        void (*destroy)(void *data);
        node_t *head;
        node_t *tail;
} list_t;

/* Public interface. ------------------------------------------------------ */

void list_init(list_t *list, void (*destroy)(void *data));

void list_destroy(list_t *list);

int list_insert_next(list_t *list, node_t *node, const void *data);

int list_remove_next(list_t *list, node_t *node, void **data);

/* Macros. ---------------------------------------------------------------- */

#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

#define list_is_head(list, node) ((node) == (list)->head ? 1 : 0)

#define list_is_tail(list, node) ((node) == (list)->tail ? 1 : 0)

#define list_data(node) ((node)->data)

#define list_next(node) ((node)->next)

#endif
