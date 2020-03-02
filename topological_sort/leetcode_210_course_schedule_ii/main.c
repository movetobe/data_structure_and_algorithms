#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_LEN 1024
struct queue {
	int value[QUEUE_LEN];
	int front;
	int rear;
};
struct queue *init_queue(void)
{
	struct queue *q = calloc(1, sizeof(struct queue));
	return q;
}
void destroy_queue(struct queue *q)
{
	free(q);
}
void enqueue(struct queue *q, int value)
{
	q->value[q->rear] = value;
	q->rear = (q->rear + 1) % QUEUE_LEN;
}
int dequeue(struct queue *q)
{
	int value = q->value[q->front];
	q->front = (q->front + 1) % QUEUE_LEN;
	return value;
}
int queue_empty(struct queue *q)
{
	return (q->front == q->rear);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize)
{
	int *returnArray = calloc(1, sizeof(int) * numCourses);
	int **graph = calloc(1, sizeof(int *) * numCourses);
	int i, j;
	int *ingree = calloc(1, sizeof(int) * numCourses);
	int current;
	struct queue *q = init_queue();

	for (i = 0; i < numCourses; i++) {
		graph[i] = calloc(1, sizeof(int) * numCourses);
	}

	for (i = 0; i < prerequisitesSize; i++) {
		graph[prerequisites[i][1]][prerequisites[i][0]] = 1;
		ingree[prerequisites[i][0]]++;
	}

	*returnSize = 0;
	for (j = 0; j < numCourses; j++) {
		if (ingree[j] == 0) {
			enqueue(q, j);
		}
	}	
	while (!queue_empty(q)) {
		current = dequeue(q);
		returnArray[*returnSize] = current;
		*returnSize = *returnSize + 1;
		for (j = 0; j < numCourses; j++) {
			if (graph[current][j]) {
				ingree[j]--;
				graph[current][j] = 0;
				if (ingree[j] == 0) {
					enqueue(q, j);
				}
			}
		}
	}

	/* clear if cannot schedule all courses. */
	if (*returnSize < numCourses) {
		*returnSize = 0;
	}
	destroy_queue(q);
	free(ingree);
	for (i = 0; i < numCourses; i++) {
		free(graph[i]);
	}
	free(graph);

	return returnArray;
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
	int returnSize = 0;
    int *returnArray = findOrder(numCourses, prerequisites, prerequisitesSize, prerequisitesColSize, &returnSize);
	for (i = 0; i < returnSize; i++) {
		printf("%d ", returnArray[i]);
	}
	printf("\n");
                                                                                
    /* should free memory */                                                    
    return 0;                                                                   
} 
