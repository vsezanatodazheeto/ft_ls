/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:06:30 by pcomic            #+#    #+#             */
/*   Updated: 2020/11/27 18:57:10 by yshawn           ###   ########.fr       */
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

static int			first_sort(t_file *f1, t_file *f2)
{
	if (!S_ISDIR(f1->stat.st_mode) && S_ISDIR(f2->stat.st_mode))
		return (1);
	else if ( ( S_ISDIR(f1->stat.st_mode) && S_ISDIR(f2->stat.st_mode) ) || ( !S_ISDIR(f1->stat.st_mode) && !S_ISDIR(f2->stat.st_mode)) )
	{
		if (ISFLAG(flag_r))
			return (desc_sort(f1, f2));
		else if (ISFLAG(flag_t))
			return (time_sort(f1, f2));
		else
			return (asc_sort(f1, f2));
	}
	return (0);
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

static t_file		*merge(t_file *a, t_file *b,
							int (*f_ptr)(t_file *, t_file *))
{
	if (a == NULL)
		return (b);
	if (b == NULL)
		return (a);
	if (f_ptr(a, b) > 0)
	{
		a->next = merge(a->next, b, f_ptr);
		a->next->prev = a;
		a->prev = NULL;
		return (a);
	}
	else
	{
		b->next = merge(a, b->next, f_ptr);
		b->next->prev = b;
		b->prev = NULL;
		return (b);
	}
}

void				merge_sort(t_file **head)
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
	merge_sort(&a);
	merge_sort(&b);
	*head = merge(a, b, f_ptr);
}

void				ftype_merge_sort(t_file **head)
{
	int		(*f_ptr)(t_file *, t_file *);
	t_file	*a;
	t_file	*b;

	f_ptr = first_sort;
	if (*head == NULL || (*head)->next == NULL)
		return ;
	a = *head;
	b = NULL;
	split(*head, &a, &b);
	ftype_merge_sort(&a);
	ftype_merge_sort(&b);
	*head = merge(a, b, f_ptr);
}
