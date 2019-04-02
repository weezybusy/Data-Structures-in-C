#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#include "list.h"

/* Implement stacks as linked lists. */

typedef list_t stack_t;

/* Public Interface. ------------------------------------------------------ */

#define stack_init list_init

#define stack_destroy list_destroy

int stack_push(stack_t *stack, const void *data);

int stack_pop(stack_t *stack, void **data);

#define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)

#define stack_size list_size

#endif
