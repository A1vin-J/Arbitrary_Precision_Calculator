#include "apc.h"

int subtraction(Sign *s, Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR)
{
	// Check inputs are empty
	if(*head1 == NULL || *head2 == NULL) return FAILURE;

	// Reset result sign
    s->res_sign = 0;

    // Flip sign of second operand: A - B = A + (-B)
    s->sign2 ^= 1;

    int ret = addition(s, head1, tail1, head2, tail2, headR, tailR);

    // Restore original sign of operand 2
    s->sign2 ^= 1;

    return ret;
}