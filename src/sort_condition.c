/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_condition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:06:30 by pcomic            #+#    #+#             */
/*   Updated: 2020/11/28 19:32:40 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			asc_sort(t_file *f1, t_file *f2)
{
	return (ft_strcmp(f2->name, f1->name));
}

int			desc_sort(t_file *f1, t_file *f2)
{
	return (ft_strcmp(f1->name, f2->name));
}

int			time_sort(t_file *f1, t_file *f2)
{
	return (difftime(f1->stat.st_mtime, f2->stat.st_mtime));
}

int			first_sort(t_file *f1, t_file *f2)
{
	if (!S_ISDIR(f1->stat.st_mode) && S_ISDIR(f2->stat.st_mode))
		return (1);
	else if ((S_ISDIR(f1->stat.st_mode) && S_ISDIR(f2->stat.st_mode)) \
			|| (!S_ISDIR(f1->stat.st_mode) && !S_ISDIR(f2->stat.st_mode)))
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
