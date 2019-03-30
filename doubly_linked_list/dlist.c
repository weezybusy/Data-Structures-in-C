#include <stdlib.h>
#include <string.h>

#include "dlist.h"

void dlist_init(dlist_t *list, void (*destroy)(void *data))
{
        list->size = 0;
        list->destroy = destroy;
        list->head = NULL;
        list->tail = NULL;
}

void dlist_destroy(dlist_t *list)
{
        void *data;

        while (list->size > 0) {
                if (dlist_remove(list, list->head, (void **) &data) == 0 &&
                                list->destroy != NULL) {
                        list->destroy(data);
                }
        }

        memset(list, 0, sizeof(dlist_t));
}

int dlist_insert_prev(dlist_t *list, dnode_t *node, const void *data)
{
        if (node == NULL && list->size != 0) {
                return -1;
        }

        dnode_t *new_node = (dnode_t *) malloc(sizeof(dnode_t));
        if (new_node == NULL) {
                return -1;
        }
        new_node->data = (void *)data;
        new_node->prev = NULL;
        new_node->next = NULL;

        if (list->size == 0) {
                list->head = new_node;
                list->tail = new_node;
        } else {
                new_node->prev = node->prev;
                new_node->next = node;
                if (node->prev == NULL) {
                        list->head = new_node;
                } else {
                        node->prev->next = new_node;
                }
                node->prev = new_node;
        }

        list->size++;

        return 0;
}

int dlist_insert_next(dlist_t *list, dnode_t *node, const void *data)
{
        if (node == NULL && list->size != 0) {
                return -1;
        }

        dnode_t *new_node = (dnode_t *) malloc(sizeof(dnode_t));
        if (new_node == NULL) {
                return -1;
        }
        new_node->data = (void *)data;
        new_node->prev = NULL;
        new_node->next = NULL;

        if (list->size == 0) {
                list->head = new_node;
                list->tail = new_node;
        } else {
                new_node->prev = node;
                new_node->next = node->next;
                if (node->next == NULL) {
                        list->tail = new_node;
                } else {
                        node->next->prev = new_node;
                }
                node->next = new_node;
        }

        list->size++;

        return 0;
}

int dlist_remove(dlist_t *list, dnode_t *node, void **data)
{
        if (node == NULL || list->size == 0) {
                return -1;
        }

        *data = node->data;

        if (node == list->head) {
                list->head = node->next;
                if (list->head == NULL) {
                        list->tail = NULL;
                } else {
                        node->next->prev = NULL;
                }
        } else {
                node->prev->next = node->next;
                if (node->next == NULL) {
                        list->tail = node->prev;
                } else {
                        node->next->prev = node->prev;
                }
        }

        free(node);
        list->size--;

        return 0;
}
