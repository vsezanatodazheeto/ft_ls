/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:06:30 by pcomic            #+#    #+#             */
/*   Updated: 2020/11/27 17:58:23 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			asc_sort(t_file *f1, t_file *f2)
{
	return (ft_strcmp(f2->name, f1->name));
}

static int			desc_sort(t_file *f1, t_file *f2)
{
	return (ft_strcmp(f1->name, f2->name));
}

static int			time_sort(t_file *f1, t_file *f2)
{
	return (difftime(f1->stat.st_mtime, f2->stat.st_mtime));
}

void				split(t_file *head, t_file **a, t_file **b)
{
	t_file *slow;
	t_file *fast;

	slow = head;
	fast = head->next;
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

static t_file		*merge2(t_file *a, t_file *b,
							int (*f_ptr)(t_file *, t_file *))
{
	if (a == NULL)
		return (b);
	if (b == NULL)
		return (a);
	if (f_ptr(a, b) > 0)
	{
		a->next = merge2(a->next, b, f_ptr);
		a->next->prev = a;
		a->prev = NULL;
		return (a);
	}
	else
	{
		b->next = merge2(a, b->next, f_ptr);
		b->next->prev = b;
		b->prev = NULL;
		return (b);
	}
}

void				merge_sort2(t_file **head)
{
	int		(*f_ptr)(t_file *, t_file *);
	t_file	*a;
	t_file	*b;

	if (ISFLAG(flag_r))
		f_ptr = desc_sort;
	else if (ISFLAG(flag_t))
		f_ptr = time_sort;
	else
		f_ptr = asc_sort;
	if (*head == NULL || (*head)->next == NULL)
		return ;
	a = *head;
	b = NULL;
	split(*head, &a, &b);
	merge_sort2(&a);
	merge_sort2(&b);
	*head = merge2(a, b, f_ptr);
}
