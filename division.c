#include "apc.h"

int division(Sign *s, Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR, int precision)
{
    // head1, tail1 -> Input number (dividend or num1)
    // head2, tail2 -> Input number (divisor or num2)
    // headR, tailR -> Final result list (quotient)
    
	// Check inputs are empty
    if (*head1 == NULL || *head2 == NULL) return FAILURE;

    // Only any 1 num is neg
    if(s->sign1 ^ s->sign2) s->res_sign = 1;

    // If divisor == 0 → FAIL
    if ((*head2)->data == 0 && (*head2)->next == NULL)
    {
        printf("Error: Division by zero\n");
        return FAILURE;
    }

    // If dividend < divisor → quotient = 0
    if (precision == 0 && compare(*head1, *head2) < 0)
    {
        insert_at_last(headR, tailR, 0);
        return SUCCESS;
    }

    // If dividend == divisor → quotient = 1
    if (compare(*head1, *head2) == 0)
    {
        insert_at_last(headR, tailR, 1);
        return SUCCESS;
    }

    // Core function call
    if(div_core(head1, tail1, head2, tail2, headR, tailR, div_mode, precision) == FAILURE) return FAILURE;

    return SUCCESS;
}