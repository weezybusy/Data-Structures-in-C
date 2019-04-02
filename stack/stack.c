#include <stdlib.h>

#include "list.h"
#include "stack.h"

int stack_push(stack_t *stack, const void *data)
{
        return list_insert_next(stack, NULL, data);
}

int stack_pop(stack_t *stack, void **data)
{
        return list_remove_next(stack, NULL, data);
}
