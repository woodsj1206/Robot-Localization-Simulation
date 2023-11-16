#include "Robot.h"

//Default Constructor
Robot::Robot() 
{
	//Iniitialize all of the values in the array.
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			maze[i][j].probability = 0;
			maze[i][j].isSpace = false;
		}
	}
}

//Constructor
Robot::Robot(int arr[ROWS][COLUMNS]) 
{
	this->SetMaze(arr);
}

//Robot moves northward or eastward in the windy situation.
void Robot::Moving(char direction) 
{
	node tempMaze[ROWS][COLUMNS];
	memcpy(tempMaze, maze, sizeof(maze));

	double total = 0;

	//Prediction.
	if (direction == 'N')
	{	
		//Moving North
		for (int i = 0; i < ROWS; i++) 
		{
			for (int j = 0; j < COLUMNS; j++) 
			{
				if (maze[i][j].isSpace)
				{					
					maze[i][j].probability = 0;

					//Check West Position
					if (j - 1 >= 0) {
						if (maze[i][j - 1].isSpace)
						{
							//Drifting
							maze[i][j].probability += tempMaze[i][j - 1].probability * 0.1;
						}
						else
						{
							//Bouncing back to original position.
							maze[i][j].probability += tempMaze[i][j].probability * 0.1;
						}
					}
					else
					{
						//Bouncing back to original position.
						maze[i][j].probability += tempMaze[i][j].probability * 0.1;
					}

					//Check North Position
					if (i - 1 >= 0) {
						if (!maze[i - 1][j].isSpace)
						{
							maze[i][j].probability += tempMaze[i][j].probability * 0.8;
						}
					}
					else
					{
						maze[i][j].probability += tempMaze[i][j].probability * 0.8;
					}

					//Check East Position
					if (j + 1 < COLUMNS) {
						if (maze[i][j + 1].isSpace)
						{
							//Drifting
							maze[i][j].probability += tempMaze[i][j + 1].probability * 0.1;
						}
						else
						{
							//Bouncing back to original position.
							maze[i][j].probability += tempMaze[i][j].probability * 0.1;
						}
					}
					else
					{
						//Bouncing back to original position.
						maze[i][j].probability += tempMaze[i][j].probability * 0.1;
					}

					//Check South Position
					if (i + 1 < ROWS) {
						if (maze[i + 1][j].isSpace)
						{
							//Reaching the square to the north.
							maze[i][j].probability += tempMaze[i + 1][j].probability * 0.8;
						}
					}
					
					total += maze[i][j].probability;
				}
			}
		}
	}
	else if (direction == 'E')
	{	
		//Moving East
		for (int i = 0; i < ROWS; i++) 
		{
			for (int j = 0; j < COLUMNS; j++) 
			{
				if (maze[i][j].isSpace)
				{					
					maze[i][j].probability = 0;

					//Check West Position
					if (j - 1 >= 0) {
						if (maze[i][j - 1].isSpace)
						{
							//Reaching the square to the east.
							maze[i][j].probability += tempMaze[i][j - 1].probability * 0.8;
						}
					}

					//Check North Position
					if (i - 1 >= 0) {
						if (maze[i - 1][j].isSpace)
						{
							//Drifting
							maze[i][j].probability += tempMaze[i - 1][j].probability * 0.1;
						}
						else
						{
							//Bouncing back to original position.
							maze[i][j].probability += tempMaze[i][j].probability * 0.1;
						}
					}
					else
					{
						//Bouncing back to original position.
						maze[i][j].probability += tempMaze[i][j].probability * 0.1;
					}

					//Check East Position
					if (j + 1 < COLUMNS) {
						if (!maze[i][j + 1].isSpace)
						{
							maze[i][j].probability += tempMaze[i][j].probability * 0.8;
						}
					}
					else
					{
						maze[i][j].probability += tempMaze[i][j].probability * 0.8;
					}

					//Check South Position
					if (i + 1 < ROWS) {
						if (maze[i + 1][j].isSpace)
						{
							//Drifting
							maze[i][j].probability += tempMaze[i + 1][j].probability * 0.1;
						}
						else
						{
							//Bouncing back to original position.
							maze[i][j].probability += tempMaze[i][j].probability * 0.1;
						}
					}
					else
					{
						//Bouncing back to original position.
						maze[i][j].probability += tempMaze[i][j].probability * 0.1;
					}

					total += maze[i][j].probability;
				}
			}
		}
	}
	else 
	{
		return;
	}

	Multiplier(total);
}

//Multiplies each location probability by a multiplier.
void Robot::Multiplier(double total)
{
	double multiplier = 1;

	if (total != 0)
	{
		multiplier = 100 / total;
	}

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (maze[i][j].isSpace)
			{				
				maze[i][j].probability *= multiplier;
			}
		}
	}

}

//Prints the maze containing the location probabilities and obstacles.
void Robot::PrintMaze() 
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (maze[i][j].isSpace)
			{
				std::cout << std::fixed << std::setprecision(2) << maze[i][j].probability << "\t";
			}
			else 
			{
				std::cout << "####" << "\t";
			}
		}
		std::cout << std::endl << std::endl;
	}

	std::cout << std::endl;
}

