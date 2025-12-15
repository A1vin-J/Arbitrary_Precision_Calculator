#include "apc.h"

void digit_to_list(Sign *s, Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,char *argv[])
{
    int data = 0, i=0;

    // Checking for negative sign "-" in num1
    if(argv[1][0] == '-')
    {
        s->sign1 = 1;
        i = 1;
    }

    //Traversing till '\0' character of 1st number string
    while(argv[1][i] != '\0')
    {
        data = (argv[1][i]) - '0';

        if(i == 0 && argv[1][i+1] != '\0' && data == 0)
        {
            while(argv[1][i] != '\0' && data == 0)
            {
                data = (argv[1][i]) - '0';
                i++;
            }
            i--;
        }
        insert_at_last(head1, tail1, data);
        i++;
    }

    i=0;

    // Checking for negative sign "-" in num2
    if(argv[3][0] == '-')
    {
        s->sign2 = 1;
        i = 1;
    }

    //Traversing till '\0' character of 2nd number string
    while(argv[3][i] != '\0')
    {
        data = (argv[3][i]) - '0';
        if(i == 0 && argv[3][i+1] != '\0' && data == 0)
        {
            while(argv[3][i] != '\0' && data == 0)
            {
                data = (argv[3][i]) - '0';
                i++;
            }
            i--;
        }
        insert_at_last(head2, tail2, data);
        i++;
    }
}


int insert_at_first(Dlist **head, Dlist **tail, int data)
{
    //DMA
    Dlist *new = malloc(sizeof(Dlist));

    //Checking node is created or not
    if(new == NULL) return FAILURE;         
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    
    Dlist *temp = *head;

    //Checking the list is empty or not
    if(*head == NULL)                       
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    else
    {
        new->next = *head;
        *head = new;
        temp->prev = new;
        return SUCCESS;
    }

    return FAILURE;
}


int insert_at_last(Dlist **head, Dlist **tail, int data)
{
    //DMA
    Dlist *new = malloc(sizeof(Dlist));         
    
    //Checking node is created or not
    if(new == NULL) return FAILURE;             
    new->data = data;
    new->next = NULL;
    
    //Checking the list is empty or not
    if(*head == NULL && *tail == NULL)          
    {
        new->prev = NULL;
        *head = new;
        *tail = new;
    }
    else 
    {
        new->prev = *tail;
        (*tail)->next = new;
        *tail = new;
    }
    return SUCCESS;
}

int delete_first(Dlist **head, Dlist **tail)
{
    // Checking the list is empty or not
    if(*head == NULL) return FAILURE;
    
    Dlist *temp = *head;

    // Check whether only 1 node is present
    if(*head == *tail)
    {
        *head = NULL;
        *tail = NULL;
        free(temp);
        return SUCCESS;
    }
    else
    {
        *head = temp->next;
        (*head)->prev = NULL;
        free(temp);
    }
    
    return SUCCESS;
}


void print_list(Dlist *head)
{
    //Checking the list is empty or not
	if (head == NULL)                       
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    while (head)		
	    {
            if(head->data == '.') printf("%c", head->data);
            else printf("%d", head -> data);

		    head = head -> next;
	    }
    }
}


int compare(Dlist *head1, Dlist *head2)
{
    int len1 = 0, len2 = 0;
    Dlist *t1 = head1, *t2 = head2;

    //Length of list 1
    while(t1)
    {
        len1++;
        t1 = t1->next;
    }

    //Length of list 2
    while(t2)
    {
        len2++;
        t2 = t2->next;
    }

    // Compare lengths
    if(len1 > len2) return 1;
    if(len1 < len2) return -1;

    //If lengths are equal, then compare the digits
    t1 = head1;
    t2 = head2;

    //Comparing the digits
    while(t1 && t2)
    {
        if (t1->data > t2->data) return 1;
        if (t1->data < t2->data) return -1;

        t1 = t1->next;
        t2 = t2->next;
    }

    // Both numbers are equal
    return 0;
}


void borrow(Dlist *node)
{
    Dlist *p = node->prev;

    while (p && p->data == 0)
    {
        p = p->prev;
    }

    // Found a digit to borrow from
    p->data -= 1;

    // Fill zeros with 9 while going forward
    p = p->next;
    while (p != node)
    {
        p->data = 9;
        p = p->next;
    }
}


int delete_list(Dlist **head, Dlist **tail)
{
    // Cheking the list is empty or not
    if(*head == NULL) return FAILURE;
    
    Dlist *temp = *head;
    
    // Traverse upto last node
    while(temp != NULL)
    {
        *head = temp->next;
        free(temp);
        temp = *head;
    }
    
    *head = NULL;
    *tail = NULL;
    
    return SUCCESS;
}


void print_result(Sign *s, Dlist **headR)
{
    int zero = 0;
    if((*headR)->data == 0 && (*headR)->next == NULL) zero = 1;
    if(s->res_sign && !zero) printf("-");
    print_list(*headR);
    printf("\n");
}


void print_inputs(char *argv[])
{
    printf("Input\t: ");
	printf("%s %s %s", argv[1], argv[2], argv[3]);
	printf("\n");
}