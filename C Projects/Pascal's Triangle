/*Author: Taylor Fraser
*Purpose: This piece of code prints a Pascal's triangle of a magnitude specified by the user.
*First the user is asked to input a magnitude of their choice. Valid choices for this program are magnitudes from 1-12.
*Using a variety of functions and loops, the code then prints out a pascal's triangle.
For example, given the input 12, the code will print
*   1
*   1   1
*   1   2   1
*   1   3   3   1
*   1   4   6   4   1
*   1   5  10  10   5   1
*   1   6  15  20  15   6   1
*   1   7  21  35  35  21   7   1
*   1   8  28  56  70  56  28   8   1
*   1   9  36  84 126 126  84  36   9   1
*   1  10  45 120 210 252 210 120  45  10   1
*   1  11  55 165 330 462 462 330 165  55  11   1
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int myFactorial(int num);
int n_choose_r(int num1, int num2);
int getInputInRange(int min, int max);
void Pascal(int size);


/* Main loop */
int main(void){
	int size;
	
	size = getInputInRange(1, 12);
	Pascal(size);

	system("pause");
	return 0; 
}



/* Function: myFactorial
* Purpose: This Function determines the factorial of the number given
* Inputs: number to be factorial-ed
* Returns: The Factorial of the number
*/

int myFactorial(int num){
	int result = num;
	int count = num - 1;

	if (num == 0){
		result = 1;
	}
	else{
		while (count > 0){
			result = result*count;
			count--;
		}
	}

	return result;
}



/* Function: n_choose_r
* Purpose: This Function calculates the propability of choosing r objects from n possibilities
* Inputs: n: possibilities, and r: number of objects to choose
* Returns: (n!)/(r!(n-r)!)
*/
int n_choose_r(int num1, int num2){
	int result;
	result = myFactorial(num1) / (myFactorial(num2) * myFactorial(num1 - num2));
	return result;
}




/* Function: get Input in Range
* Purpose: This Function asks the user for a number in between two specified numbers, 
* if the user inputs an invalid number, the program will inform the user that their selection is invalid and ask again.
* Inputs: the minimum and maximum of the range
* Returns: The user's selection
*/

int getInputInRange(int min, int max){
	int response;
	printf("enter a number between to equal to %i and %i\n", min, max);
	scanf("%i", &response);
	while (response<min || response>max){
		printf("That number is not valid. Please enter a number between or equal to %i and %i \n", min, max);
		scanf("%i", &response);
	}
	return response;

}



/* Function: Pascal
* Purpose: This Function prints a pascal's triangle
* Inputs: size or magnitude of the triangle to be printed
* Returns: None
*/

void Pascal(int size){
	int rowcount = 1;
	int colcount = 1;

	while (rowcount <= size){
		while (colcount <= rowcount){
			int num = n_choose_r(rowcount - 1, colcount - 1);

			if (num < 10){
				printf("   %i", num);
			}
			else{
				if (num < 100){
					printf("  %i", num);
				}
				else{
					printf(" %i", num);
				}
			}
			colcount++;
		}

		colcount = 1;
		printf("\n");
		rowcount++;
	}




}
