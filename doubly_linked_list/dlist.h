#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

typedef struct _dnode {
        void *data;
        struct _dnode *prev;
        struct _dnode *next;
} dnode_t;


typedef struct _dlist {
        size_t size;
        void (*destroy)(void *data);
        dnode_t *head;
        dnode_t *tail;
} dlist_t;

/* Public interface. -------------------------------------------------------*/

#define dlist_size(list) ((list)->size)

#define dlist_head(list) ((list)->head)

#define dlist_tail(list) ((list)->tail)

#define dlist_data(node) ((node)->data)

#define dlist_next(node) ((node)->next)

#define dlist_prev(node) ((node)->prev)

void dlist_init(dlist_t *list, void (*destroy)(void *data));

void dlist_destroy(dlist_t *list);

int dlist_insert_prev(dlist_t *list, dnode_t *node, const void *data);

int dlist_insert_next(dlist_t *list, dnode_t *node, const void *data);

int dlist_remove(dlist_t *list, dnode_t *node, void **data);

#endif
