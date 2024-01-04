#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;
// 정점 번호는 1번부터 N번까지
// 모든 정점 번호에 대해 

void init_graph(int** g, int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			g[i][j] = 0;
}

int bfs_visited[10000];
void bfs(int** g, int n, int start) {
	queue<int> q;

	q.push(start-1);
	printf("%d ", start);
	bfs_visited[start-1] = 1;
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

int dfs_visited[10000];
void dfs(int** g, int n, int start) {
	printf("%d ", start+1);
	dfs_visited[start] = 1;
	for (int u = 0; u < n; u++) {
		if (g[start][u] && !dfs_visited[u])
			dfs(g, n, u);
	}
}

// n = 정점의 개수 | m = 간선의 개수 | v = 시작 정점
int main(void) {
	int n, m, v;
	int** adj_map;

	// 입력 
	scanf("%d %d %d", &n, &m, &v);
	getchar();
	if (n < 1 || n > 10000 || m < 1 || m > 10000 || v < 1 || v > n)
		return 0;
	// 2차원 배열 할당
	adj_map = (int**)malloc(sizeof(int*) * n);
	for (int j = 0; j < n; j++)
		adj_map[j] = (int*)malloc(sizeof(int) * n);
	// 기본세팅 간선 정보 추가 및 그래프 초기화
	init_graph(adj_map, n);
	int accepted_edge = 0;
	while (accepted_edge != m) {
		int start = 0, end = 0;
		scanf("%d %d", &start, &end);
		getchar();
		if (start > n || start < 1 || end > n || end < 1) {
			continue;
		}
		adj_map[start - 1][end - 1] = 1;
		adj_map[end - 1][start - 1] = 1;
		accepted_edge++;
	}

	dfs(adj_map, n, v-1);
	printf("\n");
	bfs(adj_map, n, v);
	printf("\n");

	for (int w = 0; w < n; w++)
		free(adj_map[w]);
	free(adj_map);
	return 0;
}
