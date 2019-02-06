/*
*Author: Taylor Fraser
*Purpose: A simple Betting game. User inputs value of wallet, can bet money. 
*Wallet value is monitored and kept track of.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(void){
system("pause");
}


/*
int rollDie(void);
int roll2Die(void);

int main(void){

	int wallet;
	int bet;
	int roll;
	int pointVal;
	int playAgain = 1;

	printf("WELCOME TO TAYLORS AMAAAZING GAME OF CHANCE!!\n\n");

	printf("How much money do you have to play with?\n");
	scanf("%i", &wallet);

	while (wallet < 5){
		printf("Sorry, but you have less money in your wallet than the minimum bet. Come back when you've a little more, mmm, richer.\n\n\n    ***\n\n\nOh? You're back!\n");
		printf("How much money do you have to play with?\n");
		scanf("%i", &wallet);
	}
	
	


	while (playAgain == 1){

		bet = -1;

		
		while (bet == -1){
			printf("\n\n\n");
			printf("You have %i in your wallet\n", wallet);
			printf("Place your bet! (Min 5$):");
			scanf("%i", &bet);

			if (bet > wallet){
				printf("You can't bet more than you have in your wallet! Try again.\n");
				bet = -1;
			}
			if (bet < 5){
				printf("The value you entered is less than the minimum bet. Try again\n");
				bet = -1;
			}
		}

		roll = roll2Die();
		printf("You rolled a(n) %i\n", roll);
		if (roll == 7 || roll == 11){
			printf("You win! %i$ has been added to your wallet!\n", bet);
			wallet += bet;
		}
		else{
			if (roll == 2 || roll == 3 || roll == 12){
				printf("Sorry, you lose. %i$ has been removed from your wallet.\n", bet);
				wallet -= bet;
			}
			else{
				printf("Rolling for point: %i...\n", roll);
				pointVal = roll;
				roll = -1;
				while (roll != pointVal && roll != 7){
					roll = roll2Die();
					if (roll == pointVal){
						printf("You rolled a(n) %i, you win! %i$ has been added to your wallet!\n", roll, bet);
						wallet += bet;
					}
					if (roll == 7){
						printf("You rolled a(n) %i. Sorry, you lose. %i$ has been removed to your wallet.\n", roll, bet);
						wallet -= bet;

					}
				}

			}
		}

		if (wallet < 5){
			printf("Uh oh! Looks like you no longer have enough money to play! Goodbye.\n");
			playAgain = -1;
		}
		else{
			playAgain = 2;
			while (playAgain != 1 && playAgain != 0 ){
				printf("Enter 1 to play again, 0 to quit.\n");
				scanf("%i", &playAgain);
			}

			if (playAgain == 1){
				printf("Ok!\n");
			}
			if (playAgain == 0){
				printf("You have %i$ left in your wallet. Goodbye!\n", wallet);
			}
		}

		

	}

	system("pause");
	return 0;
}

/* A function to simulate the solling of a standard die.
*Inputs: none
*Returns: Value between 1 - 6
*/
int rollDie(void){
	srand(time(0));
	int num;
	num = (rand() % 6) + 1;
	return num;
}


/* A function to simulate the rolling of two dice
*Inputs: none
*Returns: Value between 1 - 12
*Dependency on rollDie()
*/
int roll2Die(void){
	int num1 = rollDie();
	int num2 = rollDie();
	int result = num1 + num2;
	return result;
}
*/
