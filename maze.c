#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5
#define bool int
#define true 1
#define false 0

struct point { int row, col; } stack[512];
int top = 0;

void push(struct point p)
{
	stack[top++] = p;
}

struct point pop(void)
{
	return stack[--top];
}

int is_empty(void)
{
	return top == 0;
}

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 0, 0
};

void print_maze(void)
{
	int i, j;
	for(i = 0; i < MAX_ROW; i++)
	{
		for(j = 0; j < MAX_COL; j++)
			printf("%d", maze[i][j]);
		putchar('\n');
	}
	printf("*********\n");
}

int predecessor[MAX_ROW * MAX_COL] = {-1};

/*
struct point predecessor[MAX_ROW][MAX_COL] = {
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}}
};
*/

void visit(int row, int col, struct point pre)
{
	struct point visit_point = { row, col };
	maze[row][col] = 2;
	//predecessor[row][col] = pre;
	predecessor[row * 5 + col] = pre.row * 5 + pre.col;
	push(visit_point);
}

int num = 0;

void dfs(struct point p)
{
	struct point n = p;
		
	if(n.row == MAX_ROW - 1 && n.col == MAX_COL - 1)
	{
		num++;
		printf("(%d, %d)\n", n.row, n.col);
		while(predecessor[n.row * 5 + n.col] != -1)
		{
			int t = n.row * 5 + n.col;
			n.row = predecessor[t] / 5;
			n.col = predecessor[t] % 5;
			printf("(%d, %d)\n", n.row, n.col);
		}
		printf("*********************\n");
	}
 	else
	{
		maze[n.row][n.col] = 2;
		//print_maze();
	
		if(n.col + 1 < MAX_COL && maze[n.row][n.col + 1] == 0)
		{
			n.col++;
			predecessor[n.row * 5 + n.col] = p.row * 5 + p.col;
			dfs(n);
			n.col--;
		}
		if(n.row + 1 < MAX_ROW && maze[n.row + 1][n.col] == 0) /* down */
		{
			n.row++;
			predecessor[n.row * 5 + n.col] = p.row * 5 + p.col;
			dfs(n);
			n.row--;
		}
		if(n.col - 1 >= 0 && maze[n.row][n.col - 1] == 0) /* left */
		{
			n.col--;
			predecessor[n.row * 5 + n.col] = p.row * 5 + p.col;
			dfs(n);
			n.col++;
		}
		if(n.row - 1 >= 0 && maze[n.row - 1][n.col] == 0) /* up */
		{
			n.row--;
			predecessor[n.row * 5 + n.col] = p.row * 5 + p.col;
			dfs(n);
			n.row++;
		}
		maze[n.row][n.col] = 0;
	}
}

int main()
{
	struct point p = {0,0};
	maze[p.row][p.col] = 2;
	
	dfs(p);

	if(predecessor[24] != 0)
	{
		//printf("(0, 0)\n");
		printf("%d\n", num);
	}
	else
		printf("no path\n");

	return 0;
}
