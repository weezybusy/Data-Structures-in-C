#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "clist.h"

void test_clist(void);

void test_clist_insert_next(void);
void test_clist_remove_next(void);
void display_clist(const clist_t *list);

int main(void)
{
        test_clist();
        return EXIT_SUCCESS;
}

void test_clist(void)
{
        test_clist_insert_next();
        test_clist_remove_next();
}

void test_clist_insert_next(void)
{
        clist_t list;
        clist_init(&list, free);

        int *data1 = (int *) malloc(sizeof(int));
        int *data2 = (int *) malloc(sizeof(int));
        int *data3 = (int *) malloc(sizeof(int));

        assert(data1 != NULL);
        assert(data2 != NULL);
        assert(data3 != NULL);

        int val1 = 55;
        int val2 = 66;
        int val3 = 77;

        *data1 = val1;
        *data2 = val2;
        *data3 = val3;

        size_t count = 0;

        // Add element to an empty list.
        assert(list.size == count);
        assert(clist_insert_next(&list, NULL, (void *) data1) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->data == 55);

        // Add element to the end of the list.
        assert(clist_insert_next(&list, list.head, (void *) data2) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->next->data == 66);

        // Add element into the middle of the list.
        assert(clist_insert_next(&list, list.head, (void *) data3) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->next->data == 77);

        //display_clist(&list);
        clist_destroy(&list);

        printf("%-30s ok\n", __func__);
}

void test_clist_remove_next(void)
{
        clist_t list;
        clist_init(&list, free);

        int *data1 = (int *) malloc(sizeof(int));
        int *data2 = (int *) malloc(sizeof(int));
        int *data3 = (int *) malloc(sizeof(int));

        assert(data1 != NULL);
        assert(data2 != NULL);
        assert(data3 != NULL);

        int val1 = 55;
        int val2 = 66;
        int val3 = 77;

        *data1 = val1;
        *data2 = val2;
        *data3 = val3;

        int *data;
        size_t count = 0;

        // Check removing from an empty list.
        assert(list.size == count);
        assert(clist_remove_next(&list, NULL, (void **) &data) == -1);

        // Add elements to the list.
        assert(clist_insert_next(&list, list.head, data1) != -1);
        assert(list.size == ++count);
        assert(clist_insert_next(&list, list.head, data2) != -1);
        assert(list.size == ++count);
        assert(clist_insert_next(&list, list.head, data3) != -1);
        assert(list.size == ++count);

        // Check removing element from the middle of the list.
        assert(clist_remove_next(&list, list.head, (void **) &data) != -1);
        assert(list.size == --count);
        assert(*data == val3);
        free(data);

        // Check removing an element at the end of the list.
        assert(clist_remove_next(&list, list.head, (void **) &data) != -1);
        assert(list.size == --count);
        assert(*data == val2);
        free(data);

        // Check removing the last remaining element in the list.
        assert(clist_remove_next(&list, list.head, (void **) &data) != -1);
        assert(list.size == --count);
        assert(*data == val1);
        free(data);

        clist_destroy(&list);

        printf("%-30s ok\n", __func__);
}

void display_clist(const clist_t *list)
{
        if (list->size == 0) {
                printf("empty\n");
        } else if (list->size == 1) {
                printf("%d\n", *(int *) list->head->data);
        } else {
                cnode_t *tmp = list->head;
                while (tmp->next != list->head) {
                        printf("%d ", *(int *) tmp->data);
                        tmp = tmp->next;
                }
                printf("%d\n", *(int *) tmp->data);
        }
}
