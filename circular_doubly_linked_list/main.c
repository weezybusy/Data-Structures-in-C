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
        //test_cdlist_insert_next();
        //test_cdlist_remove();
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

        display_cdlist(&list);

        // Add an element at the end of the list.
        assert(cdlist_insert_prev(&list, list.head, (void *) data2) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->prev->data == val2);

        display_cdlist(&list);

        // Add an element to the middle of the list.
        assert(cdlist_insert_prev(&list, list.head, (void *) data3) != -1);
        assert(list.size == ++count);
        assert(*(int *) (list.head)->prev->data == val3);

        display_cdlist(&list);

        cdlist_destroy(&list);
        printf("%-30s ok\n", __func__);
}

void test_cdlist_insert_next(void)
{
        cdlist_t list;
        cdlist_init(&list, free);

        cdlist_destroy(&list);
        printf("%-30s ok", __func__);
}

void test_cdlist_remove(void)
{
        cdlist_t list;
        cdlist_init(&list, free);

        cdlist_destroy(&list);
        printf("%-30s ok", __func__);
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
