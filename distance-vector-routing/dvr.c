#include <stdio.h>
#include <limits.h>

#define INF 9999  
#define MAX 10    

typedef struct {
    int distance[MAX];  
    int nextHop[MAX];   
} RoutingTable;

int main() {
    int n; 
    int costMatrix[MAX][MAX];
    RoutingTable table[MAX];

    printf("Enter the number of routers: ");
    scanf("%d", &n);

    printf("Enter the cost matrix (enter %d for no direct connection):\n", INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &costMatrix[i][j]);
            if (i == j) {
                costMatrix[i][j] = 0; 
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            table[i].distance[j] = costMatrix[i][j];
            if (costMatrix[i][j] != INF && i != j) {
                table[i].nextHop[j] = j;
            } else {
                table[i].nextHop[j] = -1;
            }
        }
    }

    int updated;
    do {
        updated = 0; 
        for (int i = 0; i < n; i++) { 
            for (int j = 0; j < n; j++) { 
                for (int k = 0; k < n; k++) {
                    if (table[i].distance[k] + table[k].distance[j] < table[i].distance[j]) {
                        table[i].distance[j] = table[i].distance[k] + table[k].distance[j];
                        table[i].nextHop[j] = k;
                        updated = 1;
                    }
                }
            }
        }
    } while (updated);

    for (int i = 0; i < n; i++) {
        printf("\nRouting table for Router %d:\n", i + 1);
        printf("Destination\tCost\tNext Hop\n");
        for (int j = 0; j < n; j++) {
            printf("%d\t\t", j + 1);
            if (table[i].distance[j] == INF) {
                printf("INF\t-");
            } else {
                printf("%d\t%d", table[i].distance[j], table[i].nextHop[j] + 1);
            }
            printf("\n");
        }
    }

    return 0;
}
