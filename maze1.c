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
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
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

int predecessor[MAX_ROW * MAX_COL] = {0};

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

bool dfs(struct point p)
{
	bool right, down, left, up;
	right = down = left = up = false;
	
	if(p.row == MAX_ROW - 1 && p.col == MAX_COL - 1)
	{
		num++;
		return true;
	}
	
	maze[p.row][p.col] = 2;
	//print_maze();
	
	if(p.col + 1 < MAX_COL && maze[p.row][p.col + 1] == 0)
	{
		p.col++;
		if(dfs(p))
		{
			right = true;
			printf("(%d, %d)\n", p.row, p.col);
		}
		p.col--;
	}
	if(p.row + 1 < MAX_ROW && maze[p.row + 1][p.col] == 0) /* down */
	{
		p.row++;
		if(dfs(p))
		{
			down = true;
			printf("(%d, %d)\n", p.row, p.col);
		}
		p.row--;
	}
	if(p.col - 1 >= 0 && maze[p.row][p.col - 1] == 0) /* left */
	{
		p.col--;
		if(dfs(p))
		{
			left = true;
			printf("(%d, %d)\n", p.row, p.col);
		}
		p.col++;
	}
	if(p.row - 1 >= 0 && maze[p.row - 1][p.col] == 0) /* up */
	{
		p.row--;
		if(dfs(p))
		{
			up = true;
			printf("(%d, %d)\n", p.row, p.col);
		}
		p.row++;
	}
	maze[p.row][p.col] = 0;
	if(right | down | left | up == true)
		return true;
	else return false;
}

int main()
{
	struct point p = {0,0};
	maze[p.row][p.col] = 2;

	if(dfs(p))
	{
		printf("(0, 0)\n");
		printf("%d\n", num);
	}
	else
		printf("no path\n");
	return 0;
}
