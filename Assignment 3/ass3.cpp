/*****************************************************************
Filename: ass3.cpp
Version: 1.0
Student Name: Ahmed Afzal
Student #: 040-845-435
Course Name and Number: CST8233 - Numerical Computing
Lab Section: 302
Assignment #: Assignment 3
Assignment Name: Bungee Jump
Due Date: Apr 14, 2019
Submission Date: Apr 14, 2019
Professor's Name: Andrew Tyler
Source and Header Files: ass3.cpp
Purpose: use Heun's method to calculate a bungee jump
******************************************************************/

#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;

void startSimulation();


/****************************************
Function name: main()
Purpose: to display the menu
Function In parameters: none
Function Out parameters: none
Version: 3.0
Author: Ahmed Afzal
*****************************************/
int main(void)
{
	char option;

	while (1)
	{
		system("cls");

		cout << "Bungee Jumping" << endl;
		cout << "1. Start" << endl;
		cout << "2. Exit" << endl;

		fflush(stdin);

		cin >> option;
		
		switch (option) 
		{
			case '1':
				system("cls");
				startSimulation();
				break;
			case '2':
				return 0;
			default:
				break;
		}
	}
}

/****************************************
Function name: startSimulation
Purpose: to calculate a bungee jump
Function In parameters: none
Function Out parameters: none
Version: 4.0
Author: Ahmed Afzal
*****************************************/
void startSimulation()
{
	double drag = 0.0;
	double accel = 0.0;
	double speed = 0.0;
	double prev_speed = 0.0;
	double height = 200.0;
	double time_elapsed = 0.0;
	clock_t curr_time, prev_time = 0;
	clock_t base_time = clock();

	while (1)
	{
		curr_time = clock() - base_time;
		time_elapsed = ((double)(curr_time - prev_time)) / CLOCKS_PER_SEC;

		/* calculations */
		accel = 9.8 - drag / 68 * (speed + 8.0 * pow(speed / 46, 2)) - 0.04 * (200 - height);
		speed = speed + accel * time_elapsed;
		height = height - ((speed + prev_speed) / 2) * time_elapsed;

		prev_time = curr_time;
		prev_speed = speed;

		cout << "Press q to quit; w to increase drag; e to decrease drag" << endl;
		cout << "minute = " << (curr_time / (CLOCKS_PER_SEC * 60)) % 60 << "; second = " << (curr_time / CLOCKS_PER_SEC) % 60 << "; millisec = " << (curr_time / CLOCKS_PER_SEC * 1000) << endl;

		/* get key press */
		if (_kbhit())
		{
			switch (_getch()) 
			{
			case 'w': 
				if (drag < 10)
					drag += 1.0;
				cout << "\t w was pressed - increase wind drag" << endl;
				break;
			case 'e': 
				if (drag > 1.0)
					drag -= 1.0;
				cout << "\t e was pressed - decrease wind drag" << endl;
				break;
			}
		}

		cout << "\t Bungee: EXTENDED" << endl;
		cout << "\t Wind Drag = " << drag << endl;
		cout << "\t speed of descent = " << speed << " m/s" << endl;
		cout << "\t height above ground = " << height << " metres" << endl;

		if (height <= 0)
		{
			cout << "Crashed!" << endl;
			cout << "Press a button to continue" << endl;

			fflush(stdin);
			_getch();

			return;
		}
			
		system("cls");
	}
}