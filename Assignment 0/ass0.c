/***********************************************************
Filename: ass0.c
Version: 1.0
Student Name: Ahmed Afzal
Student Number: 040-845-435
Course Name and Number: CST8233 - Numerical Computing
Lab Section: 302
Assignment Number: 0
Assignment Name: Animation Project in C
Due Date: January 27, 2018
Submission Date: January 28, 2018
Professor's name: Andrew Tyler
List of Source and Header Files: ass0.c
Purpose: hold data of an animation using a linked list in
         dynamic memory
***********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC	// need this to get the line identification
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF); // in main, after local declarations
//NB must be in debug build

#include <crtdbg.h>
#include <stdio.h>
#include <string.h>

typedef enum { FALSE = 0, TRUE } BOOL;

struct Frame {
	char* frameName;
	struct Frame* pNext;
};

typedef struct {
	char* animationName;
	struct Frame* frames;
}Animation;

// Forward declarations
void InitAnimation(Animation*);
void InsertFrame(Animation*);
void DeleteFrame(Animation*);
void EditFrame(Animation*);
void ReportAnimation(Animation*);
void CleanUp(Animation*);

int main(void)
{
	char response;
	BOOL RUNNING = TRUE;
	Animation RG;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	InitAnimation(&RG);

	while (RUNNING)
	{
		printf("MENU\n 1. Insert a Frame at the front\n 2. Delete last Frame\n 3. Edit a Frame\n 4. Report the Animation\n 5. Quit\n");
		scanf("%c", &response);

		switch (response)
		{
		case '1':InsertFrame(&RG); break;
		case '2':DeleteFrame(&RG); break;
		case '3':EditFrame(&RG); break;
		case '4':ReportAnimation(&RG); break;
		case '5':RUNNING = FALSE; CleanUp(&RG); break;
		default:printf("Please enter a valid option\n");
		}
		while ((response = getchar()) != '\n' && response != EOF) {}
	}
	return 0;
}

/*************************************************************
Function name:		initAnimation
Purpose:			initialize variables in struct Animation
In parameters:		Animation pointer
Out parameters:
Version:			1.0
Author:				Ahmed Afzal
**************************************************************/
void InitAnimation(Animation* an)
{
	char aName[100];
	int length = 0;
	
	printf("Please enter the Animation name: ");
	scanf("%s", aName);

	an->animationName = malloc(sizeof(char)*(strlen(aName) + 1));
	strcpy(an->animationName, aName);
	an->frames = NULL;

	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}

}

/************************************************
Function name:		InsertFrame
Purpose:			add new Frame to Animation
In parameters:		Animation pointer
Out parameters:
Version:			1.0
Author:				Ahmed Afzal
*************************************************/
void InsertFrame(Animation* an)
{
	char fName[100];
	int size;

	/* create and allocate memory for Frame struct */
	struct Frame *iterator;
	iterator = (struct Frame*)malloc(sizeof(struct Frame));

	printf("Insert a Frame in the Animation\n");
	printf("Please enter the Frame frameName: ");
	scanf("%s", &fName);

	/* get length of fName */
	size = strlen(fName) + 1;
	/* allocate memory for frameName */
	iterator->frameName = (char *)malloc(size);
	/* copy memory of fName to frameName */
	strcpy(iterator->frameName, fName);

	iterator->pNext = an->frames;
	an->frames = iterator;
}

/**************************************************
Function name:		DeleteFrame
Purpose:			delete the last frame in list
In parameters:		Animation pointer
Out parameters:
Version:			1.0
Author:				Ahmed Afzal
***************************************************/
void DeleteFrame(Animation* an)
{
	struct Frame* iterator;

	if (an->frames)
	{
		iterator = an->frames;

		if (iterator->pNext)
		{
			do
			{
				if (iterator->pNext->pNext)
					iterator = iterator->pNext;
				else
				{
					/* release memory of frameName and Animation */
					free(iterator->pNext->frameName);
					free(iterator->pNext);

					iterator->pNext = NULL;
					iterator = iterator->pNext;
				}
			} while (iterator != NULL);
		}
		else
		{
			free(an->frames->frameName);
			free(an->frames);

			an->frames = NULL;
		}
	}
}

/*******************************************************
Function name:		EditFrame
Purpose:			edit a frame and changes it name
In parameters:		Animation pointer
Out parameters:
Version:			1.0
Author:				Ahmed Afzal
********************************************************/
void EditFrame(Animation* an)
{
	char fName[100];
	struct Frame *iterate = an->frames;

	int input = -1;
	int count = 0;

	printf("Edit a Frame in the Animation\n");

	if (iterate)
	{
		++count;

		/* counts how many frames in Animation */
		while (iterate->pNext)
		{
			++count;
			iterate = iterate->pNext;
		}

		do
		{
			printf("There are %d Frame(s) in the list. Please specifiy the index(<= %d) to edit at: ", count, (count - 1));
			scanf("%d", &input);
			
			/* checks for vaild inputs */
			if (input < 0 || input >= count)
					input = -1;
		} while (input == -1);

		count = 0;
		/* resets to start of Animation list */
		iterate = an->frames;

		/* loops until it finds frame to edit */
		while (count < input)
			iterate = iterate->pNext;	

		printf("The name of this Frame is %s. What do you wish to replace it with? ", iterate->frameName);
		scanf("%s", &fName);

		/* release old memory */
		free(iterate->frameName);
		/* allocate memory */
		iterate->frameName = malloc(sizeof(char)*(strlen(fName) + 1));
		strcpy(iterate->frameName, fName);
	}
	else
		printf("Animation has no frames\n");
}

/************************************************************
Function name:		ReportAnimation
Purpose:			report Animation to display Frame list
In parameters:		Animation pointer
Out parameters:
Version:			1.0
Author:				Ahmed Afzal
*************************************************************/
void ReportAnimation(Animation* an)
{
	int counter = 0;

	struct Frame* iterator = an->frames;

	if (an->frames == 0)
	{
		printf("No Frames in the Animation\n");
		return;
	}

	printf("Animation name is %s\n", an->animationName);
	printf("Report the Animation\n");

	while (iterator)
	{
		printf("Image #%d, file name = %s\n", counter++, iterator->frameName);
		iterator = iterator->pNext;
	}
}

/****************************************************************
Function name:		CleanUp
Purpose:			to free all memory
In parameters:		Animation pointer
Out parameters:
Version:			1.0
Author:				Ahmed Afzal
*****************************************************************/
void CleanUp(Animation* an)
{
	struct Frame *tmp;

	if (an->frames == NULL)
	{
		printf("Nothing available");
	}
	else /* nodes exist */
	{
		tmp = an->frames;

		while ((tmp = an->frames) != NULL)
		{
			an->frames = tmp->pNext;

			free(tmp->frameName);
			free(tmp);
			free(an->animationName);
			
		}
	}
}