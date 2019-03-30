#include <assert.h>
#include <stdio.h>

#include "dlist.h"

void test_dlist(void);
void test_dlist_insert_prev(void);
void test_dlist_insert_next(void);
void test_dlist_remove(void);

void display_dlist(const dlist_t *list);

int main(void)
{
        test_dlist();
        return EXIT_SUCCESS;
}

void test_dlist(void)
{
        test_dlist_insert_prev();
        test_dlist_insert_next();
        test_dlist_remove();
}

void test_dlist_insert_prev(void)
{
        dlist_t list;
        dlist_init(&list, free);

        int val1 = 55;
        int val2 = 66;
        int val3 = 77;

        int *data1 = (int *) malloc(sizeof(int));
        int *data2 = (int *) malloc(sizeof(int));
        int *data3 = (int *) malloc(sizeof(int));

        assert(data1 != NULL);
        assert(data2 != NULL);
        assert(data3 != NULL);

        *data1 = val1;
        *data2 = val2;
        *data3 = val3;

        size_t count = 0;

        // Check initial list size is 0.
        assert(list.size == count);

        // Check adding element to the empty list.
        assert(dlist_insert_prev(&list, NULL, (void *) data1) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->data == val1);
        assert(list.head == list.tail);

        // Check adding element to the list with single element in it.
        assert(dlist_insert_prev(&list, list.head, (void *) data2) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->data == val2);
        assert(list.head != list.tail);

        // Check adding element to the middle of the list.
        assert(dlist_insert_prev(&list, list.tail, (void *) data3) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.tail)->prev->data == val3);

        dlist_destroy(&list);

        printf("%-30s ok\n", __func__);
}

void test_dlist_insert_next(void)
{
        dlist_t list;
        dlist_init(&list, free);

        int val1 = 55;
        int val2 = 66;
        int val3 = 77;

        int *data1 = (int *) malloc(sizeof(int));
        int *data2 = (int *) malloc(sizeof(int));
        int *data3 = (int *) malloc(sizeof(int));

        assert(data1 != NULL);
        assert(data2 != NULL);
        assert(data3 != NULL);

        *data1 = 55;
        *data2 = 66;
        *data3 = 77;

        size_t count = 0;

        // Check initial list size is 0.
        assert(list.size == count);

        // Check adding an element into the empty list.
        assert(dlist_insert_next(&list, NULL, (void *) data1) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->data == val1);
        assert(list.head == list.tail);

        // Check adding an element into the list with single element in it.
        assert(dlist_insert_next(&list, list.head, (void *) data2) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.tail)->data == val2);
        assert(list.head != list.tail);

        // Check adding an element into the middle of the list.
        assert(dlist_insert_next(&list, list.head, (void *) data3) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->next->data == val3);

        dlist_destroy(&list);

        printf("%-30s ok\n", __func__);
}

void test_dlist_remove(void)
{
        dlist_t list;
        dlist_init(&list, free);

        int val1 = 55;
        int val2 = 66;
        int val3 = 77;
        int val4 = 88;
        int val5 = 99;

        int *data1 = (int *) malloc(sizeof(int));
        int *data2 = (int *) malloc(sizeof(int));
        int *data3 = (int *) malloc(sizeof(int));
        int *data4 = (int *) malloc(sizeof(int));
        int *data5 = (int *) malloc(sizeof(int));

        assert(data1 != NULL);
        assert(data2 != NULL);
        assert(data3 != NULL);
        assert(data4 != NULL);
        assert(data5 != NULL);

        *data1 = 55;
        *data2 = 66;
        *data3 = 77;
        *data4 = 88;
        *data5 = 99;

        size_t count = 0;

        // Add element to the list.
        assert(list.size == count);
        assert(dlist_insert_next(&list, NULL, (void *) data1) != -1);
        assert(list.size == ++count);
        assert(dlist_insert_next(&list, list.head, (void *) data2) != -1);
        assert(list.size == ++count);
        assert(dlist_insert_next(&list, list.head, (void *) data3) != -1);
        assert(list.size == ++count);
        assert(dlist_insert_next(&list, list.head, (void *) data4) != -1);
        assert(list.size == ++count);
        assert(dlist_insert_next(&list, list.head, (void *) data5) != -1);
        assert(list.size == ++count);

        int *data = NULL;

        // Check deleting head element.
        assert(dlist_remove(&list, list.head, (void **) &data) != -1);
        assert(list.size == --count);
        assert(*data == val1);
        free(data);

        // Check deleting tail element.
        assert(dlist_remove(&list, list.head, (void **) &data) != -1);
        assert(list.size == --count);
        assert(*data == val5);
        free(data);

        // Check deleting middle element.
        assert(dlist_remove(&list, (list.head)->next, (void **) &data) != -1);
        assert(list.size == --count);
        assert(*data == val3);
        free(data);

        // Check deleting element when it is NULL.
        assert(dlist_remove(&list, NULL, (void **) &data) == -1);

        // Check if one element remains head == tail.
        assert(dlist_remove(&list, list.head, (void **) &data) != -1);
        assert(list.size == --count);
        assert(*data == val4);
        assert(list.head == list.tail);
        free(data);

        // Check that list size is zero after removing all the elements.
        assert(dlist_remove(&list, list.tail, (void **) &data) != -1);
        assert(list.size == --count);
        assert(*data == val2);
        free(data);

        dlist_destroy(&list);

        printf("%-30s ok\n", __func__);
}

void display_dlist(const dlist_t *list)
{
        if (list->size == 0) {
                printf("empty\n");
        }

        dnode_t *node = list->head;
        while (node != NULL) {
                printf("%d ", *(int *) node->data);
                node = node->next;
        }
        printf("\n");
}
