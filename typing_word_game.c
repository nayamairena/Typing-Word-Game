/*

Naya Mairena
CS201
Assignment 1
April, 8, 2021

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

/*Constant variables using macros. */
#define WORDS 9
#define SIZE 10

/* Function to display welcome message and instructions. */
void intro();

/* Function to randomize the array of the set words. */
void randomize_words(char words[][SIZE], int);

/* Function to get the user input of each word and compare with the set words. */
void input_compare(char words[][SIZE]);


int main()
{
	/* Defined variables */
	char chosen_words[WORDS][SIZE] = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};	/* Array of set words. */
	char again = 0;
	/* timeval objects for timer. */
	struct timeval start_time;
	struct timeval end_time;
	struct timeval result;

	/* Function calls. */
	intro();

	/*do...while loop to allow user to play the game again. */
	do
	{
		printf("\n\nType out the following words:\n\n");
		randomize_words(chosen_words, WORDS);
		/* Start the timer. */
		gettimeofday(&start_time, NULL);
		input_compare(chosen_words);
		/* End the timer. */
		gettimeofday(&end_time, NULL);
		/* Use timersub function to get final timed result. */
		timersub(&end_time, &start_time, &result);
		printf("\nFinal time: %ld seconds and %d microseconds.\n", result.tv_sec, result.tv_usec);
		printf("\nWould you like to try again? (y for yes, n for no): ");
		again = getchar();	/* Allow the user to play again. */
	}while(again == 'y' || again == 'Y');

	printf("\n\n\t\t\tGOODBYE!\n\n\n");

	return 0;
}


/* This function will display the game instructions and allow the user to start as soon as they hit the enter key. */
void intro()
{
	/* Variable definitions. */
	char enter = 0;
	struct timeval current_time;	

	/* Seed the random generator to make it appear random everytime. */
	gettimeofday(&current_time, NULL);
	srand(current_time.tv_usec);

	printf("\n\n\t\t\tTYPING SPEED GAME\n\n");
	printf("Each word will display one at a time and you must enter the word exactly as you see it.\n");
	printf("If you enter the wrong input, you must try again.\n");
	printf("You will be timed for how quickly you can type each word that is displayed.\n");
	printf("Press enter to start...");

	while(enter != '\n')
		enter = getchar();

	return;
}


/* This function will use the Fisher-Yates Shuffle algorithm to shuffle the words in random order without repeats. */
void randomize_words(char words[WORDS][SIZE], int num)
{
	int i = 0;
	int j = 0;
	char temp[10];

	/* Inside the for loop the array will be sorted randomly and replaced with the words in a new order, one by one. */
	for(i = num - 1; i > 0; i--)
	{
		j = rand() % (i + 1);
		strncpy(temp, words[j], SIZE);
		strncpy(words[j], words[i], SIZE);
		strncpy(words[i], temp, SIZE);
	}

	return;
}


/* This function will take the user input one word at a time. If they enter the wrong word, it will display an error message
and have them enter the correct answer. The answer is compared with the word in the array using strncmp(). */
void input_compare(char words[WORDS][SIZE])
{
	int num = 0;
	char user_word[SIZE];
	int c = 0;

	/* for loop will go through the entire array of randomly sorted words one at a time. */
	for(int i = 0; i < WORDS; ++i)
	{
		printf("%s:\t", words[i]);	/*Print the current word for user to input. */
		do	/*do while loop for when the user inputs incorrect word. Allows them to try again. */
		{
			if(scanf("%10s", user_word) == 1)	/* Uses return value from scanf(). */
			{
				/* Flushing the rest of the line to allow extraneous input. */
				while((c = getchar()) != '\n' && c != EOF);
				num = strncmp(words[i], user_word, SIZE);	/* Uses return value from strncmp(). */
				if(num != 0)	/* The user input was not the correct word, display error message. */
				{
					printf("\nINVALID. Please try again. \n");
					printf("\n%s:\t", words[i]);
				}
			}
			else	/* If input failed to read, give error message. */
				printf("Failed to read word \n\n");
		}while(num != 0);
	}

	return;
}

