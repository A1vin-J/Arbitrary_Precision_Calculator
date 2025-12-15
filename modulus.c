#include "apc.h"

int modulus(Sign *s, Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR)
{
    // If divisor == 0 → FAIL
    if ((*head2)->data == 0 && (*head2)->next == NULL)
    {
        printf("Error: Modulus by zero\n");
        return FAILURE;
    }

    // Only num 1 is negative
    if(s->sign1 && !s->sign2) s->res_sign = 1;

    // If num 1 < num2 → result = num 1
    if (compare(*head1, *head2) < 0)
    {
        *headR = *head1;
        *tailR = *tail1;
        return SUCCESS;
    }

    // If num 1 == num2 → result = 0
    if (compare(*head1, *head2) == 0)
    {
        insert_at_last(headR, tailR, 0);
        return SUCCESS;
    }

    // Core function call
    if(div_core(head1, tail1, head2, tail2, headR, tailR, mod_mode, 0) == FAILURE) return FAILURE;

    return SUCCESS;
}