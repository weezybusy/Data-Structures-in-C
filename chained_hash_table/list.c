#include <stdlib.h>
#include <string.h>

#include "list.h"

void list_init(list_t *list, void (*destroy)(void *data))
{
        list->size = 0;
        list->compare = NULL;
        list->destroy = destroy;
        list->head = NULL;
        list->tail = NULL;
}

void list_destroy(list_t *list)
{
        void *data = NULL;

        while (list->size > 0) {
                if (list_remove_next(list, NULL, (void **) &data) == 0 &&
                                list->destroy != NULL) {
                        list->destroy(data);
                }
        }

        memset(list, 0, sizeof(list_t));
}

int list_insert_next(list_t *list, node_t *node, const void *data)
{
        node_t *new_node = (node_t *) malloc(sizeof(node_t));
        if (new_node == NULL) {
                return -1;
        }
        new_node->data = (void *) data;
        new_node->next = NULL;

        if (node == NULL) {
                new_node->next = list->head;
                list->head = new_node;
                if (list->size == 0) {
                        list->tail = new_node;
                }
        } else {
                if (node->next == NULL) {
                        list->tail = new_node;
                }
                new_node->next = node->next;
                node->next = new_node;
        }

        list->size++;

        return 0;
}

int list_remove_next(list_t *list, node_t *node, void **data)
{
        node_t *tmp = NULL;

        if (list->size == 0) {
                return -1;
        }

        if (node == NULL) {
                *data = list->head->data;
                tmp = list->head;
                list->head = list->head->next;
        } else {
                if (node->next == NULL) {
                        return -1;
                }
                *data = node->next->data;
                tmp = node->next;
                node->next = node->next->next;
                if (node->next == NULL) {
                        list->tail = node;
                }
        }

        free(tmp);
        list->size--;

        return 0;
}
