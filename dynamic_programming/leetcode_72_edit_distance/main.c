#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * ->word1[i], ->word2[j]
 * ed[i][j] = ed[i - 1][j - 1] if word1[i] == word2[j]
 * ed[i][j] = min {ed[i - 1][j], ed[i][j - 1], ed[i - 1][j - 1]} + 1 if word1[i] != word2[j]
 * ed[i - 1][j] -> delete element in word1
 * ed[i][j - 1] -> add element in word1
 * ed[i - 1][j - 1] -> replace element in word1
 */

enum {
	EDIT_ACTION_NONE,
	EDIT_ACTION_DELETE,
	EDIT_ACTION_ADD,
	EDIT_ACTION_REPLACE,
	EDIT_ACTION_MAX
};

static char actions[] = {'N', 'D', 'A', 'R'};

int min(int a, int b, int c, int *action)
{
	int m = a;

	*action = EDIT_ACTION_DELETE;
	if (b < m) {
		m = b;
		*action = EDIT_ACTION_ADD;
	} else if(c < m) {
		m = c;
		*action = EDIT_ACTION_REPLACE;
	}

	return m;
}

int min_distance(char *word1, char *word2)
{
	int len1 = strlen(word1);
	int len2 = strlen(word2);
	int **ed = calloc(1, sizeof(int *) * (len1 + 1));
	int **ea = calloc(1, sizeof(int *) * (len1 + 1));
	int i, j;
	int min_dist;

	for (i = 0; i <= len1; i++) {
		ed[i] = calloc(1, sizeof(int) * (len2 + 1));
		ea[i] = calloc(1, sizeof(int) * (len2 + 1));
	}

	for (i = 1; i <= len1; i++) {
		ed[i][0] = i;
	}
	for (j = 1; j <= len2; j++) {
		ed[0][j] = j;
	}

	for (i = 1; i <= len1; i++) {
		for (j = 1; j <= len2; j++) {
			if (word1[i - 1] == word2[j - 1]) {
				ed[i][j] = ed[i - 1][j - 1];
			} else {
				ed[i][j] = min(ed[i - 1][j], ed[i][j - 1], ed[i - 1][j - 1], &ea[i][j]) + 1;
			}
		}
	}
	min_dist = ed[len1][len2];

	for (i = 1; i <= len1; i++) {
		for (j = 1; j <= len2; j++) {
			printf("%c ", actions[ea[i][j]]);
			printf("(%d) ", ed[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i <= len1; i++) {
		free(ed[i]);
		free(ea[i]);
	}
	free(ed);
	free(ea);

	return min_dist;
}

int main(void)
{
	char word1[1024] = {0};
	char word2[1024] = {0};

	scanf("%s", word1);
	scanf("%s", word2);

	printf("%d\n", min_distance(word1, word2));

	return 0;
}
