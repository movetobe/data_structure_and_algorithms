#include <stdio.h>
#include <stdlib.h>

int num_binary_search_trees(int start, int end, int **results)
{
	int index = 0;
	int nums = 0;
	int left = 0;
	int right = 0;

	/* ended position: only one nunber */
	if (start == end) {
		return 1;
	}

	/* options, start->end one number as root */
	for (index = start; index <= end; index++) {
		if (index > 0) {
			if (results[start][index - 1] > 0) {
				left = results[start][index - 1];
			} else {
				left = num_binary_search_trees(start, index - 1, results);
				results[start][index - 1] = left;
			}
		}
		if (index < end) {
			if (results[index + 1][end] > 0) {
				right = results[index + 1][end];
			} else {
				right = num_binary_search_trees(index + 1, end, results);
				results[index + 1][end] = right;
			}
		}
		nums += ((left > 0) && (right > 0)) ? (left * right) : (left + right);
	}

	return nums;
}

int num_trees(int n)
{
	int nums = 0;
	int **results = calloc(1, sizeof(int *) * (n + 1));
	int i = 0;

	for (i = 0; i < (n + 1); i++) {
		results[i] = calloc(1, sizeof(int) * (n + 1));
	}

	nums = num_binary_search_trees(1, n, results);

	for (i = 0; i < (n + 1); i++) {
		free(results[i]);
	}
	free(results);
	return nums;
}

int main(void)
{
	int n = 0;

	scanf("%d", &n);

	printf("%d\n", num_trees(n));

	return 0;
}
