#include <math.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 9
#define HEIGHT 9
#define BOX_W 3
#define BOX_H 3
#define MAX_VAL 9

struct Vec2
{
	int x;
	int y;
};

struct Vec2 getNextEmpty(int** board)
{
	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			if (board[j][i] == 0)
			{
				struct Vec2 pos = { i, j };
				return pos;
			}
		}
	}
	struct Vec2 pos = { -1, -1 };
	return pos;
}

int isValid(int** board, int x, int y, int val)
{
	for (int i = 0; i < WIDTH; i++)
	{
		if (board[y][i] == val)
		{
			return 0;
		}
	}
	for (int j = 0; j < HEIGHT; j++)
	{
		if (board[j][x] == val)
		{
			return 0;
		}
	}

	int box_x = (x / 3) * 3; // top of box
	int box_y = (y / 3) * 3; // left of box

	for (int j = box_y; j < box_y + 3; j++)
	{
		for (int i = box_x; i < box_x + 3; i++)
		{
			if (board[j][i] == val)
			{
				return 0;
			}
		}
	}

	return 1;
}

int solve(int** board)
{
	struct Vec2 emptyPos = getNextEmpty(board);

	if (emptyPos.x == -1 && emptyPos.y == -1)
	{
		return 1;
	}

	for (int possVal = 1; possVal <= MAX_VAL; possVal++)
	{
		if (isValid(board, emptyPos.x, emptyPos.y, possVal))
		{
			board[emptyPos.y][emptyPos.x] = possVal;
			
			if (solve(board))
			{
				return 1;
			}

			board[emptyPos.y][emptyPos.x] = 0;
		}
	}

	return 0;
}

int** createTestBoard()
{
	int** board = (int*) calloc(HEIGHT, sizeof(int*));

	for (int j = 0; j < HEIGHT; j++)
	{
		board[j] = (int*) calloc(WIDTH, sizeof(int));
	}

	board[4][0] = 7;
	board[8][4] = 8;
	board[1][1] = 9;
	board[3][1] = 5;
	board[6][1] = 2;
	board[8][1] = 6;
	board[3][2] = 1;
	board[7][2] = 7;
	board[4][3] = 2;
	board[6][3] = 7;
	board[7][3] = 9;
	board[1][4] = 6;
	board[2][4] = 2;
	board[4][4] = 9;
	board[6][4] = 5;
	board[7][4] = 3;
	board[1][5] = 7;
	board[2][5] = 9;
	board[4][5] = 1;
	board[1][6] = 4;
	board[5][6] = 1;
	board[0][7] = 3;
	board[2][7] = 7;
	board[5][7] = 8;
	board[7][7] = 2;
	board[0][8] = 2;
	board[4][8] = 6;

	return board;
}

int main()
{
	int** board = createTestBoard();

	clock_t start, end;
	double cpu_time_used;

	start = clock();

	solve(board);

	end = clock();

	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	printf("algorithm finished in %f cpu seconds", cpu_time_used);

	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			printf("%d ", board[j][i]);
		}
		printf("/n");
	}

}