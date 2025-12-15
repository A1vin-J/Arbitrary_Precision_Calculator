#include "apc.h"

int multiplication(Sign *s, Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR)
{
    // Check inputs are empty
    if (*head1 == NULL || *head2 == NULL) return FAILURE;

    // Only any 1 num is neg
    if(s->sign1 ^ s->sign2) s->res_sign = 1;
    
    // Core function call
    if(mul_core(head1, tail1, head2, tail2, headR, tailR) == FAILURE) return FAILURE;

    return SUCCESS;
}