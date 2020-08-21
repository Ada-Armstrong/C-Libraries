#ifndef CONTAINER_QUEUE_H
#define CONTAINER_QUEUE_H

#include "dlinked_list.h"

typedef struct queue *Queue;

Queue create_queue(void (*free_func)(void *), void *(*cpy_func)(void *));

void destroy_queue(Queue q);

int insert_queue(Queue q, void *item);

void *pop_queue(Queue q);

int isempty_queue(Queue q);

#endif
