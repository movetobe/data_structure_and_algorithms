#include <stdio.h>
#include <stdlib.h>

/* reference from others */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int jump(int *arr, int arrSize, int d, int start, int *jump_cache)
{
	int i;
	int left_start, left_end, right_start, right_end;
	int max = 0;

	/* ended */
	if (start < 0 || start >= arrSize) {
		return 0;
	}

	/* options */
	left_start = MAX(0, start - 1);
	left_end = MAX(0, start - d);
	for (i = left_start; i >= left_end; i--) {
		if (arr[i] >= arr[start]) {
			break;
		}
		if (!jump_cache[i]) {
			jump_cache[i] = jump(arr, arrSize, d, i, jump_cache);
		}
		max = MAX(max, jump_cache[i]);
	}

	right_start = MIN(arrSize - 1, start + 1);
	right_end = MIN(arrSize - 1, start + d);
	for (i = right_start; i <= right_end; i++) {
		if (arr[i] >= arr[start]) {
			break;
		}
		if (!jump_cache[i]) {
			jump_cache[i] = jump(arr, arrSize, d, i, jump_cache);
		}
		max = MAX(max, jump_cache[i]);
	}

	return max + 1;
}
int maxJumps(int* arr, int arrSize, int d){
	int i;
	int max_jump = 0;
	int steps;
	int *jump_cache = calloc(1, sizeof(int) * arrSize);

	if (arrSize <= 1) {
		return 1;
	}
	for (i = 0; i < arrSize; i++) {
		steps = jump(arr, arrSize, d, i, jump_cache);
		max_jump = MAX(max_jump, steps);
	}
	free(jump_cache);
	return max_jump;
}

int main(void)
{
	int arr[1024] = {0};
	int arrSize;
	int d;
	int i;

	scanf("%d", &arrSize);
	for (i = 0; i < arrSize; i++) {
		scanf("%d,", &arr[i]);
	}
	scanf("%d", &d);

	printf("%d\n", maxJumps(arr, arrSize, d));

	return 0;
}
