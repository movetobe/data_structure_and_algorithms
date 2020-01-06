#ifndef _QUEUE_H_
#define _QUEUE_H_

#define QUEUE_DEPTH 8
struct queue {
	int value[QUEUE_DEPTH];
	int rear;
	int front;
};

int queue_init(struct queue *q);

int queue_empty(struct queue *q);

int queue_full(struct queue *q);

int enqueue(struct queue *q, int value);

int dequeue(struct queue *q);

#endif /* _QUEUE_H_*/
