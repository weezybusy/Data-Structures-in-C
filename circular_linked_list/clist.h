#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>

typedef struct _cnode {
        void *data;
        struct _cnode *next;
} cnode_t;

typedef struct _clist {
        size_t size;
        int (*compare)(void *value1, void *value2);
        void (*destroy)(void *data);
        cnode_t *head;
} clist_t;

/* Public interface. -------------------------------------------------------*/

#define clist_size(list) ((list)->size)

#define clist_head(list) ((list)->head)

#define clist_data(node) ((node)->data)

#define clist_next(node) ((node)->next)

void clist_init(clist_t *list, void (*destroy)(void *data));

void clist_destroy(clist_t *list);

int clist_insert_next(clist_t *list, cnode_t *node, const void *data);

int clist_remove_next(clist_t *list, cnode_t *node, void **data);

#endif
