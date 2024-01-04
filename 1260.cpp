#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;
#define MAX_VERTICES 1000
#define _CRT_SECURE_NO_WARNINGS
// 정점 번호는 1번부터 N번까지

void init_graph(int** g, int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			g[i][j] = 0;
}


void insert_edge(int** g, int start, int end, int n) {
	g[start][end] = 1;
	g[end][start] = 1;
}

int bfs_visited[MAX_VERTICES];
void bfs(int** g, int n, int start) {
	queue<int> q;

	q.push(start);
	printf("%d ", start+1);
	bfs_visited[start] = 1;
	while (!q.empty()) {
		int w = q.front();
		for (int u = 0; u < n; u++) {
			if (g[w][u] && !bfs_visited[u]) {
				printf("%d ", u+1);
				q.push(u);
				bfs_visited[u] = 1;
			}
		}
		q.pop();
	}
}

int dfs_visited[MAX_VERTICES];
void dfs(int** g, int n, int start) {
	printf("%d ", start+1);
	dfs_visited[start] = 1;
	for (int u = 0; u < n; u++) {
		if (g[start][u] && !dfs_visited[u])
			dfs(g, n, u);
	}
}

// m = 간선의 개수 n = 정점의 개수 v = 시작 정점
int main(void) {
	int m, n, v;
	int** adj_map;

	// 입력 
	do{
		scanf("%d %d %d", &n, &m, &v);
		getchar();
	}while(n < 0 || m < 0 || n > MAX_VERTICES || m > MAX_VERTICES || v < 0 || v > n );
	// 2차원 배열 할당
	adj_map = (int**)malloc(sizeof(int*) * n);
	for (int j = 0; j < n; j++)
		adj_map[j] = (int*)malloc(sizeof(int) * n);
	
	// 기본세팅
	init_graph(adj_map, n);
	for(int i = 0; i < m; i++) {
		int start, end;
		do{
			scanf("%d %d", &start, &end);
			getchar();
		}while(start < 0 || start > n|| end > n || end < 0);
		start -= 1;
		end -= 1;
		insert_edge(adj_map, start, end, n);
	}

	dfs(adj_map, n, v-1);
	printf("\n");
	bfs(adj_map, n, v-1);
	printf("\n");


	for(int w = 0; w < n; w++)
		free(adj_map[w]);
	free(adj_map);
	return 0;
}
