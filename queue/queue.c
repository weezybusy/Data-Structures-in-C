#include <stdlib.h>

#include "list.h"
#include "queue.h"

int queue_enqueue(queue_t *queue, const void *data)
{
        return list_insert_next(queue, queue->tail, data);
}

int queue_dequeue(queue_t *queue, void **data)
{
        return list_remove_next(queue, NULL, data);
}
