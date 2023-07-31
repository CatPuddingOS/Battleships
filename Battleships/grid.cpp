#include <SDL.h>
#include "unity_build.h"

inline int Grid::GetGridSize()
{
	return cellCount;
}

void Grid::Initialize(int row, int col, int screenWidth, int screenHeight) {
	//Lazy because 'default contructor'
	size[0] = row;
	size[1] = col;
	WIDTH = screenWidth;
	HEIGHT = screenHeight;
	cellCount = row * col;
	cellArr.resize(cellCount);
}

void Grid::CreateGrid()
{
	float newCellWidth = WIDTH / size[0]; //Distance between X lines (Vertical)
	float newCellHeight = HEIGHT / size[1]; //Distance between Y lines (Horizontal)
	int lastPointX = 0;
	int lastPointY = 0;

	//Populate cells[] with properly sized and positioned cells
	for (int i = 0; i < cellCount; i++)
	{
		cellArr[i] = (std::make_unique<Cell>());
		cellArr[i]->Initialize(i, lastPointX, lastPointY, newCellWidth, newCellHeight);
		lastPointX += newCellWidth;
		if (lastPointX >= WIDTH)
		{
			lastPointX = 0;
			lastPointY += newCellHeight;
		}
	}
}

/*To use: pass the size of the ship and assign the return value of the method to the location vector of the ship used in the param pass*/
std::vector<int> Grid::AssignLocation(int range)
{
	/*Add checks for other ships in path. ex. if(this ship + direction == cell occupied) {move away}*/

	std::vector<int> locations;
	int orientation;
	int size = range;
	bool greenlight;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, cellCount - 1);

	std::uniform_int_distribution<> dist(1, 2);
	dist(gen) == 1 ? orientation = Horizontal : orientation = Vertical;
	locations.push_back(dis(gen));

	while (cellArr[locations[0]]->occupied == true)
	{ 
		std::cout << "Finding initial location\n";
		locations[0] = (dis(gen));
	}
	cellArr[locations[0]]->occupied = true;

	std::cout << "Starting position " << locations[0] << " checks out\n\n";
	int modifier;
	do {
		modifier = orientation;
		std::cout << "Starting loop at " << locations[0] <<"\n\n";
		greenlight = true;
		
		if (cellArr[locations[0]]->occupied) { greenlight = false; }

		for (int i = 0; i < range+2; i++)
		{
			if (locations[0] - modifier < cellArr.size())
			{
				if (cellArr[locations[0] - modifier]->occupied) { greenlight = false; };
			}
			if (locations[0] + modifier < cellArr.size())
			{
				if (cellArr[locations[0] + modifier]->occupied) { greenlight = false; };
			}
			modifier += orientation;
		}

		if (!greenlight)
		{
			locations[0] = dis(gen);
		}
	} while (!greenlight);

	std::cout << "Ending loop at" << locations[0] << "\n\n";

	if (range < 2) { return locations; };

	std::cout << "Starting push at: " << locations[0] << std::endl;
	for (int i = 0; i < size - 1; i++)
	{
		cellArr[locations[i]]->occupied = true;
		/*Check all the cells around the ship based on size and orientation
		If a cell is marked as occupied, pick a new location*/


		//Prevent Out of Scope exceptions and row hopping
		//If start location is Out of Scope --or-- next location is near the end of the row 
		if (locations[0] >= cellCount - size || locations[0] % 10 >= size + 1 && orientation == Horizontal)
		{
			std::cout << "Condition Out of range / Row Hop\n";
			if (locations[i] - orientation < 0)
			{
				locations = ShiftForward(locations, orientation);
				locations.push_back(locations[i] - orientation);
			}
			else
			{
				locations.push_back(locations[i] - orientation);
			}
			std::cout << "Condition 1	END\n";
			cellArr[locations[i]]->occupied = true;
			continue;
		}
		else if (locations[i] + orientation >= cellCount)
		{
			std::cout << "Condition Back\n";
			locations = ShiftBackward(locations, orientation);
			locations.push_back(locations[i] + orientation);
			std::cout << "Back Restricting to: " << locations[i] + orientation << std::endl;
			continue;
		}
		else if (locations[i] + orientation % 10 == 0)
		{
			std::cout << "Condition Forward\n";
			locations = ShiftForward(locations, orientation);
			locations.push_back(locations[i] - orientation);
			std::cout << "Forward Restricting to: " << locations[i] - orientation << std::endl;
			continue;
		}

		std::cout << "Default pushing to: " << locations[i] + orientation << std::endl;
		locations.push_back(locations[i] + orientation);
		std::cout << "END ITERATION\n";
		cellArr[locations[i]]->occupied = true;
	}
	std::cout << "END LOOP\n\n";
	cellArr[locations.back()]->occupied = true;
	return locations;
}

std::vector<int> Grid::ShiftForward(std::vector<int> vec, int orientation)
{
	//Shift the positions in locations vec forward. Relative to ships orientation
	cellArr[vec[0]]->occupied = false;

	for (int r = 0; r < vec.size(); r++)
	{
		std::cout << "Rewriting: " << vec[r] << " to ";
		vec[r] += orientation;
		cellArr[vec[r]]->occupied = true;
		std::cout << vec[r] << "\n\n";
	}
	return vec;
}

std::vector<int> Grid::ShiftBackward(std::vector<int> vec, int orientation)
{
	//Shift the positions in locations vec backwards. Relative to ships orientation
	cellArr[vec.back()]->occupied = false;

	for (int r = 0; r < vec.size(); r++)
	{
		std::cout << "Rewriting: " << vec[r] << " to ";
		vec[r] -= orientation;
		cellArr[vec[r]]->occupied = true;
		std::cout << vec[r] << "\n\n";
	}
	return vec;
}

template<typename T> void Grid::CheckGrid(T &fleet)
{
	//Reset occupied for all cells (band-aid fix)
	for (int c = 0; c < cellCount; c++)
	{
		cellArr[c]->occupied = false;
	}

	//Set cells that match the ships location are flagged occupied
	std::vector<int> vec;
	for (int s = 0; s < fleet->GetSize(); s++)
	{
		vec = fleet->fleetArr[s].GetLocation();
		for (int i = 0; i < vec.size(); i++)
		{
			cellArr[vec[i]]->occupied = true;
			cellArr[vec[i]]->occupant = fleet->fleetArr[s].GetName();
		}
	}
}

void Grid::ResetGrid()
{
	for (int i = 0; i < cellCount; i++)
	{
		cellArr[i]->ResetCell();
	}
}

void Grid::Listen(int mouseX, int mouseY)
{
	//Listen for changes in each cell of the grid
	for (int i = 0; i < cellCount; i++)
	{
		cellArr[i]->Listen(mouseX, mouseY);
	}
}

void Grid::Draw(SDL_Renderer * renderer, int Xstart, int Ystart, int Xend, int Yend) 
{
	for (int c = 0; c < cellCount; c++)
	{
		cellArr[c]->Render(renderer);
	}
}
