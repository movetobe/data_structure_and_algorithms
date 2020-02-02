#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int search_first(int *nums, int start, int end, int target)
{
	int left = start, right = end;
	int middle = (left + right) / 2;

	while (left < right) {
		if (nums[middle] == target) {
			right = middle;
		} else if (nums[middle] < target) {
			left = middle + 1;
		} else {
			right = middle - 1;
		}
		middle = (left + right) / 2;
	}

	return left;
}

int search_last(int *nums, int start, int end, int target)
{
	int left = start, right = end;
	int middle = (left + right) / 2;

	while ((left + 1) < right) {
		if (nums[middle] == target) {
			left = middle;
		} else if (nums[middle] > target) {
			right = middle - 1;
		} else {
			left = middle + 1;
		}
		middle = (left + right) / 2;
	}

	return ((nums[right] == target) ? right : left);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *search_range(int *nums, int numsSize, int target, int *returnSize)
{
	int left = 0, right = numsSize - 1;
	int middle = (left + right) / 2;
	int i = 0;
	int *range;

	*returnSize = 2;
	range = calloc(1, sizeof(int) * (*returnSize));
	range[0] = -1;
	range[1] = -1;

	while (left <= right) {
		if (nums[middle] == target) {
			range[0] = search_first(nums, left, middle, target);
			range[1] = search_last(nums, middle, right, target);
			return range;
		} else if (nums[middle] > target) {
			right = middle - 1;
		} else {
			left = middle + 1;
		}
		middle = (left + right) / 2;
	}

	return range;
}

int main(void)
{
	int nums[1024] = {0};
	int numsSize, returnSize;
	int target;
	int i;

	scanf("%d %d", &numsSize, &target);
	for (i = 0; i < numsSize; i++) {
		scanf("%d", &nums[i]);
	}

	int *range = search_range(nums, numsSize, target, &returnSize);

	printf("[%d, %d]\n", range[0], range[1]);

	return 0;
}


