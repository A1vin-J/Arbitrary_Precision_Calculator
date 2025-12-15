#include"apc.h"

int add_core(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;

	int carry = 0, data = 0;

	while(temp1 || temp2)
	{
		// When there are digits in both numbers
		if(temp1 && temp2)
		{
			data = temp1->data + temp2->data + carry;
			carry = data / 10;
			data %= 10;

			if(insert_at_first(headR, tailR, data) == FAILURE) 
			{
				printf("temp1 && temp2 failed");
				return FAILURE;
			}

			temp1 = temp1->prev;
			temp2 = temp2->prev;
		}
		//When there are no more digits num2
		else if(temp1 && !temp2)
		{
			data = temp1->data + carry;
			carry = data / 10;
			data %= 10;

			if(insert_at_first(headR, tailR, data) == FAILURE)
			{
				printf("temp1 && temp2 == NULL failed");
				return FAILURE;
			}
			temp1 = temp1->prev;
		}
		//When there no are more digits in num1
		else
		{
			data = temp2->data + carry;
			carry = data / 10;
			data %= 10;

			if(insert_at_first(headR, tailR, data) == FAILURE)
			{
				printf("else failed");
				return FAILURE;
			}
			temp2 = temp2->prev;
		}
	}

	//If carry is present insert one node at the left-end
	if(carry)
	{
		if(insert_at_first(headR, tailR, carry) == FAILURE)
		{
			printf("carry failed");
			return FAILURE;
		}
	}

	return SUCCESS;
}


int sub_core(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR)
{
	Dlist *temp1, *temp2;

	//Comparing the inputs
	int cmp = compare(*head1, *head2);

	// If num1 == num2
	if (cmp == 0)
	{
		insert_at_first(headR, tailR, 0);
		return SUCCESS;
	}

	//If num1 < num2
	if (cmp < 0)
	{
		// Swap lists so it becomes larger number - smaller number
		temp1 = *tail2;
		temp2 = *tail1;
	}
	else
	{
		temp1 = *tail1;
		temp2 = *tail2;
	}

	int result = 0, data1 = 0, data2 = 0;

	while(temp1 || temp2)
	{
		data1 = temp1 ? temp1->data : 0;
		data2 = temp2 ? temp2->data : 0;

		if(data1 < data2)
		{
			// Borrowing from the left
			borrow(temp1);
			data1 += 10;
		}

		result = data1 - data2;

		// Inserting the result digit in list as node
		insert_at_first(headR, tailR, result);

		temp1 = temp1 ? temp1->prev : NULL;
		temp2 = temp2 ? temp2->prev : NULL;
	}

	// Deleting the leading zeros 
	if((*headR)->data == 0)
	delete_first(headR, tailR);

	return SUCCESS;
}


int mul_core(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR)
{    
	Dlist *temp1;
    Dlist *temp2 = *tail2;

    // Temporary Lists 
    Dlist *hr1 = NULL, *hr2 = NULL;
    Dlist *tr1 = NULL, *tr2 = NULL;

    insert_at_last(&hr2, &tr2, 0);

    int carry = 0, data = 0, zeros = 0;

    // Traverse through all the digits of num 2
    while(temp2)
    {
        temp1 = *tail1;

        // Zeros at the end of each multiplication result rows
        for(int i=0; i<zeros; i++)
            insert_at_first(&hr1, &tr1, 0);

        // Traverse through all the digits of num 1
        while(temp1)
        {
            data = (temp1->data * temp2->data ) + carry;
            carry = data / 10;
            data = data % 10;

            // Inserting multiplication results in nodes in the list
            if(insert_at_first(&hr1, &tr1, data) == FAILURE)
            {
                printf("Multiplication Failed!\n");
                return FAILURE;
            }
            
            temp1 = temp1->prev;
        }

        // Checking for carry 
        if(carry)
        {
            insert_at_first(&hr1, &tr1, carry);
            carry = 0;
        }

        // Adding multiplication results
        if(add_core(&hr1, &tr1, &hr2, &tr2, headR, tailR) == FAILURE) printf("Addition Failed!\n");

        // Free the list to store the addition result
        delete_list(&hr2, &tr2);

        // Update the list addressess
        hr2 = *headR;
        tr2 = *tailR;
        
        // Reset the result list
        *headR = NULL;
        *tailR = NULL;

        // Free the list to store the next multiplication result row
        delete_list(&hr1, &tr1);

        temp2 = temp2->prev;
        zeros++;
    }

    // Free the list to store the final result
    delete_list(headR, tailR);

    *headR = hr2;
    *tailR = tr2;

    while((*headR)->data == 0 && (*headR)->next != NULL)
    delete_first(headR, tailR);

    return SUCCESS;
}


