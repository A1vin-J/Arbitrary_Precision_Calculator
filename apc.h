#ifndef APC_H
#define APC_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS 0
#define FAILURE -1

// Node in List
typedef struct node
{
	struct node *prev;
	struct node *next;
	int data;
}Dlist;

// Mode options
typedef enum
{
	div_mode,
	mod_mode
}Modes;

// Flags for negative nums
typedef struct
{
	int sign1;		// num 1 - neg
	int sign2;		// num 2 - neg
	int res_sign;	// result - neg
}Sign;

// Main Operations

// Addition [addition.c]
int addition(Sign *s, Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

// Subtraction [subtraction.c]
int subtraction(Sign *s, Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

// Multiplication [multiplication.c]
int multiplication(Sign *s, Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

// Division [division.c]
int division(Sign *s, Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR, int precision);

// Modulud [modulus.c]
int modulus(Sign *s, Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);


// Core Functionalities [cores.c]

// Addition core
int add_core(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

// Subtraction core
int sub_core(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

// Multiplication core
int mul_core(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

// Division core
int div_core(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR, Modes mode, int precision);


// Helper Functions - [Utils.c]

// Store the operands into the list
void digit_to_list(Sign *s, Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,char *argv[]);

//Compare Function
int compare(Dlist *head1, Dlist *head2);

// Borrow Function
void borrow(Dlist *node);

// Print list
void print_list(Dlist *head);

// Insert node at first
int insert_at_first(Dlist **head, Dlist **tail, int data);

// Insert node at last
int insert_at_last(Dlist **head, Dlist **tail, int data);

// Delete the node at first
int delete_first(Dlist **head, Dlist **tail);

// Delete List
int delete_list(Dlist **head, Dlist **tail);

// Printing Inputs
void print_inputs(char *argv[]);

// Printing Result
void print_result(Sign *s, Dlist **headR);

#endif