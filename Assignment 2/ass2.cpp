/*****************************************************************
Filename: ass2.cpp
Version: 1.0
Student Name: Ahmed Afzal
Student #: 040-845-435
Course Name and Number: CST8233 - Numerical Computing
Lab Section: 302
Assignment #: Assignment 2
Assignment Name: Moore's Law
Due Date: Mar 17, 2019
Submission Date: Mar 18, 2019
Professor's Name: Andrew Tyler
Source and Header Files: ass2.cpp
Purpose: fit data using linear regression least squares method for
		 an exponential function
******************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Values
{
	double S, Sx, Sy, Sxx, Sxy;
	double Delta, m, c, a;
};

void calculate(Values *);
void resetvalues(Values *);
void subMenu(Values *);
bool getfile(Values *);
void extrapolation(Values *);

/****************************************
Function name: main()
Purpose: to display the menu
Function In parameters: none
Function Out parameters: none
Version: 3.0
Author: Ahmed Afzal
*****************************************/
int main()
{
	int num = 0;
	Values val = {0,0,0,0,0,0,0,0,0}, *value = &val;
	Values valPower = {0,0,0,0,0,0,0,0,0}, *valuePower = &valPower;

	do
	{
		printf("\n\tLEAST_SQUARE LINEAR REGRESSION\n"
			"MENU\n"
			" 1. Exponential Fit\n"
			" 2. Quit\n");

		if (!scanf("%d", &num))
			while ((num = getchar()) != '\n' && num != EOF);

		switch (num)
		{
			case 1:
				getfile(value);
				calculate(value);
				printf("\nLinear Regression Fit: transistor count = %e*exp(%e*(year-1970))\n", value->a, value->m);
				subMenu(value);
				break;
			case 2:
				break;
			default:
				printf("Invalid Input\n");
				break;
		}
	} while (num != 2);

	return 0;
}

/****************************************
Function name: resetValues
Purpose: reset values
Function In parameters: Values *val
Function Out parameters: none
Version: 1.0
Author: Ahmed Afzal
*****************************************/
void resetvalues(Values *val)
{
	val->S = 0;
	val->Sx = 0;
	val->Sxx = 0;
	val->Sxy = 0;
	val->Sy = 0;
	val->a = 0;
	val->c = 0;
	val->m = 0;
	val->Delta = 0;
}

/****************************************
Function name: subMenu
Purpose: display sub menu
Function In parameters: Values *val
Function Out parameters: none
Version: 1.0
Author: Ahmed Afzal
*****************************************/
void subMenu(Values *val)
{
	bool running = true;
	int num = 0;

	while (running)
	{
		printf("\nMENU\n");
		printf(" 1. Extrapolation\n");
		printf(" 2. Main Menu\n");

		if (!scanf("%d", &num))
			while ((num = getchar()) != '\n' && num != EOF);

		switch (num)
		{
			case 1:
				extrapolation(val);
				break;
			case 2:
				running = false;
				break;
			default:
				printf("Invalid option");
				break;
		}
	}
}

/*****************************************************
Function name: getfile
Purpose: get values from file and place them in array
Function In parameters: Values *val
Function Out parameters: true
Version: 2.0
Author: Ahmed Afzal
******************************************************/
bool getfile(Values *val)
{
	int i = 0;
	double x = 0, y = 0;
	char cpuName[50], fileName[100];

	// file pointer
	FILE *file;

	printf("Please enter the name of the file: ");
	scanf("%s", fileName);

	// open the file
	file = fopen(fileName, "r");

	printf("year\t tranCount\t Name\n");

	// loop through file and get values
	do
	{
		// check if file exists
		if (file == NULL)
		{
			printf("Error! File cannot be opened\n");
			break;
		}

		// can't properly read the file
		if (!fscanf(file, "%s %lf %lf", &cpuName, &x, &y))
		{
			printf("Error Reading File");
			fclose(file);
			return false;
		}

		printf("%.0f\t %.3e\t %s\n", x + 1970, y, cpuName);

		// place values from text file into arrays
		val->Sx += x;
		val->Sy += log(y);
		val->Sxx += x * x;
		val->Sxy += x * log(y);
		++i;

	} while (!feof(file));

	val->S = i;

	printf("\nThere are %d records\n", i);

	return true;
}

/**********************************************
Function name: calculate
Purpose: calculate the equation
Function In parameters: Values *val
Function Out parameters: none
Version: 1.0
Author: Ahmed Afzal
***********************************************/
void calculate(Values *val)
{
	val->Delta = (val->S * val->Sxx) - (val->Sx * val->Sx);
	val->m = ((val->S * val->Sxy) - (val->Sx * val->Sy)) / val->Delta;
	val->c = ((val->Sxx * val->Sy) - (val->Sx * val->Sxy)) / val->Delta;
	val->a = exp(val->c);
}

/**********************************************
Function name: extrapolation
Purpose: extrapolate the values
Function In parameters: Values *val
Function Out parameters: none
Version: 1.0
Author: Ahmed Afzal
***********************************************/
void extrapolation(Values *val)
{
	int year, newYear;
	double tranCount, tranCount2, otherNum, rateIncrease, diffTranCount;

	printf("Please enter the year to extrapolate to: ");
	scanf("%d", &year);

	// calculate the values
	newYear = year - 1970;
	tranCount = (val->a) * (exp(val->m*newYear));
	tranCount2 = (val->a) * (exp(val->m*(newYear - 1)));
	diffTranCount = (tranCount) - (tranCount2);
	otherNum = (tranCount) / (diffTranCount);
	rateIncrease = ((tranCount * otherNum) / 10) - 50000000;

	printf("Year = %d\n", year);
	printf("transistor count = %.3e\n", tranCount);
	printf("rate of count increase = %.3e transistors/year", rateIncrease);
}