#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define QUEUE_LEN 1024
struct position {
	int x;
	int y;
};
struct queue {
	struct position pos[QUEUE_LEN];
	int front;
	int rear;
};
struct queue *init_queue(void)
{
	struct queue *q = calloc(1, sizeof(struct queue));

	return q;
}
void enqueue(struct queue *q, struct position *pos)
{
	q->pos[q->rear].x = pos->x;
	q->pos[q->rear].y = pos->y;
	q->rear = (q->rear + 1) % QUEUE_LEN;
}
void dequeue(struct queue *q, struct position *pos)
{
	pos->x = q->pos[q->front].x;
	pos->y = q->pos[q->front].y;
	q->front = (q->front + 1) % QUEUE_LEN;
}
int queue_size(struct queue *q)
{
	if (q->rear >= q->front) {
		return (q->rear - q->front);
	}
	return (q->rear + QUEUE_LEN - q->front);
}

int cross_obstacles(int **matrix, struct position *start, struct position *end, int k)
{
	int row = end->x + 1, col = end->y + 1;
	int **cost = calloc(1, sizeof(int *) * row);
	int **visited = calloc(1, sizeof(int *) * row);
	int i, j;
	struct position current, next;
	struct queue *q = init_queue();
	int level_size;
	struct position directions[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	int path_len = 0;;
	int find = 0;

	for (i = 0; i < row; i++) {
		cost[i] = calloc(1, sizeof(int) * col);
		visited[i] = calloc(1, sizeof(int) * col);
		for (j = 0; j < col; j++) {
			cost[i][j] = INT_MAX;
		}
	}

	/* enqueue first point, start/end must be 0 */
	enqueue(q, start);
	visited[start->x][start->y] = 1;
	cost[start->x][start->y] = 0;
	while (queue_size(q) > 0) {
		level_size = queue_size(q);
		path_len++;
		for (i = 0; i < level_size; i++) {
			dequeue(q, &current);
			visited[current.x][current.y] = 0;
			if (current.x == end->x && current.y == end->y) {
				find = 1;
				break;
			}
			for (j = 0; j < 4; j++) {
				next.x = current.x + directions[j].x;
				next.y = current.y + directions[j].y;
				if ((next.x < 0) || (next.x >= row) || (next.y < 0) || (next.y >= col)) {
					continue;
				}
				/* next is not an obstacles */
				if ((matrix[next.x][next.y] == 0) && (cost[next.x][next.y] > cost[current.x][current.y])) {
					cost[next.x][next.y] = cost[current.x][current.y];
					if (!visited[next.x][next.y]) {
						enqueue(q, &next);
						visited[next.x][next.y] = 1;
					}
				}
				if (matrix[next.x][next.y] && (cost[current.x][current.y] + 1 <= k)
					&& (cost[next.x][next.y] > cost[current.x][current.y] + 1)) {
					/* next cost is greater than from current->next */
					cost[next.x][next.y] = cost[current.x][current.y] + 1;
					if (!visited[next.x][next.y]) {
						enqueue(q, &next);
						visited[next.x][next.y] = 1;
					}
				}
			}
		}
		if (find) {
			break;
		}
	}
	for (i = 0; i < row; i++) {
		free(cost[i]);
		free(visited[i]);
	}
	free(cost);
	free(visited);
	destroy_queue(q);
	return (find ? path_len - 1: -1);
}
int main(void)
{
	int **matrix;
	int i, j;
	int row, col;
	struct position start, end;
	int k;

	scanf("%d %d", &row, &col);
	matrix = calloc(1, sizeof(int *) * row);
	for (i = 0; i < row; i++) {
		matrix[i] = calloc(1, sizeof(int) * col);
		for (j = 0; j < col; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	scanf("%d", &k);

	start.x = 0;
	start.y = 0;
	end.x = row - 1;
	end.y = col -1;

	printf("%d\n", cross_obstacles(matrix, &start, &end, k));

	for (i = 0; i < row; i++) {
		free(matrix[i]);
	}
	free(matrix);
	return 0;
}
