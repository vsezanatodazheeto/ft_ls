/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:54:58 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/27 18:13:26 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			file_list_free(t_file **head)
{
	t_file		*curr;

	if (!head)
		return ;
	while (*head)
	{
		curr = *head;
		*head = (*head)->next;
		free(curr->name);
		free(curr);
		curr = NULL;
	}
}

static t_file	*file_create(void)
{
	t_file		*f;

	f = (t_file *)malloc(sizeof(t_file));
	if (!f)
		ERR_FCREATE;
	f->name = NULL;
	f->next = NULL;
	f->prev = NULL;
	return (f);
}

void			file_add(t_file **fls)
{
	t_file		*f;

	f = file_create();
	if (*fls)
	{
		(*fls)->prev = f;
		f->next = *fls;
	}
	*fls = f;
}
