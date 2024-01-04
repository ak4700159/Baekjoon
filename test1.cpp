#include <stdlib.h>
#include <stdio.h>
#define MAX_SIZE 100


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

void init_painted(Painted* painted){
	for(int i = 0; i < painted->m; i++)
		for(int j = 0; j < painted->n; j++)
			painted->matrix[i][j] = 0;
}

void print_painted(Painted* painted){
	for(int i = painted->m-1; i >= 0; i--){
		for(int j = 0; j < painted->n; j++)
			printf("%d ", painted->matrix[i][j]);
		printf("\n");
	}
}

int main (void){

	int m, n, k;
	int ldx, ldy, rux, ruy;
	
	// 0 < m n k < 100 
	scanf("%d %d %d", &m, &n, &k);

	Painted* painted = (Painted*)malloc(sizeof(Painted));
	painted->m = m;
	painted->n = n;
	init_painted(painted);

	Ractangle* rect = (Ractangle*)malloc(sizeof(Ractangle) * k);
	for(int i = 0; i < k; i++){
		scanf("%d %d %d %d", &ldx, &ldy, &rux, &ruy);
		rect[i].left_down_x = ldx;
		rect[i].left_down_y = ldy;
		rect[i].right_up_x = rux;
		rect[i].right_up_y = ruy;
	}

	int l = 0;
	while(l < k){
		for(int j = rect[l].left_down_y; j < rect[l].right_up_y; j++)
			for(int i = rect[l].left_down_x; i < rect[l].right_up_x; i++)
				painted->matrix[j][i] = 1;
		l++;
		print_painted(painted);
		printf("\n");
	}

	print_painted(painted);

	return 0;
}
