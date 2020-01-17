#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct position {
	int x;
	int y;
};
int paths(int **grid, int row, int col, struct position *curr, struct position *end,
			int **visited, int whole_len)
{
	int up, right, down, left;
	struct position next;

	/* ended position: all positions are walk through and arrive at end */
	if ((whole_len < 0) && (curr->x == end->x) && (curr->y == end->y)) {
		return 1;
	}

	if ((curr->x < 0) || (curr->y < 0) || (curr->x >= row) || (curr->y >= col)) {
		return 0;
	}

	if ((visited[curr->x][curr->y]) || (grid[curr->x][curr->y] == -1) || (grid[curr->x][curr->y] == 2)) {
		return 0;
	}

	visited[curr->x][curr->y] = 1;
	/* options: up/right/down/left */
	next.x = curr->x - 1;
	next.y = curr->y;
	up = paths(grid, row, col, &next, end, visited, whole_len - 1);

	next.x = curr->x;
	next.y = curr->y + 1;
	right = paths(grid, row, col, &next, end, visited, whole_len - 1);

	next.x = curr->x + 1;
	next.y = curr->y;
	down = paths(grid, row, col, &next, end, visited,  whole_len - 1);

	next.x = curr->x;
	next.y = curr->y - 1;
	left = paths(grid, row, col, &next, end, visited, whole_len - 1);

	/* backtrace */
	visited[curr->x][curr->y] = 0;

	return (up + right + down + left);
}

int uniquePathsIII(int **grid, int gridSize, int *gridColSize)
{
	int i, j;
	struct position start, end;
	int whole_len = 0;
	int **visited = calloc(1, sizeof(int *) * gridSize);
	int paths_num;

	for (i = 0; i < gridSize; i++) {
		visited[i] = calloc(1, sizeof(int) * gridColSize[0]);
	}

	for (i = 0; i < gridSize; i++) {
		for (j = 0; j < gridColSize[0]; j++) {
			if (grid[i][j] == 1) {
				start.x = i;
				start.y = j;
			} else if (grid[i][j] == 2) {
				end.x = i;
				end.y = j;
			} else if (grid[i][j] == 0) {
				whole_len++;
			}
		}
	}

	paths_num = paths(grid, gridSize, gridColSize[0], &start, &end, visited, whole_len);

	for (i = 0; i < gridSize; i++) {
		free(visited[i]);
	}
	free(visited);

	return paths_num;
}

int main(void)
{
	int gridSize;
	int *gridColSize;
	int **grid;
	int i, j;

	scanf("%d", &gridSize);
	gridColSize = calloc(1, sizeof(int) * gridSize);
	scanf("%d", &gridColSize[0]);
	grid = calloc(1, sizeof(int *) * gridSize);
	for (i = 0; i < gridSize; i++) {
		grid[i] = calloc(1, sizeof(int) * gridColSize[0]);
		gridColSize[i] = gridColSize[0];
		for (j = 0; j < gridColSize[i]; j++) {
			scanf("%d", &grid[i][j]);
		}
	}

	printf("%d\n", uniquePathsIII(grid, gridSize, gridColSize));

	for (i = 0; i < gridSize; i++) {
		free(grid[i]);
	}
	free(grid);
	free(gridColSize);

	return 0;
}
