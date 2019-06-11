#include "Grid.h"



Grid::Grid()
{
	_cellRows = 8;
	_cellCols = 74;

	Wall_Cells = new vector<Wall*>*[_cellRows];
	for (int i = 0; i < _cellRows; i++)
		Wall_Cells[i] = new vector<Wall*>[_cellCols];
}


Grid::~Grid()
{
}

void Grid::GridClear()
{
	for (int i = 0; i < _cellRows; i++)
		if (Wall_Cells[i])
			delete[] Wall_Cells[i];
	if (Wall_Cells)
		delete[] Wall_Cells;
}

void Grid::Add(Wall * wall)
{
	int startRows = wall->wall.bottom / CELL_SIZE + 1;
	int endRows = wall->wall.top / CELL_SIZE + 1;
	int startCol = wall->wall.left / CELL_SIZE + 1;
	int endCols = wall->wall.right / CELL_SIZE + 1;
	for (int i = startRows; i <= endRows; i++)
		for (int j = startCol; j <= endCols; j++)
			Wall_Cells[i][j].push_back(wall);

}

//void Grid::Add(Enemy * enemy)
//{
//}

void Grid::Output()
{
	ofstream gridTxt;
	gridTxt.open((char*)"Resource/Grid/Grid.txt");
	for (int i = 0; i < _cellRows; i++)
	{
		for (int j = 0; j < _cellCols; j++)
		{
			gridTxt << i << " " << j << "\n";
			for (const auto &i : Wall_Cells[i][j])
			{
				RECT tmp = i->wall;
				gridTxt << tmp.left << " " << tmp.top << " " << tmp.right << " " << tmp.bottom << "\n";
			}
			gridTxt << "\n";
		}
		gridTxt << "------------------------------------------------------------------\n";
	}
	gridTxt.close();
}

vector<Wall*> Grid::WallOut(RECT rect)
{
	vector<Wall*> result, tmp;
	int startRows = rect.bottom / CELL_SIZE;
	int endRows = rect.top / CELL_SIZE + 2;
	int startCol = rect.left / CELL_SIZE;
	int endCols = rect.right / CELL_SIZE + 2;

	for (int i = startRows; i <= endRows; i++)
		for (int j = startCol; j <= endCols; j++)
		{
			result.swap(tmp);
			set_union(tmp.begin(), tmp.end(),
				Wall_Cells[i][j].begin(), Wall_Cells[i][j].end(), back_inserter(result));
			tmp.clear();
		}

	return result;
}

