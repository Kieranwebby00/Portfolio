#include "Prims.h"
#include <iostream>
#include <time.h> 

//Key 1-unsearched   2-Searched
void Prims::Initialize(int maze[50][50])
{
	//Picks a random Position and sets it to searched
	srand(time(NULL));
	for (int x = 0;x < m_rows;x++)
	{
		for (int y = 0;y < m_columns;y++)
		{
			maze[x][y] = 1;
		}
	}
	int x = rand() % m_rows;
	int y = rand() % m_columns;
	maze[x][y] = 2;

	AddCells(maze, x, y);
}

void Prims::AddCells(int maze[50][50], int x, int y)
{
	int max = 2;
	//Sets the neighboring cells as possible checks on the maze
	if (maze[x + 1][y] == 1)
	{
		if (x + 1 < m_rows-1)
		{
			if (max > 0) {

			}
			maze[x + 1][y] = 3;
		}
	}
	if (maze[x - 1][y] == 1)
	{
		if (x - 1 >0)
		{
			maze[x - 1][y] = 3;
		}
	}
	if (maze[x][y+1] == 1)
	{
		if (y + 1 < m_columns-1)
		{
			maze[x][y + 1] = 3;
		}
	}
	if (maze[x][y-1] == 1)
	{
		if (y - 1 > 0)
		{
			maze[x][y - 1] = 3;
		}
	}
	//adds walls to maze
	//AddWall(maze, x, y);
	//Adds to the possible cells vector
	Cells.clear();
	for (int x = 0;x < m_rows;x++)
	{
		for (int y = 0;y < m_columns;y++)
		{
			if (maze[x][y] == 3) {
				Cell cell;
				cell.x = x;
				cell.y = y;
				Cells.push_back(cell);
			}
		}
	}
}

void Prims::Step(int maze[50][50])
{
	//chooses a random possbile cell from the vector and updates it on the map
	if (Cells.size() != 0) {
		int NextCell = rand() % Cells.size();
		maze[Cells[NextCell].x][Cells[NextCell].y] = 2;
		AddCells(maze, Cells[NextCell].x, Cells[NextCell].y);
	}
	else
		std::cout << "DONE";
}

void Prims::AddWall(int maze[50][50], int x, int y)
{
	//randomly adds walls
	int wall = rand() % 3;
	switch (wall) {
	case 0:
		if (maze[x + 1][y] == 3)
		{
			if (x + 1 < m_rows - 3)
			{
				maze[x + 1][y] = 4;
			}
		}

		break;
	case 1:
		if (maze[x - 1][y] == 3)
		{
			if (x - 1 > 0)
			{
				maze[x - 1][y] = 4;
			}
		}
		break;

	case 2:
		if (maze[x][y + 1] == 3)
		{
			if (y + 1 < m_columns - 1)
			{
				maze[x][y + 1] = 4;
			}
		}
		break;

	case 3:
		if (maze[x][y - 1] == 3)
		{
			if (y - 1 > 0)
			{
				maze[x][y - 1] = 4;
			}
		}
		break;

	}
}
