#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void test_queue(void);
void test_queue_enqueue(void);
void test_queue_dequeue(void);
void test_peek(void);

int main(void)
{
        test_queue();
        return EXIT_SUCCESS;
}

void test_queue(void)
{
        test_queue_enqueue();
        test_queue_dequeue();
        test_peek();
}

void test_queue_enqueue(void)
{
        queue_t queue;
        queue_init(&queue, free);

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

        assert(queue.size == 0);
        size_t size = queue.size;

        assert(queue_enqueue(&queue, data1) != -1);
        assert(queue.size == ++size);
        assert(*(int *) (queue.tail)->data == val1);

        assert(queue_enqueue(&queue, data2) != -1);
        assert(queue.size == ++size);
        assert(*(int *) (queue.tail)->data == val2);

        assert(queue_enqueue(&queue, data3) != -1);
        assert(queue.size == ++size);
        assert(*(int *) (queue.tail)->data == val3);

        queue_destroy(&queue);
        printf("%-30s ok\n", __func__);
}

void test_peek(void)
{
        queue_t queue;
        queue_init(&queue, free);

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

        assert(queue.size == 0);
        size_t size = queue.size;

        assert(queue_enqueue(&queue, data1) != -1);
        assert(queue.size == ++size);
        assert(*(int *) queue_peek(&queue) == val1);

        assert(queue_enqueue(&queue, data2) != -1);
        assert(queue.size == ++size);
        assert(*(int *) queue_peek(&queue) == val1);

        assert(queue_enqueue(&queue, data3) != -1);
        assert(queue.size == ++size);
        assert(*(int *) queue_peek(&queue) == val1);

        int *data = NULL;

        assert(queue_dequeue(&queue, (void **) &data) != -1);
        assert(queue.size == --size);
        assert(*(int *) queue_peek(&queue) == val2);
        free(data);

        assert(queue_dequeue(&queue, (void **) &data) != -1);
        assert(queue.size == --size);
        assert(*(int *) queue_peek(&queue) == val3);
        free(data);

        assert(queue_dequeue(&queue, (void **) &data) != -1);
        assert(queue.size == --size);
        assert(queue_peek(&queue) == NULL);
        free(data);

        queue_destroy(&queue);
        printf("%-30s ok\n", __func__);
}

void test_queue_dequeue(void)
{
        queue_t queue;
        queue_init(&queue, free);

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

        assert(queue.size == 0);
        size_t size = queue.size;

        // queue_enqueue data.
        assert(queue_enqueue(&queue, data1) != -1);
        assert(queue.size == ++size);
        assert(*(int *) queue_peek(&queue) == val1);

        assert(queue_enqueue(&queue, data2) != -1);
        assert(queue.size == ++size);
        assert(*(int *) queue_peek(&queue) == val1);

        assert(queue_enqueue(&queue, data3) != -1);
        assert(queue.size == ++size);
        assert(*(int *) queue_peek(&queue) == val1);

        int *data = NULL;

        // queue_dequeue data.
        assert(queue_dequeue(&queue, (void **) &data) != -1);
        assert(queue.size == --size);
        assert(*(int *) queue_peek(&queue) == val2);
        free(data);

        assert(queue_dequeue(&queue, (void **) &data) != -1);
        assert(queue.size == --size);
        assert(*(int *) queue_peek(&queue) == val3);
        free(data);

        assert(queue_dequeue(&queue, (void **) &data) != -1);
        assert(queue.size == --size);
        assert(queue_peek(&queue) == NULL);
        free(data);

        assert(queue.size == 0);
        queue_destroy(&queue);
        printf("%-30s ok\n", __func__);
}
