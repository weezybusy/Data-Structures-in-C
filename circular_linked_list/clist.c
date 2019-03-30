#include <stdlib.h>
#include <string.h>

#include "clist.h"

void clist_init(clist_t *list, void (*destroy)(void *data))
{
        list->size = 0;
        list->compare = NULL;
        list->destroy = destroy;
        list->head = NULL;
}

void clist_destroy(clist_t *list)
{
        void *data = NULL;

        while (list->size > 0) {
                if (clist_remove_next(list, list->head, (void **) &data) == 0 &&
                                list->destroy != NULL) {
                        list->destroy(data);
                }
        }

        memset(list, 0, sizeof(clist_t));
}

int clist_insert_next(clist_t *list, cnode_t *node, const void *data)
{
        if (node == NULL && list->size != 0) {
                return -1;
        }

        cnode_t *new_node = (cnode_t *) malloc(sizeof(cnode_t));
        if (new_node == NULL) {
                return -1;
        }
        new_node->data = (void *) data;
        new_node->next = NULL;

        if (list->size == 0) {
                new_node->next = new_node;
                list->head = new_node;
        } else {
                new_node->next = node->next;
                node->next = new_node;
        }

        list->size++;

        return 0;
}

int clist_remove_next(clist_t *list, cnode_t *node, void **data)
{
        cnode_t *tmp = NULL;

        if (node == NULL || list->size == 0) {
                return -1;
        }

        *data = node->next->data;

        if (node->next == node) {
                tmp = node;
                list->head = NULL;
        } else {
                tmp = node->next;
                node->next = node->next->next;
                if (tmp == list->head) {
                        list->head = tmp->next;
                }
        }

        free(tmp);
        list->size--;

        return 0;
}
