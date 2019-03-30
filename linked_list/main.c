#include <assert.h>
#include <stdio.h>

#include "list.h"

void test_list(void);
void test_list_insert_next(void);
void test_list_remove_next(void);

void display_list(const list_t *list);

int main(void)
{
        test_list();
        return EXIT_SUCCESS;
}

void test_list(void)
{
        test_list_insert_next();
        test_list_remove_next();
}

void test_list_insert_next(void)
{
        list_t list;
        list_init(&list, free);

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
        assert(list.size == count);

        // Check adding an element to the empty list.
        assert(list_insert_next(&list, NULL, (void *) data1) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->data == val1);

        // Check adding an element to the end of the list.
        assert(list_insert_next(&list, list.head, (void *) data2) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->next->data == val2);

        // Check adding an element into the middle of the list.
        assert(list_insert_next(&list, list.head, (void *) data3) -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->next->data == val3);

        list_destroy(&list);

        printf("%-30s ok\n", __func__);
}

void test_list_remove_next(void)
{
        list_t list;
        list_init(&list, free);

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

        int val1 = 55;
        int val2 = 66;
        int val3 = 77;
        int val4 = 88;
        int val5 = 99;

        *data1 = val1;
        *data2 = val2;
        *data3 = val3;
        *data4 = val4;
        *data5 = val5;

        size_t count = 0;
        int *data = NULL;

        // Check removing from the empty list.
        assert(list_remove_next(&list, NULL, (void **) &data) == -1);

        // Add elements to the list.
        assert(list_insert_next(&list, NULL, (void *) data1) != -1);
        assert(list.size == ++count);

        assert(list_insert_next(&list, NULL, (void *) data2) != -1);
        assert(list.size == ++count);

        assert(list_insert_next(&list, NULL, (void *) data3) != -1);
        assert(list.size == ++count);

        assert(list_insert_next(&list, NULL, (void *) data4) != -1);
        assert(list.size == ++count);

        assert(list_insert_next(&list, NULL, (void *) data5) != -1);
        assert(list.size == ++count);

        // Check removing the head of the list.
        assert(list_remove_next(&list, NULL, (void **) &data) != -1);
        assert(list.size == --count);
        assert(*data == 99);
        free(data);
        data = NULL;

        // Check removing an element from the middle of the list.
        assert(list_remove_next(&list, list.head, (void **) &data) != -1);
        assert(list.size == --count);
        assert(*data == 77);
        free(data);
        data = NULL;

        // Check removing the tail of the list.
        assert(list_remove_next(&list, list.head->next, (void **) &data) != -1);
        assert(list.size == --count);
        assert(*data == 55);
        free(data);
        data = NULL;

        // Remove remaining elements.
        assert(list_remove_next(&list, NULL, (void **) &data) != -1);
        assert(list.size == --count);
        assert(*data == 88);
        free(data);
        data = NULL;

        assert(list_remove_next(&list, NULL, (void **) &data) != -1);
        assert(list.size == --count);
        assert(*data == 66);
        free(data);
        data = NULL;

        list_destroy(&list);
        list.head = NULL;

        printf("%-30s ok\n", __func__);
}

void display_list(const list_t *list)
{
        node_t *node = list->head;

        while (node != NULL) {
                printf("%d ", *(int *) node->data);
                node = node->next;
        }
        putchar('\n');
}
