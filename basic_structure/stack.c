#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stack_init(struct stack *s)
{
	memset(s, 0, sizeof(struct stack));
	s->top = -1;

	return 0;
}

int stack_empty(struct stack *s)
{
	if (s->top < 0) {
		return 1;
	}

	return 0;
}

int stack_full(struct stack *s)
{
	if (s->top >= STACK_DEPTH - 1) {
		return 1;
	}

	return 0;
}

int push(struct stack *s, int value)
{
	if (stack_full(s)) {
		printf("stack overflow\n");
		return -1;
	}
	s->top++;
	s->value[s->top] = value;

	return 0;
}

int pop(struct stack *s)
{
	int value = 0;

	if (stack_empty(s)) {
		printf("stack underflow\n");
		return -1;
	}
	value = s->value[s->top];
	s->top--;

	return value;
}

int touch_pop(struct stack *s)
{
	if (s->top < 0) {
		printf("stack underflow\n");
		return -1;
	}
	return s->value[s->top];
}

