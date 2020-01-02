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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *next_greater_elements(int *nums, int numsSize, int *returnSize)
{
	int *return_arr = calloc(1, sizeof(int) * numsSize);
	int i = 0;
	struct stack s;

	*returnSize = numsSize;
	stack_init(&s);
	for (i = 0; i < numsSize; i++) {
		while ((!stack_empty(&s)) && (nums[i] > nums[touch_pop(&s)])) {
			return_arr[pop(&s)] = nums[i];
		}
		push(&s, i);
	}

	if (stack_empty(&s)) {
		return return_arr;
	}
	for (i = 0; i < numsSize; i++) {
		while ((!stack_empty(&s)) && (nums[i] > nums[touch_pop(&s)])) {
			return_arr[pop(&s)] = nums[i];
		}
	}
	while (!stack_empty(&s)) {
		return_arr[pop(&s)] = -1;
	}

	return return_arr;
}

int main(void)
{
	int nums[MAX_STACK_LEN] = {0};
	int numsSize = 0;
	int returnSize = 0;
	int i = 0;

	scanf("%d", &numsSize);
	for (i = 0; i < numsSize; i++) {
		scanf("%d", &nums[i]);
	}
	int *return_arr = next_greater_elements(nums, numsSize, &returnSize);
	for (i = 0; i < returnSize; i++) {
		printf("%d ", return_arr[i]);
	}
	printf("\n");

	return 0;
}
