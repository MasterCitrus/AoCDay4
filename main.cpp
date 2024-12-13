#include <string>
#include <fstream>
#include <vector>
#include <iostream>

std::vector<std::string> GetInput();
int CheckNeighbours(int x, int y, std::vector<std::string> data);
bool CheckBounds(int x, int y, int xLimit, int yLimit);
bool CheckCross(int x, int y, std::vector<std::string> data);

int main()
{
	std::vector<std::string> data = GetInput();

	std::size_t pos = 0;
	int xmasCount = 0;
	int crossCount = 0;
	for (std::size_t i = 0; i < data.size(); i++)
	{
		for (std::size_t j = 0; j < data[i].size(); j++)
		{
			if (data[i][j] == 'X')
			{
				xmasCount += CheckNeighbours(j, i, data);
			}
			if (data[i][j] == 'A')
			{
				if (CheckCross(j, i, data)) crossCount++;
			}
		}
	}

	std::cout << "Total XMAS in word search: " << xmasCount <<'\n';
	std::cout << "Total X-MAS in word search: " << crossCount << '\n';
}

std::vector<std::string> GetInput()
{
	std::fstream io("input.txt");
	std::vector<std::string> input;

	for (std::string line; std::getline(io, line);)
	{
		input.push_back(line);
	}

	return input;
}

int CheckNeighbours(int x, int y, std::vector<std::string> data)
{
	int xmas = 0;
	int neighbourOffset[9][2] = {
		{-1, -1}, {0, -1}, {1, -1},
		{-1,  0}, {0,  0}, {1,  0},
		{-1,  1}, {0,  1}, {1,  1},
	};

	for (std::size_t i = 0; i < 9; i++)
	{
		int x2 = x + neighbourOffset[i][0];
		int y2 = y + neighbourOffset[i][1];
		if (CheckBounds(x2, y2, data[i].size(), data.size()))
		{
			if (data[y2][x2] == 'M')
			{
				x2 = x2 + neighbourOffset[i][0];
				y2 = y2 + neighbourOffset[i][1];
				if (CheckBounds(x2, y2, data[i].size(), data.size()))
				{
					if (data[y2][x2] == 'A')
					{
						x2 = x2 + neighbourOffset[i][0];
						y2 = y2 + neighbourOffset[i][1];
						if (CheckBounds(x2, y2, data[i].size(), data.size()))
						{
							if (data[y2][x2] == 'S')
							{
								xmas++;
							}
						}
						
					}
				}
				
			}
		}
		
	}

	return xmas;
}

bool CheckBounds(int x, int y, int xLimit, int yLimit)
{
	if (x < 0 || x >= xLimit || y < 0 || y >= yLimit) return false;
	else return true;
}

bool CheckCross(int x, int y, std::vector<std::string> data)
{
	int offsets[2][2] = {
		{-1, -1}, {1, -1}
	};

	int diagonal = 0;

	for (std::size_t i = 0; i < 2; i++)
	{
		int x2 = x + offsets[i][0];
		int y2 = y + offsets[i][1];
		if (CheckBounds(x2, y2, data[0].size(), data.size()))
		{
			if (data[y2][x2] == 'M')
			{
				if (i == 0)
				{
					x2 = x + 1;
					y2 = y + 1;
				}
				else
				{
					x2 = x + -1;
					y2 = y + 1;
				}
				if (CheckBounds(x2, y2, data[0].size(), data.size()))
				{
					if (data[y2][x2] == 'S')
					{
						diagonal++;
					}
				}
			}
			else if (data[y2][x2] == 'S')
			{
				if (i == 0)
				{
					x2 = x + 1;
					y2 = y + 1;
				}
				else
				{
					x2 = x + -1;
					y2 = y + 1;
				}
				if (CheckBounds(x2, y2, data[0].size(), data.size()))
				{
					if (data[y2][x2] == 'M')
					{
						diagonal++;
					}
				}
			}
			else return false;
		}
	}

	if (diagonal == 2) return true;
	else return false;
}
