#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_LEN 1024

struct stack {
	int value[MAX_STACK_LEN];
	int top;
};

int stack_init(struct stack *s)
{
	memset(s, 0, sizeof(struct stack));
	s->top = -1;

	return 0;
}

int push(struct stack *s, int value)
{
	s->top++;
	if (s->top >= MAX_STACK_LEN) {
		printf("stack overflow\n");
		return -1;
	}

	s->value[s->top] = value;

	return 0;
}

int pop(struct stack *s)
{
	int value = 0;

	if (s->top < 0) {
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
		return -1;
	}

	return s->value[s->top];
}

int stack_empty(struct stack *s)
{
	if (s->top < 0) {
		return 1;
	}

	return 0;
}

int trap(int *height, int heightSize)
{
	int i = 0;
	struct stack s;
	int area = 0;
	int bottom = 0;
	int top = 0;
	int idx_prev = 0;

	/* decrease stack */
	stack_init(&s);
	for (i = 0; i < heightSize; i++) {
		while ((!stack_empty(&s)) && (height[i] > height[touch_pop(&s)])) {
			/* pop */
			bottom = height[pop(&s)];
			if (!stack_empty(&s)) {
				/* touch top of stack */
				idx_prev = touch_pop(&s);
				top = height[i] < height[idx_prev] ? height[i] : height[idx_prev];
				/* calc */
				area += ((top - bottom) * (i - idx_prev - 1));
			}
		}
		/* push */
		push(&s, i);
	}

	return area;
}

int main(void)
{
	int height[MAX_STACK_LEN] = {0};
	int i = 0;
	int heightSize = 0;

	scanf("%d", &heightSize);
	for (i = 0; i < heightSize; i++) {
		scanf("%d", &height[i]);
	}
	printf("%d\n", trap(height, heightSize));
	return 0;
}
