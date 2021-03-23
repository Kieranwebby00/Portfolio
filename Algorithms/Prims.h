#pragma once
#include <vector>

struct Cell {
	int x;
	int y;
};

class Prims
{
private:
	std::vector<Cell> Cells;
	int m_rows = 50;
	int m_columns = 50;
	int x;
	int y;
public:
	void Initialize(int maze[50][50]);
	void AddCells(int maze[50][50], int x, int y);
	void Step(int maze[50][50]);
	void AddWall(int maze[50][50], int x, int y);
};

