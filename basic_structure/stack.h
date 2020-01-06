#ifndef _STACK_H_
#define _STACK_H_

#define STACK_DEPTH 8
/* value type is int */
struct stack {
	int value[STACK_DEPTH];
	int top;
};

int stack_init(struct stack *s);

int stack_empty(struct stack *s);

int stack_full(struct stack *s);

int push(struct stack *s, int value);

int pop(struct stack *s);

int touch_pop();

#endif /* _STACK_H_ */
