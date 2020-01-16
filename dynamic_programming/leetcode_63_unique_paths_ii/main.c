#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* p[i][j] = p[i - 1][j] + p[i][j - 1] */
int uniquePathsWithObstacles(int **obstacleGrid, int obstacleGridSize, int *obstacleGridColSize)
{
	int i = 0;
	int j = 0;
	int **p = calloc(1, sizeof(int *) * obstacleGridSize);

	for (i = 0; i < obstacleGridSize; i++) {
		p[i] = calloc(1, sizeof(int) * obstacleGridColSize[i]);
	}

	if (!obstacleGrid[0][0]) {
		p[0][0] = 1;
	}
	for (i = 1; i < obstacleGridSize; i++) {
		if (!obstacleGrid[i][0]) {
			p[i][0] = p[i - 1][0];
		}
	}
	for (i = 1; i < obstacleGridColSize[0]; i++) {
		if (!obstacleGrid[0][i]) {
			p[0][i] = p[0][i - 1];
		}
	}
	for (i = 1; i < obstacleGridSize; i++) {
		for (j = 1; j < obstacleGridColSize[0]; j++) {
			if (!obstacleGrid[i][j]) {
				p[i][j] = p[i - 1][j] + p[i][j - 1];
			} 
		}
	}

	return p[obstacleGridSize - 1][obstacleGridColSize[0] - 1];
}
int main(void)
{
	int obstacleGridSize = 0;
	scanf("%d", &obstacleGridSize);
	int **obstacleGrid = calloc(1, sizeof(int *) * obstacleGridSize);
	int i = 0;
	int j = 0;
	int *obstacleGridColSize = calloc(1, sizeof(int) * obstacleGridSize);
	scanf("%d", &obstacleGridColSize[0]);

	for (i = 0; i < obstacleGridSize; i++) {
		obstacleGrid[i] = calloc(1, sizeof(int) * obstacleGridColSize[0]);
		obstacleGridColSize[i] = obstacleGridColSize[0];
		for (j = 0; j < obstacleGridColSize[i]; j++) {
			scanf("%d", &obstacleGrid[i][j]);
		}
	}
	printf("%d\n", uniquePathsWithObstacles(obstacleGrid, obstacleGridSize, obstacleGridColSize));

	for (i = 0; i < obstacleGridSize; i++) {
		free(obstacleGrid[i]);
	}
	free(obstacleGrid);
	free(obstacleGridColSize);

	return 0;
}
