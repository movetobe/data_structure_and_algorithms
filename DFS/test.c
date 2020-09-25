#include<stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_N 200

int longest_recu(char words[][MAX_N], int num, int visited[], char *word)
{
	int i;
	int len;
	int max = 0;
	int has_next = 0;

	for (i = 0; i < num; i++) {
		if (!visited[i] && word[strlen(word) - 1] == words[i][0]) {
			has_next = 1;
			visited[i] = 1;
			len = longest_recu(words, num, visited, words[i]);
			if (max < len + 1) {
				max = len + 1;
			}
			visited[i] = 0;
		}
	}
	if (!has_next) {
		return 0;
	}
	return max;
}

int longest(char words[][MAX_N], int num, int visited[])
{
	int i;
	int len;;
	int max = 0;

	for (i = 0; i < num; i++) {
		visited[i] = 1;
		len = longest_recu(words, num, visited, words[i]);
		if (max < len + 1) {
			max = len + 1;
		}
		visited[i] = 0;
	}
	return max;
}
int main(void)
{
	int num;
	char words[MAX_N][MAX_N];
	int visited[MAX_N];
	int i;

	scanf("%d", &num);
	for (i = 0; i < num; i++) {
		scanf("%s", words[i]);
	}

	printf("%d\n", longest(words, num, visited));
	return 0;
}
