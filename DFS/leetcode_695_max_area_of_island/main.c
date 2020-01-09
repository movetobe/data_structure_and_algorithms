#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int area(int **grid, int row, int col, int x, int y, int **visited)
{
    int up = 0;
    int right = 0;
    int down = 0;
    int left = 0;

    if ((x < 0) || (y < 0) || (x >= row) || (y >= col)) {
        return 0;
    }
    if (visited[x][y] || (grid[x][y] == 0)) {
        return 0;
    }

    visited[x][y] = 1;

    up = area(grid, row, col, x - 1, y, visited);
    right = area(grid, row, col, x, y + 1, visited);
    down = area(grid, row, col, x + 1, y, visited);
    left = area(grid, row, col, x, y - 1, visited);

    return (up + right + down + left + 1);
}

int maxAreaOfIsland(int **grid, int gridSize, int *gridColSize)
{
    int i = 0;
    int j = 0;
    int **visited = NULL;
    int max_area = 0;
    int curr_area = 0;

    if ((grid == NULL) || (gridSize == 0)) {
        return 0;
    }

    visited = calloc(1, sizeof(int *) * gridSize);
    for (i = 0; i < gridSize; i++) {
        visited[i] = calloc(1, sizeof(int) * gridColSize[0]);
    }

    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < gridColSize[0]; j++) {
            if ((!visited[i][j]) && (grid[i][j])) {
                curr_area = area(grid, gridSize, gridColSize[0], i, j, visited);
                max_area = curr_area > max_area ? curr_area : max_area;
            }
        }
    }

    for (i = 0; i < gridSize; i++) {
        free(visited[i]);
    }
    free(visited);

    return max_area;
}

int main(void)
{
	int i = 0;
	int j = 0;
	int gridSize = 0;
	int **grid = NULL;
	int *gridColSize = NULL;

	scanf("%d", &gridSize);
	grid = calloc(1, sizeof(int *) * gridSize);
	gridColSize = calloc(1, sizeof(int) * gridSize);
	scanf("%d", &gridColSize[0]);
	for (i = 0; i < gridSize; i++) {
		grid[i] = calloc(1, sizeof(int) * gridColSize[0]);
		gridColSize[i] = gridColSize[0];
		for (j = 0; j < gridColSize[0]; j++) {
			scanf("%d,", &grid[i][j]);
		}
	}

	printf("%d\n", maxAreaOfIsland(grid, gridSize, gridColSize));

	for (i = 0; i < gridSize; i++) {
		free(grid[i]);
	}
	free(grid);
	free(gridColSize);
	return 0;
}
