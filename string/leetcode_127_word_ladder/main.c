#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define QUEUE_MAX 128
struct queue {
	int value[QUEUE_MAX];
	int front;
	int rear;
};

void queue_init(struct queue *q)
{
	memset(q, 0, sizeof(struct queue));
}
int queue_empty(struct queue *q)
{
	return (q->rear == q->front);
}
int queue_full(struct queue *q)
{
	return (((q->rear + 1) % QUEUE_MAX) == q->front);
}
int enqueue(struct queue *q, int value)
{
	if (queue_full(q)) {
		return -1;
	}
	q->value[q->rear] = value;
	q->rear = (q->rear + 1) % QUEUE_MAX;

	return 0;
}
int dequeue(struct queue *q)
{
	int value;

	if (queue_empty(q)) {
		return -1;
	}
	value = q->value[q->front];
	q->front = (q->front + 1) % QUEUE_MAX;

	return value;
}
int next_word(char *s1, char *s2)
{
	int len = strlen(s1);
	int i;
	int once = 0;

	for (i = 0; i < len; i++) {
		if (s1[i] != s2[i]) {
			once++;
		}
		if (once > 1) {
			break;
		}
	}
	return (once == 1);
}

int ladderLength(char *beginWord, char *endWord, char **wordList, int wordListSize)
{
	int *visited = calloc(1, sizeof(int) * wordListSize);
	int *step_cache = calloc(1, sizeof(int) * wordListSize);
	int min_ladder_len;

	min_ladder_len = word_ladder(beginWord, endWord, wordList, wordListSize, visited, step_cache);

	free(visited);
	free(step_cache);

	return (min_ladder_len < INT_MAX ? (min_ladder_len + 1) : 0);
}

int main(void)
{
	char beginWord[8] = {0};
	char endWord[8] = {0};
	char **wordList;
	int wordListSize;
	int i;

	scanf("%s", beginWord);
	scanf("%s", endWord);

	scanf("%d", &wordListSize);
	wordList = calloc(1, sizeof(char *) * wordListSize);

	for (i = 0; i < wordListSize; i++) {
		wordList[i] = calloc(1, sizeof(char) * 8);
		scanf("%s", wordList[i]);
	}

	printf("%d\n", ladderLength(beginWord, endWord, wordList, wordListSize));

	for (i = 0; i < wordListSize; i++) {
		free(wordList[i]);
	}
	free(wordList);

	return 0;
}
