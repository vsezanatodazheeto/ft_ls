/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:54:58 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/25 20:54:59 by yshawn           ###   ########.fr       */
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
	t_file		*fl;

	fl = (t_file *)malloc(sizeof(t_file));
	if (!fl)
		ERR_FCREATE;
	fl->name = NULL;
	fl->fe_err = fe_noer;
	fl->next = NULL;
	fl->prev = NULL;
	return (fl);
}

void			file_add(t_file **fls)
{
	t_file		*new_fl;

	new_fl = file_create();
	if (*fls)
	{
		(*fls)->prev = new_fl;
		new_fl->next = *fls;
	}
	*fls = new_fl;
}
