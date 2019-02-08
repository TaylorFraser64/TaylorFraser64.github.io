/*
* Author: Taylor Fraser
* Purpose: This program implements a simple counter that counts the
* number of elapsed seconds. 
* The user inputs a start and stop value,
* and the program will begin counting up from that number, stopping either
* when the stop value is reached, or the user flips the "RUN" switch.
* If the user flips the "RESET" switch, the counter will be reset,
* and the program will ask for inputs once more.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include <DAQlib.h>

#define TRUE 1
#define FALSE 0

/* The input channels for the two switches */
#define RUN_SWITCH 0
#define RESET_SWITCH 1

/* The states of the switches */
#define SWITCH_ON 1
#define SWITCH_OFF 0

/* Number of LED displays in the LED screen */
#define NUM_DISPLAYS 8

/* Value to write to the LED display to turn it off (space) */
#define SPACE_CHAR 0

/* 1 second = 1000 miliseconds for the delay */
#define DELAY_TIME 1000

/* Number of displays in the LED screen. */
#define NUM_DISPLAYS 8

/* A SPACE character turns all segments off */
#define SPACE_CHAR 0

/* Define other constants */
#define TRUE 1
#define FALSE 0

/* function prototypes for all the functions implemented here */
void WorkFunction();
void writeNumber(int number);
void writeDigit(int digit, int position);
void writeNumber(int number);
void writeDigit(int digit, int position);

int main(void)
{
	int setupNum;
  /* This si for setting up the DAC */
	printf("Enter configuration type (0 for the device or 4 for the simulator): ");
	scanf("%d", &setupNum);

	if (setupDAQ(setupNum) == TRUE)
		WorkFunction();
	else
		printf("ERROR: Cannot initialize system\n");

	system("PAUSE");
	return 0;
}

/* Implements the counter logic. */
/* Reads the two switches and act accordingly. */
void WorkFunction()
{
	int start;
	int stop;
	int canContinue = FALSE;
	int current;

	while (continueSuperLoop() == TRUE){

    /* User Inputs */
		printf("please enter the start value\n");
		scanf("%i", &start);
		current = start;
		printf("please enter the stop value\n");
		scanf("%i", &stop);
    
    /* Initial Write*/
		if (digitalRead(RUN_SWITCH) == FALSE && digitalRead(RESET_SWITCH) == FALSE){
			writeNumber(start);
			canContinue = TRUE;
		}
    
    /* Do this while the Reset switch is not on. Should the reset swiiitch be flipped, 
    *  the code will break from this loop and restart  */
    
		while (digitalRead(RESET_SWITCH) == FALSE){
			while (digitalRead(RUN_SWITCH) == FALSE && canContinue == TRUE){
				Sleep(1000);
				current += 1;
				writeNumber(current);
				if (current >= stop){
					canContinue = FALSE;
				}
			}
      /* If the RUN switch is flipped, stop counting*/
			while (digitalRead(RUN_SWITCH) == TRUE  && canContinue == TRUE || FALSE){
				writeNumber(current);
			}
      /* If we have reached the stop value, stop counting */
			while (digitalRead(RUN_SWITCH) == TRUE || FALSE  && canContinue == FALSE){
				writeNumber(current);
			}
		}
	}
	
}


/* Function: Write Number
*  Purpose: Writes a number to a seven segment display
*  Inputs: The number to be written
*  Returns: None
* Makes use of writeDigit()
*/

void writeNumber(int number){
	int pos;
	int digit;

	pos = 0;

	do {
		digit = number % 10;
		number = number / 10;

		writeDigit(digit, pos);

		pos++;
	} while (pos < NUM_DISPLAYS && number != 0);

	while (pos < NUM_DISPLAYS)
	{
		displayWrite(SPACE_CHAR, pos);
		pos++;
	}
}


/* Function: Write Digit
*  Purpose: Writes a digit to a seven segment display using a lookup table.
*  Inputs: The digit to be written
*  Returns: None
*/

void writeDigit(int digit, int position)
{
	static int digits_table[10] = {
		252, 96, 218, 242, 102, 182, 190, 224, 254, 246 };

	displayWrite(digits_table[digit], position);
}

