#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "cdlist.h"

void test_cdlist(void);
void test_cdlist_insert_prev(void);
void test_cdlist_insert_next(void);
void test_cdlist_remove(void);

void display_cdlist(const cdlist_t *list);

int main(void)
{
        test_cdlist();
        return EXIT_SUCCESS;
}

void test_cdlist(void)
{
        test_cdlist_insert_prev();
        test_cdlist_insert_next();
        test_cdlist_remove();
}

void test_cdlist_insert_prev(void)
{
        cdlist_t list;
        cdlist_init(&list, free);

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

        // Add an element to the empty list.
        assert(list.size == count);
        assert(cdlist_insert_prev(&list, NULL, (void *) data1) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->data == val1);

        // Add an element at the end of the list.
        assert(cdlist_insert_prev(&list, list.head, (void *) data2) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->prev->data == val2);

        // Add an element to the middle of the list.
        assert(cdlist_insert_prev(&list, list.head, (void *) data3) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->prev->data == val3);

        cdlist_destroy(&list);
        printf("%-30s ok\n", __func__);
}

void test_cdlist_insert_next(void)
{
        cdlist_t list;
        cdlist_init(&list, free);

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

        // Add an element to the empty list.
        assert(list.size == count);
        assert(cdlist_insert_next(&list, NULL, (void *) data1) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->data == val1);

        // Add an element at the end of the list.
        assert(cdlist_insert_next(&list, list.head, (void *) data2) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->next->data == val2);

        // Add an element to the middle of the list.
        assert(cdlist_insert_next(&list, list.head, (void *) data3) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->next->data == val3);

        cdlist_destroy(&list);
        printf("%-30s ok\n", __func__);
}

void test_cdlist_remove(void)
{
        cdlist_t list;
        cdlist_init(&list, free);

        int *data1 = (int *) malloc(sizeof(int));
        int *data2 = (int *) malloc(sizeof(int));
        int *data3 = (int *) malloc(sizeof(int));
        int *data4 = (int *) malloc(sizeof(int));

        assert(data1 != NULL);
        assert(data2 != NULL);
        assert(data3 != NULL);
        assert(data4 != NULL);

        int val1 = 55;
        int val2 = 66;
        int val3 = 77;
        int val4 = 88;

        *data1 = val1;
        *data2 = val2;
        *data3 = val3;
        *data4 = val4;

        size_t count = 0;
        int *data = NULL;

        // Check removing from the empty list.
        assert(list.size == count);
        assert(cdlist_remove(&list, NULL, (void **) &data) == -1);

        // Add elements to the list.
        assert(cdlist_insert_next(&list, NULL, (void *) data1) != -1);
        assert(list.size == ++count);
        assert(cdlist_insert_next(&list, list.head, (void *) data2) != -1);
        assert(list.size == ++count);
        assert(cdlist_insert_next(&list, list.head, (void *) data3) != -1);
        assert(list.size == ++count);
        assert(cdlist_insert_next(&list, list.head, (void *) data4) != -1);
        assert(list.size == ++count);

        // Check removing the first element.
        assert(cdlist_remove(&list, list.head, (void **) &data) != -1);
        assert(*data == 55);
        assert(list.size == --count);
        free(data);

        // Check removing the element in the middle.
        assert(cdlist_remove(&list, (list.head)->next, (void **) &data) != -1);
        assert(*data == 77);
        assert(list.size == --count);
        free(data);

        // Check removing an element before head.
        assert(cdlist_remove(&list, (list.head)->next, (void **) &data) != -1);
        assert(*data == 66);
        assert(list.size == --count);
        free(data);

        // Check if the last element still in the list.
        assert(list.size == count);
        assert(*(int *) (list.head)->data == 88);

        cdlist_destroy(&list);
        printf("%-30s ok\n", __func__);
}

void display_cdlist(const cdlist_t *list)
{
        if (list->size == 0) {
                printf("empty\n");
        } else if (list->size == 1) {
                printf("%d\n", *(int *) list->head->data);
        } else {
                cdnode_t *tmp = list->head;
                while (tmp->next != list->head) {
                        printf("%d ", *(int *) tmp->data);
                        tmp = tmp->next;
                }
                printf("%d\n", *(int *) tmp->data);
        }
}