//Rounds a number up to 2 decimal places.
void Robot::Round(double& number) 
{
	number = (int)(number * 100 + 0.5);
	number /= (float)100;
}

//Senses the four direction (West, North, East, South) to see if there is an obstacle.
void Robot::Sensing(int arr[])
{
	double total = 0;

	//Filtering.
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (maze[i][j].isSpace)
			{
				//Checks West Position
				if (j - 1 >= 0) {
					if (maze[i][j - 1].isSpace)
					{
						if (arr[0] == 0)
						{
							//The West Position is a space.
							maze[i][j].probability *= 0.9;
						}
						else
						{
							//Mistakes an open square as an obstacle.
							maze[i][j].probability *= 0.1;
						}
					}
					else
					{
						if (arr[0] == 1)
						{
							//Detects obstacle.
							maze[i][j].probability *= 0.85;
						}
						else
						{
							//Did not detect the obstacle.
							maze[i][j].probability *= 0.15;
						}
					}
				}
				else 
				{
					if (arr[0] == 1)
					{
						//Detects obstacle.
						maze[i][j].probability *= 0.85;
					}
					else
					{
						//Did not detect the obstacle.
						maze[i][j].probability *= 0.15;
					}
				}

				//Checks North Position
				if (i - 1 >= 0) {
					if (maze[i - 1][j].isSpace)
					{
						if (arr[1] == 0)
						{
							//The North Position is a space.
							maze[i][j].probability *= 0.9;
						}
						else
						{
							//Mistakes an open square as an obstacle.
							maze[i][j].probability *= 0.1;
						}
					}
					else
					{
						if (arr[1] == 1)
						{
							//Detects obstacle.
							maze[i][j].probability *= 0.85;
						}
						else
						{
							//Did not detect the obstacle.
							maze[i][j].probability *= 0.15;
						}
					}
				}
				else
				{
					if (arr[1] == 1)
					{
						//Detects obstacle.
						maze[i][j].probability *= 0.85;
					}
					else
					{
						//Did not detect the obstacle.
						maze[i][j].probability *= 0.15;
					}
				}

				//Checks East Position
				if (j + 1 < COLUMNS) {
					if (maze[i][j + 1].isSpace)
					{
						if (arr[2] == 0)
						{
							//The East Position is a space.
							maze[i][j].probability *= 0.9;
						}
						else
						{
							//Mistakes an open square as an obstacle.
							maze[i][j].probability *= 0.1;
						}
					}
					else
					{
						if (arr[2] == 1)
						{
							//Detects obstacle.
							maze[i][j].probability *= 0.85;
						}
						else
						{
							//Did not detect the obstacle.
							maze[i][j].probability *= 0.15;
						}
					}
				}
				else
				{
					if (arr[2] == 1)
					{
						//Detects obstacle.
						maze[i][j].probability *= 0.85;
					}
					else
					{
						//Did not detect the obstacle.
						maze[i][j].probability *= 0.15;
					}
				}

				//Checks South Position
				if (i + 1 < ROWS) {
					if (maze[i + 1][j].isSpace)
					{
						if (arr[3] == 0)
						{
							//The South Position is a space.
							maze[i][j].probability *= 0.9;
						}
						else
						{
							//Mistakes an open square as an obstacle.
							maze[i][j].probability *= 0.1;
						}
					}
					else
					{
						if (arr[3] == 1)
						{
							//Detects obstacle.
							maze[i][j].probability *= 0.85;
						}
						else
						{
							//Did not detect the obstacle.
							maze[i][j].probability *= 0.15;
						}
					}
				}
				else
				{
					if (arr[3] == 1)
					{
						//Detects obstacle.
						maze[i][j].probability *= 0.85;
					}
					else
					{
						//Did not detect the obstacle.
						maze[i][j].probability *= 0.15;
					}
				}
				
				total += maze[i][j].probability;
			}
		}
	}

	Multiplier(total);
}

//Sets the initial probability of all spaces and obstacles in the maze.
void Robot::SetMaze(int arr[ROWS][COLUMNS]) 
{
	int totalObstacles = 0;

	//Initializes all of the values in the maze and counts the number of obstacles.
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (arr[i][j] == 1)
			{
				maze[i][j].isSpace = false;

				totalObstacles++;
			}
			else
			{
				maze[i][j].isSpace = true;
			}
		}
	}

	double initialProbability = 0;
	
	double numberOfSpaces = static_cast<double>(ROWS) * static_cast<double>(COLUMNS) - static_cast<double>(totalObstacles);

	if (numberOfSpaces != 0)
	{
		initialProbability = 100 / numberOfSpaces;
		Round(initialProbability);
	}

	//Sets the initial probability of all spaces and obstacles in the maze.
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (maze[i][j].isSpace)
			{
				maze[i][j].probability = initialProbability;
			}
			else
			{
				maze[i][j].probability = 0;
			}
		}
	}
}