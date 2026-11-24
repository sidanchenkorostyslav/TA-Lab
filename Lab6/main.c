#include <stdio.h>
#include <limits.h>

#define N 8
#define INF 1000000000

static const int graph[N][N] = {
    {0, 8, 2, 4, 3, 0, 0, 0},
    {8, 0, 0, 0, 6, 3, 0, 0},
    {2, 0, 0, 6, 0, 7, 0, 4},
    {4, 0, 6, 0, 1, 0, 0, 0},
    {3, 6, 0, 1, 0, 0, 4, 0},
    {0, 3, 7, 0, 0, 0, 3, 1},
    {0, 0, 0, 0, 4, 3, 0, 5},
    {0, 0, 4, 0, 0, 1, 5, 0}
};

void print_path(int pred[], int v) {
    if (pred[v] == -1) {
        printf("%d", v + 1);
        return;
    }
    print_path(pred, pred[v]);
    printf(" -> %d", v + 1);
}

void dijkstra(int source) {
    int dist[N], pred[N], used[N] = {0};
    for (int i = 0; i < N; ++i) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[source] = 0;

    for (int step = 0; step < N; ++step) {
        int u = -1;
        for (int i = 0; i < N; ++i)
            if (!used[i] && (u == -1 || dist[i] < dist[u])) u = i;
        if (u == -1 || dist[u] == INF) break;
        used[u] = 1;
        for (int v = 0; v < N; ++v) {
            if (graph[u][v] > 0 && !used[v] &&
                dist[v] > dist[u] + graph[u][v]) {
                dist[v] = dist[u] + graph[u][v];
                pred[v] = u;
            }
        }
    }

    printf("Dijkstra, source = %d\n", source + 1);
    for (int v = 0; v < N; ++v) {
        printf("to %d: distance = %d, path = ", v + 1, dist[v]);
        print_path(pred, v);
        putchar('\n');
    }
}

void floyd(void) {
    int d[N][N];
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            d[i][j] = (i == j) ? 0 : (graph[i][j] ? graph[i][j] : INF);

    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (d[i][k] < INF && d[k][j] < INF &&
                    d[i][j] > d[i][k] + d[k][j])
                    d[i][j] = d[i][k] + d[k][j];

    printf("\nFloyd distance matrix:\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            printf("%4d", d[i][j]);
        putchar('\n');
    }
}

int main(void) {
    dijkstra(0); /* starting vertex 1 */
    floyd();
    return 0;
}
