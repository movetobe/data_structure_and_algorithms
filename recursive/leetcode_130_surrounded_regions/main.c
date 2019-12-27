#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct position {
    int x;
    int y;
};

enum {
    BOUNDARY_N,
    BOUNDARY_O,
    BOUNDARY_X,
    BOUNDARY_M
};

int solve_recu(char **board, int boardSize, int boardColSize, int x, int y,
                    int **visited, struct position *pos, int *index)
{
    int down = 0;
    int right = 0;
    int up = 0;
    int left = 0;

    /* ended position */
    if ((x < 0) || (y < 0) || (x >= boardSize) || (y >= boardColSize)) {
        return BOUNDARY_O;
    }

    if ((!visited[x][y]) && (board[x][y] == 'O')) {
        visited[x][y] = 1;
        pos[*index].x = x;
        pos[*index].y = y;
        *index = *index + 1;
        down = solve_recu(board, boardSize, boardColSize, x + 1, y, visited, pos, index);
        right = solve_recu(board, boardSize, boardColSize, x, y + 1, visited, pos, index);
        up = solve_recu(board, boardSize, boardColSize, x - 1, y, visited, pos, index);
        left = solve_recu(board, boardSize, boardColSize, x, y - 1, visited, pos, index);
        if ((down == BOUNDARY_O) || (right == BOUNDARY_O) || (up == BOUNDARY_O) || (left == BOUNDARY_O)) {
            return BOUNDARY_O;
        }
    }
    return BOUNDARY_X;
}

void solve(char** board, int boardSize, int* boardColSize)
{
    int i = 0;
    int j = 0;
    int **visited = NULL;
    struct position *pos = NULL;
    int pos_index = 0;

	if ((board == NULL) || (boardSize == 0) || (boardColSize == NULL)) {
		return;
	}

	visited = calloc(1, sizeof(int *) * boardSize);                       
	pos = calloc(1, sizeof(struct position) * boardSize * boardColSize[0]);
    for (i = 0; i < boardSize; i++) {
        visited[i] = calloc(1, sizeof(int) * boardColSize[i]);
    }

    for (i = 1; i < boardSize - 1; i++) {
        for (j = 1; j < boardColSize[i] - 1; j++) {
            if ((board[i][j] != 'O') || (visited[i][j])) {
                continue;
            }
            pos_index = 0;
            if (solve_recu(board, boardSize, boardColSize[0], i, j, visited, pos, &pos_index) == BOUNDARY_X) {
                for (pos_index = pos_index - 1; pos_index >= 0; pos_index--) {
                    board[pos[pos_index].x][pos[pos_index].y] = 'X';
                }
            }
        }
    }

    for (i = 0; i < boardSize; i++) {
        free(visited[i]);
    }
    free(visited);
    free(pos);

    return;
}

int main(void)
{
	char **board = NULL;
	int boardSize = 0;
	int *boardColSize = NULL;
	int i = 0;

	scanf("%d", &boardSize);
	board = calloc(1, sizeof(char *) * boardSize);
	boardColSize = calloc(1, sizeof(int) * boardSize);

	scanf("%d", &boardColSize[0]);
	for (i = 0; i < boardSize; i++) {
		boardColSize[i] = boardColSize[0];
		board[i] = calloc(1, sizeof(char) * boardColSize[i]);
		scanf("%s", board[i]);
	}

	solve(board, boardSize, boardColSize);

	printf("\n");
	for (i = 0; i < boardSize; i++) {
		printf("%s\n", board[i]);
		free(board[i]);
	}
	free(board);
	free(boardColSize);

	return 0;
}
