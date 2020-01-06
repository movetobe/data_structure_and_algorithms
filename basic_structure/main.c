#include "stack.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int i = 0;
	struct stack s;
	struct queue q;

	stack_init(&s);
	queue_init(&q);

	printf("test1\n");
	for (i = 0; i < 10; i++) {
		push(&s, i);
		enqueue(&q, i);
	}
	printf("test2\n");
	for (i = 0; i < 5; i++) {
		touch_pop(&s);
		pop(&s);
		dequeue(&q);
	}
	printf("test3\n");
	for (i = 0; i < 10; i++) {
		push(&s, i * i);
		enqueue(&q, i * i);
	}

	printf("stack: ");
	while (!stack_empty(&s)) {
		printf("%d ", pop(&s));
	}
	printf("\n");
	printf("queue: ");
	while (!queue_empty(&q)) {
		printf("%d ", dequeue(&q));
	}
	printf("\n");

	return 0;
}
