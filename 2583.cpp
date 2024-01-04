#include <stdlib.h>
#include <stdio.h>
#include <queue>
#define MAX_SIZE 100

using namespace std;

typedef struct Painted{
	int matrix[MAX_SIZE][MAX_SIZE];
	int m, n; //matrix[m][n] n = row number, m = cloumn number
}Painted;

typedef struct Ractangle{
	int left_down_x;
	int left_down_y;
	int right_up_x;
	int right_up_y;
}Ractangle;

typedef struct HeapGraph{
	int n;
	int heap[MAX_SIZE];
}HeapGraph;

void print_heap(HeapGraph* g){
	for(int i = 0; i < g->n; i++)
		printf("%d ", g->heap[i]);
	printf("\n");
}

void insert_heap(HeapGraph* g, int data){
	if(g->n+1 >= MAX_SIZE){
		fprintf(stderr, "MAX SIZE OVER");
		exit(1);
	}
	if(g->n == 0)
		g->heap[0] = data;


	for(int i = 0; i < g->n; i++){

		if(data >= g->heap[i] && i == g->n-1){
			g->heap[i+1] = data;
			break;
		}
		
		if(data < g->heap[i]){
			for(int j = g->n; j > i; j--)
				g->heap[j] = g->heap[j-1];
			g->heap[i] = data;
			break;
		}
	}
	g->n++;
}


void init_painted(Painted* painted){
	for(int i = 0; i < painted->m; i++)
		for(int j = 0; j < painted->n; j++) painted->matrix[i][j] = 0;
}

void print_painted(Painted* painted){
	for(int i = painted->m-1; i >= 0; i--){
		for(int j = 0; j < painted->n; j++)
			printf("%d ", painted->matrix[i][j]);
		printf("\n");
	}
}

void paint(Painted* painted, Ractangle* rect, int k){
	int l = 0;
	int check_sum = 0;
	while(l < k){
		for(int j = rect[l].left_down_y; j < rect[l].right_up_y; j++)
			for(int i = rect[l].left_down_x; i < rect[l].right_up_x; i++){
				painted->matrix[j][i] = 1;
				check_sum += 1;
			}
		l++;
	}
	if(check_sum == painted->n*painted->m){
		fprintf(stderr, "Except\n");
		exit(1);
	}
}

typedef struct Point{
	Point(int x = 0, int y = 0): x(x), y(y) { }
	int x;
	int y;
}Point;
void bfs(Painted* painted, HeapGraph* root){
	int count = 0;
	int area = 0;
	Point temp;
	queue<Point> q;
	for(int i = 0; i < painted->m; i++)
		for(int j = 0; j < painted->n; j++)
			if(!painted->matrix[i][j]){			
				count++;
				q.push(Point(j, i));
				painted->matrix[i][j] = 1;
				area++;
				temp = q.front();
				while(!q.empty()){
					q.pop();
					if(temp.x+1 < painted->n)
						if(!painted->matrix[temp.y][temp.x+1]){
							q.push(Point(temp.x+1, temp.y));
							painted->matrix[temp.y][temp.x+1] = 1;
							area++;
						}

					if(temp.y+1 < painted->m)
						if(!painted->matrix[temp.y+1][temp.x]){
							q.push(Point(temp.x, temp.y+1));
							painted->matrix[temp.y+1][temp.x] = 1;
							area++;
						}

					if(temp.x-1 > 0)
						if(!painted->matrix[temp.y][temp.x-1]){
							q.push(Point(temp.x-1, temp.y));
							painted->matrix[temp.y][temp.x-1] = 1;
							area++;
						}

					if(temp.y-1 > 0)
						if(!painted->matrix[temp.y-1][temp.x]){
							q.push(Point(temp.x, temp.y-1));
							painted->matrix[temp.y-1][temp.x] = 1;
							area++;
						}
					temp = q.front();
				}
				insert_heap(root, area);
				area = 0;
			}
	printf("%d\n", count);
}

int main(void){
	HeapGraph* root = (HeapGraph*)malloc(sizeof(HeapGraph));
	root->n = 0;
	int m = 0, n = 0, k = 0;
	int ldx = 0, ldy = 0, rux = 0, ruy = 0;
	
	// 0 < m n k < 100 
	scanf("%d %d %d", &m, &n, &k);
	if( m <= 0 || n <= 0 || k <= 0 || m > 100 || n > 100 || k > 100){
		fprintf(stderr,"IDX OVER");
		exit(1);
	}

	Painted* painted = (Painted*)malloc(sizeof(Painted));
	painted->m = m;
	painted->n = n;
	init_painted(painted);

	Ractangle* rectangle = (Ractangle*)malloc(sizeof(Ractangle) * k);
	for(int i = 0; i < k; i++){
		scanf("%d %d %d %d", &ldx, &ldy, &rux, &ruy);
		rectangle[i].left_down_x = ldx;
		rectangle[i].left_down_y = ldy;
		rectangle[i].right_up_x = rux;
		rectangle[i].right_up_y = ruy;
	}

	paint(painted, rectangle, k);
	bfs(painted, root);
	print_heap(root);
	
	free(root);
	free(rectangle);
	free(painted);
	return 0;
}
