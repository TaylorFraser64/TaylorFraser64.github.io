#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <conio.h>

void clearScreen(void);
void printScreen(void);
void mySetup(void);
void directionChange(char key);
void walk(void);
void spawnFood(void);
void getNewPlaySpace(void);

int playSpace[12][12];
int currentDirection = 1;
int xpos = 5;
int ypos = 11;
int alive = 1;
int length = 1;
int foodposx = 0;
int foodposy = 0;

int main(void){
	mySetup();
	printScreen();
	while (alive){

		if (_kbhit()) {
			directionChange(_getch());
		}

		getNewPlaySpace();
		clearScreen();
		printScreen();


	}
	system("pause");
	return 0;
}

void mySetup(){
	int i;
	int j;
	
	for (i = 0; i < 12; i++){
		for (j = 0; j < 12; j++){
			playSpace[i][j] = 1;
		}
	}
	spawnFood();
}

void clearScreen(){
	system("cls");
}

void printScreen(){
	int i;
	int j;
	for (i = 0; i < 12; i++){
		for (j = 0; j < 12; j++){
			printf("%i", playSpace[i][j]);
		}
		printf("\n");
	}
}

void directionChange(char key){
	// 1 - up
	// 2 - right
	// 3 - down
	// 4 - left


	switch (key){
	case 'w':
		if (currentDirection != 3){
			currentDirection = 1;
		}
		break;
	case'a':
		if (currentDirection != 2){
			currentDirection = 4;
		}
		break;
	case 's':
		if (currentDirection != 1){
			currentDirection = 3;
		}
		break;
	case'd':
		if (currentDirection != 4){
			currentDirection = 2;
		}
		break;


	}
}

void walk(){
	int newxpos = 0;
	int newypos = 0;

	if (currentDirection == 1){
		newxpos = xpos;
		newypos = ypos + 1;
	}
	if (currentDirection == 2){
		newxpos = xpos + 1;
		newypos = ypos;
	}
	if (currentDirection == 3){
		newxpos = xpos;
		newypos = ypos - 1;
	}
	if (currentDirection == 4){
		newxpos = xpos - 1;
		newypos = ypos;
	}

	if (newypos > 11 || newxpos > 11 || newypos < 0 || newxpos < 0){
		alive = 0;
	}

	if (newypos == foodposy && newxpos == foodposx){
		length++;
		spawnFood();
	}

	xpos = newxpos;
	ypos = newypos;


}

void spawnFood(){
	foodposx = rand() % 12;
	foodposy = rand() % 12;
	
}

void getNewPlaySpace(){
	int i;
	int j;
	for (i = 0; i < 12; i++){
		for (j = 0; j < 12; j++){
			playSpace[i][j] = 1;
		}
	}
	playSpace[foodposy][foodposx] = 8;
	playSpace[ypos][xpos] = 0;
}
