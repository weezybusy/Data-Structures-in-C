#include <assert.h>
#include <stdio.h>

#include "list.h"
#include "stack.h"

void test_stack(void);
void test_stack_push(void);
void test_stack_pop(void);
void test_stack_peek(void);

int main(void)
{
        test_stack();
        return EXIT_SUCCESS;
}

void test_stack(void)
{
        test_stack_peek();
        test_stack_push();
        test_stack_pop();
}

void test_stack_peek(void)
{
        stack_t stack;
        stack_init(&stack, free);

        assert(stack.size == 0);
        size_t size = stack.size;

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

        assert(stack_push(&stack, data1) != -1);
        assert(stack.size == ++size);
        assert(*(int *) stack_peek(&stack) == val1);

        assert(stack_push(&stack, data2) != -1);
        assert(stack.size == ++size);
        assert(*(int *) stack_peek(&stack) == val2);

        assert(stack_push(&stack, data3) != -1);
        assert(stack.size == ++size);
        assert(*(int *) stack_peek(&stack) == val3);

        stack_destroy(&stack);
        printf("%-30s ok\n", __func__);
}

void test_stack_push(void)
{
        stack_t stack;
        stack_init(&stack, free);

        assert(stack.size == 0);
        size_t size = stack.size;

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

        assert(stack_push(&stack, data1) != -1);
        assert(stack.size == ++size);
        assert(*(int *) (stack.head)->data == val1);

        assert(stack_push(&stack, data2) != -1);
        assert(stack.size == ++size);
        assert(*(int *) (stack.head)->data == val2);

        assert(stack_push(&stack, data3) != -1);
        assert(stack.size == ++size);
        assert(*(int *) (stack.head)->data == val3);

        assert(stack_push(&stack, data4) != -1);
        assert(stack.size == ++size);
        assert(*(int *) (stack.head)->data == val4);

        stack_destroy(&stack);
        printf("%-30s ok\n", __func__);
}

void test_stack_pop(void)
{
        stack_t stack;
        stack_init(&stack, free);

        assert(stack.size == 0);
        size_t size = stack.size;

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

        // Push data onto the stack.
        assert(stack_push(&stack, data1) != -1);
        assert(stack.size == ++size);
        assert(*(int *) (stack.head)->data == val1);

        assert(stack_push(&stack, data2) != -1);
        assert(stack.size == ++size);
        assert(*(int *) (stack.head)->data == val2);

        assert(stack_push(&stack, data3) != -1);
        assert(stack.size == ++size);
        assert(*(int *) (stack.head)->data == val3);

        int *data;

        // Pop data.
        assert(stack_pop(&stack, (void **) &data) != -1);
        assert(stack.size == --size);
        assert(*data == val3);
        free(data);

        assert(stack_pop(&stack, (void **) &data) != -1);
        assert(stack.size == --size);
        assert(*data == val2);
        free(data);

        assert(stack_pop(&stack, (void **) &data) != -1);
        assert(stack.size == --size);
        assert(*data == val1);
        free(data);

        stack_destroy(&stack);
        printf("%-30s ok\n", __func__);
}
