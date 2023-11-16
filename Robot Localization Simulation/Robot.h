#pragma once
#include<iostream>
#include<iomanip>
const int ROWS = 6;
const int COLUMNS = 7;

class Robot
{
private:
	struct node 
	{
		double probability;
		bool isSpace;
	};

	node maze[ROWS][COLUMNS];

public:
	Robot();

	Robot(int arr[ROWS][COLUMNS]);
	
	void Moving(char direction);

	void Multiplier(double total);
		
	void PrintMaze();

	void Round(double& number);

	void Sensing(int arr[]);

	void SetMaze(int arr[ROWS][COLUMNS]);
};