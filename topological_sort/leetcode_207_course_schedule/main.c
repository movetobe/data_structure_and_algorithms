#include <stdio.h>
#include <stdlib.h>

int finish_courses(int **graph, int numCourses, int *ingree, int course)
{
	int i;
	int finish = 0;

	/* decrease ingree is course */
	for (i = 0; i < numCourses; i++) {
		if (graph[course][i]) {
			ingree[i]--;
			graph[course][i] = 0;
			if (ingree[i] == 0) {
				ingree[i] = -1;
				finish += finish_courses(graph, numCourses, ingree, i);
			}
		}
	}
	return (finish + 1);
}

int can_finish(int numCourses, int **prerequisites, int prerequisitesSize, int *prerequisitesColSize)
{
	int i, j;
	int *ingree = calloc(1, sizeof(int) * numCourses);
	int **graph = calloc(1, sizeof(int *) * numCourses);
	int finish = 0;

	for (i = 0; i < numCourses; i++) {
		graph[i] = calloc(1, sizeof(int) * numCourses);
	}

	for (i = 0; i < prerequisitesSize; i++) {
		graph[prerequisites[i][1]][prerequisites[i][0]] = 1;
	}

	for (j = 0; j < numCourses; j++) {
		for (i = 0; i < numCourses; i++) {
			ingree[j] += graph[i][j];
		}
	}

	for (j = 0; j < numCourses; j++) {
		if (ingree[j] == 0) {
			ingree[j] = -1;
			finish += finish_courses(graph, numCourses, ingree, j);
		}
	}

	free(ingree);
	for(i = 0; i < numCourses; i++) {
		free(graph[i]);
	}
	free(graph);
	return (finish == numCourses);
}

int main(void)
{
	int numCourses;
	int **prerequisites;
	int prerequisitesSize;
	int *prerequisitesColSize;
	int i, j;

	scanf("%d, %d", &numCourses, &prerequisitesSize);

	prerequisites = calloc(1, sizeof(int *) * prerequisitesSize);
	prerequisitesColSize = calloc(1, sizeof(int) * prerequisitesSize);
	for (i = 0; i < prerequisitesSize; i++) {
		prerequisites[i] = calloc(1, sizeof(int) * 2);
		prerequisitesColSize[i] = 2;
		scanf("%d, %d", &prerequisites[i][0], &prerequisites[i][1]);
	}
	printf("%d\n", can_finish(numCourses, prerequisites, prerequisitesSize, prerequisitesColSize));

	/* should free memory */
	return 0;
}
