#ifndef CDLIST_H
#define CDLIST_H

typedef struct _cdnode {
        void *data;
        struct _cdnode *next;
        struct _cdnode *prev;
} cdnode_t;

typedef struct _cdlist {
        size_t size;
        int (*compare)(void *value1, void *value2);
        void (*destroy)(void *data);
        cdnode_t *head;
} cdlist_t;

/* Public interface. ------------------------------------------------------ */

void cdlist_init(cdlist_t *list, void (*destroy)(void *data));

void cdlist_destroy(cdlist_t *list);

int cdlist_insert_prev(cdlist_t *list, cdnode_t *node, const void *data);

int cdlist_insert_next(cdlist_t *list, cdnode_t *node, const void *data);

int cdlist_remove(cdlist_t *list, cdnode_t *node, void **data);

/* Macros. ---------------------------------------------------------------- */

#define cdlist_size(list) ((list)->size)

#define cdlist_head(list) ((list)->head)

#define cdlist_prev(node) ((node)->prev)

#define cdlist_next(node) ((node)->next)

#define cdlist_data(node) ((node)->data)

#define cdlist_is_head(list, node) ((list)->head == node ? 1 : 0)

#endif
