#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_LEN 1024
static void swap(int *nums, int index1, int index2)
{
	int tmp = 0;

	tmp = nums[index1];
	nums[index1] = nums[index2];
	nums[index2] = tmp;
}
static void permute_recu(int *nums, int nums_size, int index, int **return_array, int *return_size)
{
	int i = 0;

	/* index indicates which step we arrived */
	/* ended position: final element */
	if (index == nums_size) {
		return_array[*return_size] = calloc(1, sizeof(int) * nums_size);
		memcpy(return_array[*return_size], nums, sizeof(int) * nums_size);
		*return_size = *return_size + 1;
		return;
	}

	/* options: in permutations, what options does current "index" can be ? */
	for (i = index; i < nums_size; i++) {
		swap(nums, index, i);
		permute_recu(nums, nums_size, index + 1, return_array, return_size);
		/* backtrace */
		swap(nums, index, i);
	}
	return;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **permute(int *nums, int nums_size, int *return_size, int **return_column_sizes)
{
	int permute_num = 1;
	int **return_array = NULL;
	int *col_sizes = NULL;
	int i = 0;

	*return_size = 0;

	for (i = 1; i <= nums_size; i++) {
		permute_num *= i;
	}

	return_array = calloc(1, sizeof(int *) * permute_num);
	permute_recu(nums, nums_size, 0, return_array, return_size);

	col_sizes = calloc(1, sizeof(int) * (*return_size));
	for (i = 0; i < *return_size; i++) {
		col_sizes[i] = nums_size;
	}
	*return_column_sizes = col_sizes;

	return return_array;
}

int main(void)
{
	int return_size = 0;
	int nums[MAX_NUM_LEN] = {0};
	int nums_size = 0;
	int *return_column_sizes = NULL;
	int **return_array = NULL;
	int i = 0;
	int j = 0;

	scanf("%d", &nums_size);
	for (i = 0; i < nums_size; i++) {
		scanf("%d", &nums[i]);
	}
	return_array = permute(nums, nums_size, &return_size, &return_column_sizes);
	for (i = 0; i < return_size; i++) {
		for (j = 0; j < return_column_sizes[i]; j++) {
			printf("%d ", return_array[i][j]);
		}
		printf("\n");
		free(return_array[i]);
	}
	free(return_array);
	free(return_column_sizes);

	return 0;
}