int div_core(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR, Modes mode, int precision)
{
    // head1, tail1 -> Input number (dividend or num1)
    // head2, tail2 -> Input number (divisor or num2)
    // headR, tailR -> Final result list (quotient)

    // curH, curT -> Lists to store the current remainder
    Dlist *curH = NULL, *curT = NULL;

    // Temporary pointer to move Dividend
    Dlist *temp = *head1;

    // Build quotient left to right
    while (temp)
    {
        // Append next digit from dividend to current remainder
        insert_at_last(&curH, &curT, temp->data);

        // Remove leading zeros in current remainder
        while (curH && curH->data == 0 && curH->next)
            delete_first(&curH, &curT);

        // Initial q
        int q = 0;

        // Try q = 0 to 9
        for (int digit = 1; digit <= 9; digit++)
        {
            // Multiply divisor by digit

            // mh, mt -> List for Single digit multiplication
            // dummyR, dummyT -> Dummy lists used to store the multiplication results for comparison
            Dlist *mh = NULL, *mt = NULL;
            Dlist *dummyR = NULL, *dummyT = NULL;

            // Single digit (0 to 9)
            insert_at_last(&mh, &mt, digit);
            mul_core(head2, tail2, &mh, &mt, &dummyR, &dummyT);
            
            // Freeing for next use
            delete_list(&mh, &mt);

            // Compare divisor * digit vs current dividend digits
            if (compare(dummyR, curH) <= 0)
                q = digit;
            else
            {
                delete_list(&dummyR, &dummyT);
                break;
            }

            // Freeing for next use
            delete_list(&dummyR, &dummyT);
        }

        // Add q to the quotient
        insert_at_last(headR, tailR, q);

        // Now compute: cur = cur - divisor * q
        if (q > 0)
        {
            // multiply divisor * q
            Dlist *mh = NULL, *mt = NULL;

            // mulR, mulT -> List for storing the result of single digit multiplication
            Dlist *mulR = NULL, *mulT = NULL;

            insert_at_last(&mh, &mt, q);
            mul_core(head2, tail2, &mh, &mt, &mulR, &mulT);

            // Freeing for next use
            delete_list(&mh, &mt);

            // newH, newT -> List to store the new remainder
            Dlist *newH = NULL, *newT = NULL;

            // Subtract to get the new remainder (current remainder - divisor * q)
            sub_core(&curH, &curT, &mulR, &mulT, &newH, &newT);
            
            delete_list(&mulR, &mulT);
            delete_list(&curH, &curT);

            // Replace the current remainder with the new remainder
            curH = newH;
            curT = newT;
        }

        temp = temp->next;
    }

    if(precision)
    {
        // Add decimal '.' to the quotient
        insert_at_last(headR, tailR, '.');
        insert_at_last(&curH, &curT, 0);
        int count = 0;

        while(precision)
        {
            // Remove leading zeros in current remainder
            while (curH && curH->data == 0 && curH->next)
                delete_first(&curH, &curT);

            if(curH && curH->data == 0 && curH->next == NULL)
            {
                for(int i=0; i<precision; i++)
                insert_at_last(headR, tailR, 0);
                break;
            }

            // Initial q
            int q = 0;

            // Try q = 0 to 9
            for (int digit = 1; digit <= 9; digit++)
            {
                // Multiply divisor by digit

                // mh, mt -> List for Single digit multiplication
                // dummyR, dummyT -> Dummy lists used to store the multiplication results for comparison
                Dlist *mh = NULL, *mt = NULL;
                Dlist *dummyR = NULL, *dummyT = NULL;

                // Single digit (0 to 9)
                insert_at_last(&mh, &mt, digit);
                mul_core(head2, tail2, &mh, &mt, &dummyR, &dummyT);
                
                // Freeing for next use
                delete_list(&mh, &mt);

                // Compare divisor * q vs current dividend digits
                if (compare(dummyR, curH) <= 0)
                    q = digit;
                else
                {
                    delete_list(&dummyR, &dummyT);
                    break;
                }

                // Freeing for next use
                delete_list(&dummyR, &dummyT);
            }

            // Now compute: cur = cur - divisor * q
            if (q > 0)
            {
                // Add q to the quotient
                insert_at_last(headR, tailR, q);
                
                // multiply divisor * q
                Dlist *mh = NULL, *mt = NULL;

                // mulR, mulT -> List for storing the result of single digit multiplication
                Dlist *mulR = NULL, *mulT = NULL;

                insert_at_last(&mh, &mt, q);
                mul_core(head2, tail2, &mh, &mt, &mulR, &mulT);

                // Freeing for next use
                delete_list(&mh, &mt);

                // newH, newT -> List to store the new remainder
                Dlist *newH = NULL, *newT = NULL;

                // Subtract to get the new remainder (current remainder - divisor * q)
                sub_core(&curH, &curT, &mulR, &mulT, &newH, &newT);
                
                delete_list(&mulR, &mulT);
                delete_list(&curH, &curT);

                // Replace the current remainder with the new remainder
                curH = newH;
                curT = newT;
                count = 0;
            }
            else if(q == 0 && count == 0 && (*tailR)->data != '.')
            {
                insert_at_last(&curH, &curT, 0);
                count++;
                precision++;
            }
            else
            {
                insert_at_last(headR, tailR, q);
                count = 0;
            }
            precision--;
        }
    }

    // If called by modulus -> result = remainder
    if(mode == mod_mode)
    {
        delete_list(headR, tailR);

        *headR = curH;
        *tailR = curT;
    }
    else delete_list(&curH, &curT);

    // Remove leading zeros from quotient
    while (*headR && (*headR)->data == 0 && (*headR)->next && (*headR)->next->data != '.')
    delete_first(headR, tailR);

    return SUCCESS;
}