#include "ft_ls.h"

int		asc_sort(t_file *f1, t_file *f2)
{
	return(ft_strcmp(f2->name, f1->name));
}

int		desc_sort(t_file *f1, t_file *f2)
{
	return(ft_strcmp(f1->name, f2->name));
}

t_file  *merge(t_file* l1, t_file* l2, int	(*f_ptr)(t_file *, t_file *))
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

t_file* merge_Sort(t_file* head, int (*f_ptr)(t_file *, t_file *))
{

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

	t_file* l1 = merge_Sort(head, f_ptr);
	t_file* l2 = merge_Sort(slowPtr, f_ptr);

	return merge(l1, l2, f_ptr);
}
