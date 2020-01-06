#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
	CROSS_NONE,
	CROSS_NO,
	CROSS_YES,
	CROSS_MAX
};
int next(int *stones, int stones_size, int stone, int index)
{
	int i;

	for (i = index + 1; i < stones_size; i++) {
		if (stones[i] == stone) {
			return i;
		}
	}

	return -1;
}

int cross(int *stones, int stones_size, int index, int step, int **cross_hist)
{
	int stone = stones[index] + step;
	int next_index = 0;

	/* ended position: step to last one */
	if (stone == stones[stones_size - 1]) {
		return CROSS_YES;
	}

	/* had been solved */
	if (cross_hist[index][step] > CROSS_NONE) {
		return cross_hist[index][step];
	}

	/* next stone position */
	next_index = next(stones, stones_size, stone, index);
	if (next_index < 0) {
		return CROSS_NO;
	}

	/* options */
	if ((cross(stones, stones_size, next_index, step + 1, cross_hist) == CROSS_YES)
		|| (cross(stones, stones_size, next_index, step, cross_hist) == CROSS_YES)
		|| (cross(stones, stones_size, next_index, step - 1, cross_hist) == CROSS_YES)) {
		cross_hist[index][step] = CROSS_YES;
		return CROSS_YES;
	}

	cross_hist[index][step] = CROSS_NO;
	return CROSS_NO;
}

int canCross(int *stones, int stonesSize)
{
	int i = 0;
	int **cross_hist = calloc(1, sizeof(int *) * stonesSize);
	int ret = 0;

    for (i = 0; i < stonesSize; i++) {
        cross_hist[i] = calloc(1, sizeof(int) * stonesSize);
    }

	ret = cross(stones, stonesSize, 0, 1, cross_hist);

	for (i = 0; i < stonesSize; i++) {
		free(cross_hist[i]);
	}
	free(cross_hist);

	return ((ret == CROSS_YES) ? 1 : 0);
}

int main(void)
{
	int stonesSize = 0;
	int *stones = NULL;
	int i = 0;

	scanf("%d", &stonesSize);
	stones = calloc(1, sizeof(int) * stonesSize);
	for (i = 0; i < stonesSize; i++) {
		scanf("%d", &stones[i]);
	}
	printf("%d\n", canCross(stones, stonesSize));
	free(stones);
	return 0;
}
