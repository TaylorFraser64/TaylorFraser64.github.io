/*
//  Scrolling Display by Taylor Fraser
//       33803164   //  L2C
//    taylor.fraser64@alumni.ubc.ca
//
//Purpose: This program scrolls a message back and forth across a 7 segment display
//Date : 4/4/17
//
// OPTIONAL PART: You can change the speed of the scrolling with Switch 1. 
//               
*/





#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <DAQlib.h>
#include <Windows.h>
#define TRUE 1
#define FALSE 0
#define NUM_DISPLAYS 8
#define SPACE_CHAR 0
#define SIZE1 5
#define SIZE2 3
#define SWITCH0 0
#define SWITCH1 1

void clearDisplay(void);
int enterStageRight(int message[], int counter, int size);
void scrollMessage(int message[], int counter, int size);
int getSleep(void);
int changeDirection( int pastDirection);







////////////////////////////////
/*
   Main
   A driver function for the other functions
*/
////////////////////////////////


int main(void){

	
	//Declarations
	int a = 10;
	int b = 11;
	int c = 12;
	int d = 13;
	int e = 14;
	int f = 15;
	int g = 16;
	int h = 17;
	int i = 18;
	int j = 19;
	int k = 20;
	int l = 21;
	int m = 22;
	int n = 23;
	int o = 24;
	int p = 25;
	int q = 26;
	int r = 27;
	int s = 28;
	int t = 29;
	int u = 30;
	int v = 31;
	int w = 32;
	int x = 33;
	int y = 34;
	int z = 35;

	//Replacements
	g = y;
	k = h;
	m = r;



	//Messages
	int message1[SIZE1] = { 6, 4, l, 2, c };
	int message2[SIZE2] = { c, a, t };
	
	//Other Vars
	int choice;
	int counter = 0;


	// clear the display. Idk I had the function and I thought it wouldnt hurt to stick it at the beginning.
	//clearDisplay();


	//Prompts to select the message the user wants
	printf("Please select the message you would like to display\n Enter [1] for [64L2C]\n Enter [2] for [Cat]\n");
	scanf("%i", &choice);


	//Setup DAQ and start the Scroll function loop with the chosen message
	setupDAQ(4);
	if (continueSuperLoop()){
		
		
		if (choice == 1){
			counter = enterStageRight(message1, counter, SIZE1);
			scrollMessage(message1, counter, SIZE1);
		}

		if (choice == 2){
			counter = enterStageRight(message2, counter, SIZE2);
			scrollMessage(message2, counter, SIZE2);
		}
	}
	
	

	system("Pause");
	return 0;

}









////////////////////////////////
/*
Enter Stage Right
Scrolls the message in from the right side until it is fully displayed
Paramaters: 
    message[] : message to display
	counter : The current count / tick the program has reached
	size: size of the message to be displayed
Returns: The counter value the function terminated at
*/
////////////////////////////////


int enterStageRight(int message[], int counter, int size){
	int loopCounter;
	//Lookup table to translate alphabet numbers to appropriate values to display letters on the seven segment display
	int table[] = { 252, 96, 218, 242, 102, 182, 190, 224, 254, 246, 238, 62, 26, 122, 158, 142, 246, 46, 96, 112, 110, 28, 168, 42, 58, 206, 230, 10, 182, 30, 56, 56, 84, 110, 118, 218 };
	int sleepTime;

	//Loop to scroll the message onto the screen
	while (counter<size && continueSuperLoop()){
		int pos = counter;
		for (loopCounter = 0; loopCounter < size; loopCounter++){
			displayWrite(table[message[loopCounter]], pos);
			pos--;
		}
		
		counter++;

		//Get sleep time from switch and sleep for that time
		sleepTime = getSleep();
		Sleep(sleepTime);
	}
	
	return counter;
}








////////////////////////////////
/*
Scroll Message
Scrolls the message back and forth across the screen
Paramaters:
   message[] : message to display
   counter : The current count / tick the program has reached
   size: size of the message to be displayed
*/
////////////////////////////////


void scrollMessage(int message[], int counter, int size){

	int loopCounter;
	int startPos = size-1;
	int pos = 0;
	int diff = NUM_DISPLAYS - size; //Used in movement calculations
	int table[] = { 252, 96, 218, 242, 102, 182, 190, 224, 254, 246, 238, 62, 26, 122, 158, 142, 246, 46, 96, 112, 110, 28, 168, 42, 58, 206, 230, 10, 182, 30, 56, 56, 84, 110, 118, 218 };
	int sleepTime;

	//Counter == size upon first looping.
	//Counter will be used from here on to measure if the message should be moved to the right or the left.
	//Yes, passing counters between functions dosent really do anything as they are reset to zero each time, but it was useful in development and I figured it could be useful if a person wanted to modify/resuse the program in some way.
	counter = 0;

	// Main loop program will operate in until termination
	while (continueSuperLoop()){

		//Counter loops from 0 to 2*diff. If counter is less than diff, message will move left. If counter is greater than diff, message will move right.
		
		if (counter < diff){
			startPos++;
		}
		
		if (counter >= diff){
			startPos--;
		}
			
		if (diff == 0){
			startPos = NUM_DISPLAYS - 1;
		}


		pos = startPos;

		for (loopCounter = 0; loopCounter < size; loopCounter++){
			displayWrite(table[message[loopCounter]], pos);
			pos--;
		}


		counter++;
		if (counter>(2 * diff) - 1){
			counter = 0;
		}

		//Clear the bits of the display where the message should have moved away from
		displayWrite(0, startPos + 1);
		displayWrite(0, startPos -size);

		//Get sleep time from switches and sleep.
		sleepTime = getSleep();
		Sleep(sleepTime);

	}
}









////////////////////////////////
/*
Get Sleep
Reads the status of Switch 1 (The speed switch), and sets the sleep time in between ticks accordingly.
   If the switch is on, sleep is set to 0.5s. If the switch is off, sleep is set to 1s.
Returns: The appropriate sleep time.
*/
////////////////////////////////


int getSleep(void){
	int status;
	int result;
	status = digitalRead(SWITCH1);
	if (status == 0){
		result = 1000;
	}
	else{
		result = 500;
	}

	return result;
}





////////////////////////////////
/*
Clear Display
Clears the entire display
(was useful in algorithm delevopment and testing)
*/
////////////////////////////////

void clearDisplay(void){
	int counter;
	for (counter = 0; counter < NUM_DISPLAYS; counter++){
		displayWrite(0, counter);
	}
}




//Have a nice day :)
