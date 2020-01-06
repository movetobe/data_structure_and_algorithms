#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int queue_init(struct queue *q)
{
	memset(q, 0, sizeof(struct queue));

	return 0;
}

int queue_empty(struct queue *q)
{
	if (q->rear == q->front) {
		return 1;
	}
	return 0;
}

int queue_full(struct queue *q)
{
	if (((q->rear + 1) % QUEUE_DEPTH) == q->front) {
		return 1;
	}
	return 0;
}

int enqueue(struct queue *q, int value)
{
	if (queue_full(q)) {
		printf("queue full\n");
		return -1;
	}
	q->value[q->rear] = value;
	q->rear = (q->rear + 1) % QUEUE_DEPTH;

	return 0;
}

int dequeue(struct queue *q)
{
	int value = 0;

	if (queue_empty(q)) {
		printf("queue empty\n");
		return -1;
	}
	value = q->value[q->front];
	q->front = (q->front + 1) % QUEUE_DEPTH;

	return value;
}
