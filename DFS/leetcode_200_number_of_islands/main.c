#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int island(char **grid, int row, int col, int x, int y, int **visited)
{
    /* ended position */
    if ((x < 0) || (y < 0) || (x >= row) || (y >= col)) {
        return 1;
    }
    if ((grid[x][y] == '0') || (visited[x][y] == 1)) {
        return 1;
    }

    visited[x][y] = 1;
    /* options: up/right/down/left */
    if (island(grid, row, col, x - 1, y, visited)
		& island(grid, row, col, x, y + 1, visited)
		& island(grid, row, col, x + 1, y, visited)
		& island(grid, row, col, x, y - 1, visited)) {
        return 1;
    }

    return 0;
}

int numIslands(char **grid, int gridSize, int *gridColSize)
{
    int i = 0;
    int j = 0;
    int row = gridSize;
    int col = gridColSize[0];
    int **visited = NULL;
    int num = 0;

	if ((grid == NULL) || (gridSize == 0)) {
		return 0;
	}

	visited = calloc(1, sizeof(int *) * row);
    for (i = 0; i < row; i++) {
        visited[i] = calloc(1, sizeof(int) * col);
    }

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if ((!visited[i][j]) && (grid[i][j] == '1')) {
                if (island(grid, row, col, i, j, visited)) {
                    num++;
                }
            }
        }
    }

    for (i = 0; i < row; i++) {
        free(visited[i]);
    }
    free(visited);

    return num;
}

int main(void)
{
	char **grid = NULL;
	int gridSize = 0;
	int col = 0;
	int *gridColSize = NULL;
	int i = 0;

	scanf("%d %d", &gridSize, &col);
	grid = calloc(1, sizeof(char *) * gridSize);
	gridColSize = calloc(1, sizeof(int) * gridSize);
	for (i = 0; i < gridSize; i++) {
		grid[i] = calloc(1, sizeof(char *) * col);
		scanf("%s", grid[i]);
		gridColSize[i] = col;
	}

	printf("%d\n", numIslands(grid, gridSize, gridColSize));

	for (i = 0; i < gridSize; i++) {
		free(grid[i]);
	}
	free(grid);
	free(gridColSize);

	return 0;
}
