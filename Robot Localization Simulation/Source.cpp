// Program Name: Robot Localization Simulation
// Author: woodsj1206 (https://github.com/woodsj1206)
// Description: Uses an HMM algorithm to find the robot's position in a windy maze.
// Course: CIS 479-001
// Date Created: 3/17/22
// Last Modified: 3/20/22
#include <iostream>
#include "Robot.h"

int main() 
{
	//Creates the initial layout of the maze where 0 is a space and 1 is an obstacle.
	int windyMaze[ROWS][COLUMNS] = {{0, 0, 0, 0, 0, 0, 0},
									{0, 0, 1, 1, 1, 1, 0},
									{0, 0, 1, 0, 0, 1, 0},
									{0, 1, 1, 0, 0, 1, 0},
									{0, 0, 0, 0, 1, 1, 0},
									{0, 0, 0, 0, 0, 0, 0}};

	Robot robot(windyMaze);
	
	std::cout << "Initial Location Probabilities" << std::endl;
	robot.PrintMaze();
	
	//Action Sequence:		
	//1. Sensing: [0, 0, 0, 1]
	std::cout << "Filtering after Evidence [0, 0, 0, 1]" << std::endl;
	int evidence_1[] = { 0, 0, 0, 1 };
	
	robot.Sensing(evidence_1);
	robot.PrintMaze();
	
	//2. Moving northward
	std::cout << "Prediction after Action N" << std::endl;
	robot.Moving('N');
	robot.PrintMaze();
	
	//3. Sensing: [0, 1, 0, 0]	
	std::cout << "Filtering after Evidence [0, 1, 0, 0]" << std::endl;
	int evidence_2[] = { 0, 1, 0, 0 };

	robot.Sensing(evidence_2);
	robot.PrintMaze();

	//4. Moving eastward
	std::cout << "Prediction after Action E" << std::endl;
	robot.Moving('E');
	robot.PrintMaze();

	//5. Sensing : [0, 1, 0, 0]
	std::cout << "Filtering after Evidence [0, 1, 0, 0]" << std::endl;
	int evidence_3[] = { 0, 1, 0, 0 };

	robot.Sensing(evidence_3);
	robot.PrintMaze();
	
	//6. Moving eastward
	std::cout << "Prediction after Action E" << std::endl;
	robot.Moving('E');
	robot.PrintMaze();
	
	//7. Sensing : [0, 0, 1, 0]
	std::cout << "Filtering after Evidence [0, 0, 1, 0]" << std::endl;
	int evidence_4[] = { 0, 0, 1, 0 };

	robot.Sensing(evidence_4);
	robot.PrintMaze();

	return 0;
}