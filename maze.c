#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

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
	0, 0, 0, 1, 0
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

/* predecessor 1 */
int predecessor[MAX_ROW * MAX_COL] = {0};

/* predecessor 2 */
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

int main(void)
{
	struct point p = { 0, 0 };

	maze[p.row][p.col] = 2;
	push(p);

	while(!is_empty())
	{
		p = pop();
		if(p.row == MAX_ROW - 1 && p.col == MAX_COL - 1) /* goal */
			break;
		if(p.col + 1 < MAX_COL && maze[p.row][p.col + 1] == 0) /* right */
			visit(p.row, p.col+1, p);
		if(p.row + 1 < MAX_ROW && maze[p.row + 1][p.col] == 0) /* down */
			visit(p.row+1, p.col, p);
		if(p.col - 1 >= 0 && maze[p.row][p.col - 1] == 0) /* left */
			visit(p.row, p.col-1, p);
		if(p.row - 1 >= 0 && maze[p.row - 1][p.col] == 0) /* up */
			visit(p.row-1, p.col, p);
		print_maze();
	}
	
	/*****************************stack*******************************/
/*	if(p.row == MAX_ROW - 1 && p.col == MAX_COL - 1)
	{
		printf("(%d, %d)\n", p.row, p.col);
		while(predecessor[p.row][p.col].row != -1)
		{
			p = predecessor[p.row][p.col];
			printf("(%d, %d)\n", p.row, p.col);
		}
	}*/
	if(p.row == MAX_ROW - 1 && p.col == MAX_COL - 1)
	{
		printf("(%d, %d)\n", p.row, p.col);
		while(predecessor[p.row * 5 + p.col] != 0)
		{
			int t = p.row * 5 + p.col;
			p.row = predecessor[t] / 5;
			p.col = predecessor[t] % 5;
			printf("(%d, %d)\n", p.row, p.col);
		}
	}
	else
		printf("No path!\n");
	/*****************************stack*******************************/

	return 0;
}
