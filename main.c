/*
Name : Alvin_J
Roll No : 25021D_172
Project name : Arbitrary Precision Calculator
Date of completion : 14/12/2025
Description : An Arbitrary Precision Calculator in C using doubly linked lists
			  to perform addition, subtraction, multiplication, and division 
			  on large integers beyond native data type limits.

Functionalities : 

#1 Addition
#2 Subtraction
#3 Multiplication
#4 Division
#5 Modulus

Note : Works for Positive & Negative whole numbers
	   Modulus follows C semantics -> result sign follows dividend.
	   Division uses truncation, not rounding.
	   No floating-point input support. Decimals are generated only as division output.
*/

#include "apc.h"

int main(int argc, char *argv[])
{
	// Validate CLA
	if(argc == 4)
	{
		if(strlen(argv[1]) == 0 || strlen(argv[3]) == 0)
		{
			printf("Invalid input - Operand missing!\n");
			return 0;
		}
	}
	else
	{
		printf("Invalid arguments!\n"
		"Usage :- ./a.out < Operand 1 > < Operator > < Operand 2 >\n");
		return 0;
	}

	//Validate operator
	char operator = argv[2][0];

	if((strchr("+-x/%", operator) == NULL) || strlen(argv[2]) != 1)
	{
		printf("Invalid operator!\n"
		"Operators Allowed:\n"
		"\t+ (Addition)\n"
		"\t- (Subtraction)\n"
		"\tx (Multiplication)\n"
		"\t/ (Division)\n"
		"\t%% (Modulus)\n");
		return 0;
	}
    
	// Flags for negative nums
	Sign s = {0};

	// Lists for Inputs and Result
	Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL; 
    Dlist *headR = NULL, *tailR = NULL;

	// Convert input numbers into lists
	digit_to_list(&s, &head1, &tail1, &head2, &tail2, argv);
	
	switch (operator)
	{
		// Addition
		case '+':
			print_inputs(argv);
			if(addition(&s, &head1, &tail1, &head2, &tail2, &headR, &tailR) == FAILURE)
			printf("Addition Failed!");
			else
			{
				printf("Output\t: ");
				print_result(&s, &headR);
			}
			break;

		// Subtraction
		case '-':
			print_inputs(argv);
			if(subtraction(&s, &head1, &tail1, &head2, &tail2, &headR, &tailR) == FAILURE)
			printf("Subtraction Failed!");
			else
			{
				printf("Output\t: ");
				print_result(&s, &headR);
			}
			break;

		// Multiplication
		case 'x':	
			print_inputs(argv);
			if(multiplication(&s, &head1, &tail1, &head2, &tail2, &headR, &tailR) == FAILURE)
			printf("Multiplication Failed!\n");
			else
			{
				printf("Output\t: ");
				print_result(&s, &headR);
			}
			break;

		// Division
		case '/':	
		{
			int precision;
			printf("Enter the number of decimal places : ");
			scanf("%d", &precision);
			print_inputs(argv);
			if(division(&s, &head1, &tail1, &head2, &tail2, &headR, &tailR, precision) == FAILURE)
			printf("Division Failed!\n");
			else
			{
				printf("Output\t: ");
				print_result(&s, &headR);
			}
			break;
		}

		// Modulus
		case '%':	
			print_inputs(argv);
			if(modulus(&s, &head1, &tail1, &head2, &tail2, &headR, &tailR) == FAILURE)
			printf("Modulus Failed!\n");
			else
			{
				printf("Output\t: ");
				print_result(&s, &headR);
			}
			break;

		default:
			printf("Invalid Operator!\n");
	}

	return 0;
}