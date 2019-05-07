/***********************************************************
Filename: ass1.c
Version: 1.0
Student Name: Ahmed Afzal
Student Number: 040-845-435
Course Name and Number: CST8233 - Numerical Computing
Lab Section: 302
Assignment Number: 1
Assignment Name: Building Motion Simulation
Due Date: February 17, 2019
Submission Date: February 13, 2019
Professor's name: Andrew Tyler
List of Source and Header Files: ass1.c
Purpose: investiage a less accurate but faster
		 Maclaurin Series
***********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef enum { FALSE = 0, TRUE } BOOL;

void evaluateSeries();

int main(void)
{
	char option;
	BOOL RUNNING = TRUE;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	while (RUNNING)
	{
		printf("Evaluate the Maclaurin Series approximation to exp(-t)*cost(t)\n\n");
		printf("1: Evaluate the series\n");
		printf("2: quit\n\n");

		scanf("%c", &option);

		switch (option)
		{
		case '1':
			evaluateSeries();
			break;
		case '2':
			RUNNING = FALSE;
			printf("Quitting");
			break;
		default:
			printf("Please enter a valid option\n");
		}
		printf("\n");

		while ((option = getchar()) != '\n' && option != EOF);
	}
	return 0;
}

/**********************************************
Function name: evaluateSeries()
Purpose: to evaluate the Maclaurin Series for
	     d(t) = e^-t * cos(t)
Function In parameters: none
Function Out parameters: none
Version: 1.0
Author: Ahmed Afzal
***********************************************/
void evaluateSeries()
{
	int terms;

	double range, increments, x, series, exact, exactError, truncError, first_truncation;
	range = increments = x = series = exact = exactError = truncError = first_truncation = 0;

	printf("\nEvaluating the series\n");

	/* get the number of terms */
	do
	{
		printf("Please enter the number of terms in the series (max 5 terms): ");

		if (!scanf("%d", &terms))
			while ((terms = getchar()) != '\n' && terms != EOF);

	} while (terms <= 0 || terms >= 6);

	printf("\n");

	/* get the range */
	do
	{
		printf("Please enter the range of t to evaluate in 10 increments(0.0 < t < +2.0): ");

		if (!scanf("%lf", &range))
			while ((range = getchar()) != '\n' && range != EOF);

	} while (range < 0.0 || range > 2.0);

	printf("\nMACLAURIN SERIES\n");

	printf("   X\t\t Series\t         Exact\t        Exact ""&"" Error\tTrunc. ""&"" Error\n");

	for (int i = 0; i <= 10; i++)
	{
		/* to get the increments of the x-value */
		x = x + increments;
		increments = range / 10;

		/* calculate the series and first truncation based on the number of terms */
		if (terms == 1)
		{
			series = 1;
			first_truncation = x;
		}
		else if (terms == 2)
		{
			series = 1 - x;
			first_truncation = (x * x * x) / 3;
		}
		else if (terms == 3)
		{
			series = 1 - x + ((x * x) / 2);
			first_truncation = (x * x * x * x) / 6;
		}
		else if (terms == 4)
		{
			series = 1 - x + (x * x * x) / 3 - (x * x * x * x) / 6;
			first_truncation = (x * x * x * x * x) / 30;
		}
		else if (terms == 5)
		{
			series = 1 - x + (x * x * x) / 3 - (x * x * x * x) / 6 + (x * x * x * x * x) / 30;
			first_truncation = -(x * x * x * x * x * x * x) / 630;
		}

		/* formula to get exact value */
		exact = exp(-x) * cos(x);
		/* formula to get exact error */
		exactError = 100 * (exact - series) / exact;
		/* formula to get truncation error  */
		truncError = 100 * first_truncation / series;
		
		printf("%.3e\t", x);
		printf("%.5e\t", series);
		printf("%.5e\t", exact);
		printf("%.5e\t", exactError);
		printf("%.5e\n", truncError);
	}
}