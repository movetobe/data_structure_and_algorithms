#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define QUEUE_LEN 1280                                                              
struct position {                                                                  
    int x;                                                                         
    int y;                                                                         
};                                                                                 
struct queue {                                                                     
    struct position value[QUEUE_LEN];                                              
    int front;                                                                     
    int rear;                                                                      
};                                                                                 
                                                                                   
struct queue *init_queue(void)                                                     
{                                                                                  
    struct queue *q = calloc(1, sizeof(struct queue));                             
    return q;                                                                      
}                                                                                  
int queue_full(struct queue *q)                                                    
{                                                                                  
    return (((q->rear + 1) % QUEUE_LEN) == q->front);                              
}                                                                                  
int queue_empty(struct queue *q)                                                   
{                                                                                  
    return (q->rear == q->front);                                                  
}                                                                                  
void enqueue(struct queue *q, struct position *pos)                                
{                                                                                  
    if (queue_full(q)) {                                                           
        return;                                                                    
    }                                                                              
    q->value[q->rear].x = pos->x;                                                  
    q->value[q->rear].y = pos->y;                                                  
    q->rear = (q->rear + 1) % QUEUE_LEN;                                           
}                                                                                  
void dequeue(struct queue *q, struct position *pos) {                              
    if (queue_empty(q)) {                                                          
        return;                                                                    
    }                                                                              
    pos->x = q->value[q->front].x;                                                 
    pos->y = q->value[q->front].y;                                                 
                                                                                   
    q->front = (q->front + 1) % QUEUE_LEN;                                         
}   
void destroy_queue(struct queue *q)                                                 
{                                                                               
    free(q);                                                                    
}                                                                               
                                                                                
/* d[i][j] -> d[i + dx][j + dy] update everytime if the value less. */          
int minCost(int** grid, int gridSize, int* gridColSize){                        
    int i, j;                                                                   
    int **cost = calloc(1, sizeof(int *) * gridSize);        
    int **visited = calloc(1, sizeof(int *) * gridSize);                     
    struct queue *q = init_queue();                                             
    struct position pos = {0, 0}, next;                                         
    struct position direct[] = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};        
    int m;                                                                      
                                                                                
    for (i = 0; i < gridSize; i++) {                                            
        cost[i] = calloc(1, sizeof(int) * gridColSize[i]);                      
        visited[i] = calloc(1, sizeof(int) * gridColSize[i]);
        for (j = 0; j < gridColSize[i]; j++) {                                  
            /* set to be max */                                                 
            cost[i][j] = gridSize + gridColSize[i];                             
        }                                                                       
    }                                                                           
                                                    
    enqueue(q, &pos);
	cost[0][0] = 0;
    visited[pos.x][pos.y] = 1;                                                           
    while (!queue_empty(q)) {                                                
        dequeue(q, &pos);
        visited[pos.x][pos.y] = 0;
        for (i = 1; i <= 4; i++) {                                              
            if ((pos.x + direct[i].x < 0) || (pos.x + direct[i].x >= gridSize)  
                || (pos.y + direct[i].y < 0) || (pos.y + direct[i].y >= gridColSize[0])) {
                continue;                                                       
            }            
            next.x = pos.x + direct[i].x;                                       
            next.y = pos.y + direct[i].y;                                                          
            if ((grid[pos.x][pos.y] == i)                                       
                && (cost[pos.x][pos.y] < cost[pos.x + direct[i].x][pos.y + direct[i].y])) {
                cost[pos.x + direct[i].x][pos.y + direct[i].y] = cost[pos.x][pos.y];
                if (!visited[next.x][next.y]) {
                    enqueue(q, &next);    
                    visited[next.x][next.y] = 1;
                }
            } else if ((cost[pos.x][pos.y] + 1) < cost[pos.x + direct[i].x][pos.y + direct[i].y]){
                cost[pos.x + direct[i].x][pos.y + direct[i].y] = cost[pos.x][pos.y] + 1;
                if (!visited[next.x][next.y]) {
                    enqueue(q, &next);    
                    visited[next.x][next.y] = 1;
                }
            }                                                                  
        }                                                                       
    }                                                                           
                                                                                
    m = cost[gridSize - 1][gridColSize[0] - 1];                                 
    destroy_queue(q);                                                           
    for (i = 0; i < gridSize; i++) {                                            
        free(cost[i]);                                     
        free(visited[i]);                     
    }     
        free(cost);    
        free(visited);                                                             
    return m;                                                                   
}

int main(void)
{
	int **grid;
	int gridSize;
	int *gridColSize;
	int i, j;

	scanf("%d", &gridSize);
	grid = calloc(1, sizeof(int *) * gridSize);
	gridColSize = calloc(1, sizeof(int) * gridSize);
	scanf("%d", &gridColSize[0]);
	for (i = 0; i < gridSize; i++) {
		gridColSize[i] = gridColSize[0];
		grid[i] = calloc(1, sizeof(int) * gridColSize[i]);
		for (j = 0; j < gridColSize[i]; j++) {
			scanf("%d", &grid[i][j]);
		}
	}
	printf("%d\n", minCost(grid, gridSize, gridColSize));
	/*free*/
	return 0;
}
