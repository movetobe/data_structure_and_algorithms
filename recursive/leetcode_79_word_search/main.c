#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MATRIX_LEN 1024

int compare_word(char **board, int row, int col, int x, int y, char *word, int index, int **visited)
{
	/* ended position: index is last one */
	if (index == (strlen(word))) {
		return 1;
	}

	/* options */
	if ((x >= 0) && (x < row) && (y >= 0) && (y < col)
		&& (!visited[x][y]) && (word[index] == board[x][y])) {
		visited[x][y] = 1;
		if (compare_word(board, row, col, x + 1, y, word, index + 1, visited)
			|| compare_word(board, row, col, x, y + 1, word, index + 1, visited)
			|| compare_word(board, row, col, x - 1, y, word, index + 1, visited)
			|| compare_word(board, row, col, x, y - 1, word, index + 1, visited)) {
			return 1;
		}
		/* backtrace */
		visited[x][y] = 0;
	}

	return 0;
}
int word_search(char **board, int boardSize, int *boardColSize, char *word)
{
	int x = 0;
	int y = 0;
	int i = 0;
	int **visited = calloc(1, sizeof(int *) * boardSize);
	int bingo = 0;

	for (x = 0; x < boardSize; x++) {
		visited[x] = calloc(1, sizeof(int) * boardColSize[x]);
	}

	for (x = 0; x < boardSize; x++) {
		for (y = 0; y < boardColSize[x]; y++) {
			for (i = 0; i < boardSize; i++) {
				memset(visited[i], 0, sizeof(int) * boardColSize[i]);
			}
			if (compare_word(board, boardSize, boardColSize[x], x, y, word, 0, visited)) {
				bingo = 1;
				break;
			}
		}
	}

	for (x = 0; x < boardSize; x++) {
		free(visited[x]);
	}
	free(visited);

	return bingo;
}

int main(void)
{
	int boardSize = 0;
	int x = 0;
	char **board = NULL;
	int *boardColSize = NULL;
	char word[MAX_MATRIX_LEN] = {0};

	scanf("%d", &boardSize);
	boardColSize = calloc(1, sizeof(int) * boardSize);
	scanf("%d", &boardColSize[0]);
	for (x = 0; x < boardSize; x++) {
		boardColSize[x] = boardColSize[0];
	}
	board = calloc(1, sizeof(int *) * boardSize);
	for (x = 0; x < boardSize; x++) {
		board[x] = calloc(1, sizeof(int) * boardColSize[0]);
		scanf("%s", board[x]);
	}

	scanf("%s", word);

	printf("%d\n", word_search(board, boardSize, boardColSize, word));

	for (x = 0; x < boardSize; x++) {
		free(board[x]);                                                  
	}
	free(board);
	free(boardColSize);

	return 0;
}
