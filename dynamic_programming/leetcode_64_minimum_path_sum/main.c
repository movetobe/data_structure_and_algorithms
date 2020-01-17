#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ps[i][j] = max{ps[i - 1][j], p[i][j - 1]} + grid[i][j] */
int minPathSum(int **grid, int gridSize, int *gridColSize)
{
	int i, j;
	int **ps = calloc(1, sizeof(int *) * gridSize);
	int min_sum = 0;

	for (i = 0; i < gridSize; i++) {
		ps[i] = calloc(1, sizeof(int) * gridColSize[0]);
	}

	ps[0][0] = grid[0][0];

	for (i = 1; i < gridSize; i++) {
		ps[i][0] = ps[i - 1][0] + grid[i][0];
	}

	for (j = 1; j < gridColSize[0]; j++) {
		ps[0][j] = ps[0][j - 1] + grid[0][j];
	}

	for (i = 1; i < gridSize; i++) {
		for (j = 1; j < gridColSize[0]; j++) {
			ps[i][j] = (ps[i - 1][j] < ps[i][j - 1] ? ps[i - 1][j] : ps[i][j - 1]) + grid[i][j];
		}
	}

	min_sum = ps[gridSize - 1][gridColSize[0] - 1];

	for (i = 0; i < gridSize; i++) {
		free(ps[i]);
	}
	free(ps);

	return min_sum;
}

int main(void)
{
	int gridSize;
	int *gridColSize;
	int **grid;
	int i, j;

	scanf("%d", &gridSize);
	gridColSize = calloc(1, sizeof(int) * gridSize);
	grid = calloc(1, sizeof(int *) * gridSize);
	scanf("%d", &gridColSize[0]);

	for (i = 0; i < gridSize; i++) {
		grid[i] = calloc(1, sizeof(int) * gridColSize[0]);
		gridColSize[i] = gridColSize[0];
		for (j = 0; j < gridColSize[i]; j++) {
			scanf("%d", &grid[i][j]);
		}
	}

	printf("%d\n", minPathSum(grid, gridSize, gridColSize));

	for (i = 0; i < gridSize; i++) {
		free(grid[i]);
	}
	free(grid);

	return 0;
}
