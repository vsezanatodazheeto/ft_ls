#include "ft_ls.h"

static int		asc_sort(t_file *f1, t_file *f2)
{
	return(ft_strcmp(f2->name, f1->name));
}

static int		desc_sort(t_file *f1, t_file *f2)
{
	return(ft_strcmp(f1->name, f2->name));
}

static int		time_sort(t_file *f1, t_file *f2)
{
	return(difftime(f1->stat.st_mtime, f2->stat.st_mtime));
}

static t_file  *merge(t_file* l1, t_file* l2, int	(*f_ptr)(t_file *, t_file *))
{
	t_file dummy[1];
	t_file* p = dummy;

	while (l1 && l2)
	{
		if (f_ptr(l1, l2) > 0)
		{
			p->next = l1;
			l1 = l1->next;
		}
		else {
			p->next = l2;
			l2 = l2->next;
		}

		p = p->next;
	}

	if (l1)
		p->next = l1;
	if (l2)
		p->next = l2;

	return dummy->next;
}

t_file* merge_Sort(t_file* head)
{


	int (*f_ptr)(t_file *, t_file *);

	if (update_flags(-1) & 1 << fl_r)
		f_ptr = desc_sort;
	else if (update_flags(-1) & 1 << fl_t)
		f_ptr = time_sort;
	else
		f_ptr = asc_sort;

	/* terminating condition */
	if (head == NULL || head->next == NULL)
		return head;


	t_file* slowPtr = head, *fastPtr = head, *prev = NULL;


	while (fastPtr != NULL && fastPtr->next != NULL)
	{
		prev = slowPtr;
		slowPtr = slowPtr->next;
		fastPtr  = fastPtr->next->next;
	}

	/* split the list int two half */
	prev->next = NULL;

	t_file* l1 = merge_Sort(head);
	t_file* l2 = merge_Sort(slowPtr);

	return merge(l1, l2, f_ptr);
}

	// Function to split nodes of the given doubly linked list into
// two halves using the fast/slow pointer strategy
void split(t_file *head, t_file **a, t_file **b)
{
    t_file *slow = head;
    t_file *fast = head->next;
 
    // Advance 'fast' by two nodes, and advance 'slow' by single node
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
 
    *b = slow->next;
    slow->next = NULL;
}
 
// Recursive function to merge nodes of two sorted lists together
// into a single sorted list
t_file	*merge2(t_file *a, t_file *b, int	(*f_ptr)(t_file *, t_file *))
{
    // Base cases
    if (a == NULL)
        return b;
 
    if (b == NULL)
        return a;
 
    // Pick either a or b, and recur
	if (f_ptr(a, b) > 0)
    {
        a->next = merge2(a->next, b, f_ptr);
        a->next->prev = a;
        a->prev = NULL;
        return a;
    }
    else
    {
        b->next = merge2(a, b->next, f_ptr);
        b->next->prev = b;
        b->prev = NULL;
        return b;
    }
}
 
// Function to sort a doubly linked list using merge sort algorithm
void merge_Sort2(t_file **head)
{
	int (*f_ptr)(t_file *, t_file *);

	if (update_flags(-1) & 1 << fl_r)
		f_ptr = desc_sort;
	else if (update_flags(-1) & 1 << fl_t)
		f_ptr = time_sort;
	else
		f_ptr = asc_sort;

    // base case: 0 or 1 node
    if (*head == NULL || (*head)->next == NULL)
        return;
	
    // split head into 'a' and 'b' sublists
    t_file *a = *head, *b = NULL;
    split(*head, &a, &b);
 
    // recursively sort the sub-lists
    merge_Sort2(&a);
    merge_Sort2(&b);
 
    // merge the two sorted lists together
    *head = merge2(a, b, f_ptr);
}
