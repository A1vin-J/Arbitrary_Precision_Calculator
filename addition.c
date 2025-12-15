#include "apc.h"

int addition(Sign *s, Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{

	// Check inputs are empty
	if(*head1 == NULL || *head2 == NULL) return FAILURE;

	s->res_sign = 0;

	// Both num 1 & num 2 are positive
    if (!s->sign1 && !s->sign2)
    {
        add_core(head1, tail1, head2, tail2, headR, tailR);
        return SUCCESS;
    }

	// Both num 1 & num 2 are negative
    if (s->sign1 && s->sign2)
    {
        s->res_sign = 1;
        add_core(head1, tail1, head2, tail2, headR, tailR);
        return SUCCESS;
    }

    // +A + -B OR -A + +B → subtraction
    int cmp = compare(*head1, *head2);

    if (cmp == 0)
    {
        insert_at_first(headR, tailR, 0);
        return SUCCESS;
    }

	// num 2 is negative
    if (!s->sign1 && s->sign2)
    {
        // num 1 > num 2
        if (cmp > 0)
            sub_core(head1, tail1, head2, tail2, headR, tailR);
		
		// num 1 < num 2
        else
        {
            s->res_sign = 1;
            sub_core(head2, tail2, head1, tail1, headR, tailR);
        }
    }
	// Num 1 is negative
    else
    {
        // num 1 > num 2
        if (cmp < 0)
            sub_core(head2, tail2, head1, tail1, headR, tailR);

		// num 1 < num 2
        else
        {
            s->res_sign = 1;
            sub_core(head1, tail1, head2, tail2, headR, tailR);
        }
    }

    return SUCCESS;
}