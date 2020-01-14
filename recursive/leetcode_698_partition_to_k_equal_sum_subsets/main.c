#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int can_partition(int *nums, int numsSize, int index, int k, long subsum, int *visited)
{
	int i = 0;

	/* ended position */
	if (index == numsSize) {
		return 1;
	}

	/* options */
	for (i = 0; i < k; i++) {
		if (visited[i] + nums[index] <= subsum) {
			visited[i] += nums[index];
			if (can_partition(nums, numsSize, index + 1, k, subsum, visited)) {
				return 1;
			}
			visited[i] -= nums[index];
		}
		if (visited[i] == 0) {
			return 0;
		}
	}

	return 0;
}
int canPartitionKSubsets(int* nums, int numsSize, int k)
{
	int i = 0;
	long sum = 0;
	long subsum = 0;
	int *visited = calloc(1, sizeof(int) * numsSize);
	int can = 0;

	for (i = 0; i < numsSize; i++) {
		sum += nums[i];
	}

	if ((sum % k) != 0) {
		return 0;
	}
	subsum = sum / k;

	for (i = 0; i < numsSize; i++) {
		if (nums[i] > subsum) {
			return 0;
		}
	}

	can = can_partition(nums, numsSize, 0, k, subsum, visited);
	free(visited);
	return can;
}
int main(void)
{
	int numsSize = 0;
	int k = 0;
	int i = 0;
	int nums[1024] = {0};

	scanf("%d %d", &numsSize, &k);
	for (i = 0; i < numsSize; i++) {
		scanf("%d", &nums[i]);
	}

	printf("%d\n", canPartitionKSubsets(nums, numsSize, k));

	return 0;
}
