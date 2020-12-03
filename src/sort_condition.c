/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_condition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:06:30 by pcomic            #+#    #+#             */
/*   Updated: 2020/12/03 23:30:34 by yshawn           ###   ########.fr       */
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
	int64_t	now_time;
	char	*str_date1;
	char	*str_date2;
	char	*x_date1;
	char	*x_date2;

	now_time = time(NULL);
	if (!(str_date1 = ctime(&(f1->stat.st_mtime))))
		return (0);
	if (!(str_date2 = ctime(&(f1->stat.st_mtime))))
		return (0);
	str_date1 = str_date1 + 4;
	str_date2 = str_date2 + 4;
	x_date1 = str_date1 + 16;
	x_date2 = str_date2 + 16;
	if ((ft_strcmp(str_date1, str_date2) == 0) \
		&& (ft_strcmp(x_date1, x_date2) == 0))
	{
		return (difftime(f1->stat.st_mtime, f2->stat.st_mtime));
	}
	else
		return (asc_sort(f1, f2));
}

int			time_sort_rev(t_file *f1, t_file *f2)
{
	int64_t	now_time;
	char	*str_date1;
	char	*str_date2;
	char	*x_date1;
	char	*x_date2;

	now_time = time(NULL);
	if (!(str_date1 = ctime(&(f1->stat.st_mtime))))
		return (0);
	if (!(str_date2 = ctime(&(f1->stat.st_mtime))))
		return (0);
	str_date1 = str_date1 + 4;
	str_date2 = str_date2 + 4;
	x_date1 = str_date1 + 16;
	x_date2 = str_date2 + 16;
	if ((ft_strcmp(str_date1, str_date2) == 0) \
		&& (ft_strcmp(x_date1, x_date2) == 0))
	{
		return (difftime(f2->stat.st_mtime, f1->stat.st_mtime));
	}
	else
		return (desc_sort(f1, f2));
}

int			first_sort(t_file *f1, t_file *f2)
{
	if (!S_ISDIR(f1->stat.st_mode) && S_ISDIR(f2->stat.st_mode))
		return (1);
	else if ((S_ISDIR(f1->stat.st_mode) && S_ISDIR(f2->stat.st_mode)) \
			|| (!S_ISDIR(f1->stat.st_mode) && !S_ISDIR(f2->stat.st_mode)))
	{
		if (ISFLAG(flag_r) && ISFLAG(flag_t))
			return (time_sort_rev(f1, f2));
		else if (ISFLAG(flag_r))
			return (desc_sort(f1, f2));
		else if (ISFLAG(flag_t))
			return (time_sort(f1, f2));
		else
			return (asc_sort(f1, f2));
	}
	return (0);
}
