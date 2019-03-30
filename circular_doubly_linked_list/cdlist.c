#include <string.h>
#include <stdlib.h>

#include "cdlist.h"

void cdlist_init(cdlist_t *list, void (*destroy)(void *data))
{
        list->size = 0;
        list->compare = NULL;
        list->destroy = destroy;
        list->head = NULL;
}

void cdlist_destroy(cdlist_t *list)
{
        void *data = NULL;

        while (list->size > 0) {
                if (cdlist_remove(list, list->head, (void **) &data) == 0 &&
                                list->destroy != NULL) {
                        list->destroy(data);
                }
        }

        memset(list, 0, sizeof(cdlist_t));
}

int cdlist_insert_next(cdlist_t *list, cdnode_t *node, const void *data)
{
        if (node == NULL && list->size != 0) {
                return -1;
        }

        cdnode_t *new_node = (cdnode_t *) malloc(sizeof(cdnode_t));
        if (new_node == NULL) {
                return -1;
        }
        new_node->data = (void *) data;
        new_node->next = NULL;

        if (list->size == 0) {
                list->head = new_node;
                new_node->prev = new_node;
                new_node->next = new_node;
        } else {
                new_node->prev = node;
                new_node->next = node->next;
                node->next->prev = new_node;
                node->next = new_node;
        }

        list->size++;
        return 0;
}

int cdlist_insert_prev(cdlist_t *list, cdnode_t *node, const void *data)
{
        if (node == NULL && list->size != 0) {
                return -1;
        }

        cdnode_t *new_node = (cdnode_t *) malloc(sizeof(cdnode_t));
        if (new_node == NULL) {
                return -1;
        }
        new_node->data = (void *) data;
        new_node->next = NULL;

        if (list->size == 0) {
                list->head = new_node;
                new_node->prev = new_node;
                new_node->next = new_node;
        } else {
                new_node->prev = node->prev;
                new_node->next = node;
                node->prev->next = new_node;
                node->prev = new_node;
        }

        list->size++;
        return 0;
}

int cdlist_remove(cdlist_t *list, cdnode_t *node, void **data)
{
        if (node == NULL || list->size == 0) {
                return -1;
        }

        *data = node->data;
        node->prev->next = node->next;
        node->next->prev = node->prev;

        if (node == list->head) {
                list->head = node->next;
        }

        free(node);
        list->size--;

        return 0;
}
