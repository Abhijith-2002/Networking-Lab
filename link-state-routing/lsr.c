#include<stdio.h>
#define MAX 100        
#define INFINITY 99999  

int findMinDistance(int dist[], int visited[], int n) {
    int min = INFINITY, minIndex = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(int graph[MAX][MAX], int source, int n) {
    int dist[MAX];       
    int visited[MAX];    
    int path[MAX];      
    

    for (int i = 0; i < n; i++) {
        dist[i] = INFINITY;
        visited[i] = 0;
        path[i] = -1;   
    }
    dist[source] = 0;   

    for (int count = 0; count < n - 1; count++) {
        int u = findMinDistance(dist, visited, n); 
        visited[u] = 1;                            

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INFINITY 
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                path[v] = u;  
            }
        }
    }

    printf("Router\tDistance from Source\tPath\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t", i, dist[i]);
        printPath(path, i); 
        printf("\n");
    }
}

void printPath(int path[], int node) {
    if (path[node] == -1) {
        printf("%d", node);
        return;
    }
    printPath(path, path[node]);
    printf(" -> %d", node);
}

int main() {
    int n; 
    int graph[MAX][MAX];

    printf("Enter the number of routers: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (use 0 for no connection):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int source;
    printf("Enter the source router: ");
    scanf("%d", &source);

    dijkstra(graph, source, n);

    return 0;
}
