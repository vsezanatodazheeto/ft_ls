/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_stat_cells_len.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:16:18 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/28 23:29:21 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			reset_stat_cells_len(void)
{
	t_cells_len	*len_stats;

	len_stats = update_stat_cells_len(NULL);
	ft_bzero(len_stats, sizeof(t_cells_len));
}

int32_t			get_stat_cell_len(t_flags_cells flag_cell)
{
	t_cells_len	*len_stats;

	len_stats = update_stat_cells_len(NULL);
	if (flag_cell == fta_l)
		return (len_stats->l_links);
	else if (flag_cell == fta_u)
		return (len_stats->l_user);
	else if (flag_cell == fta_g)
		return (len_stats->l_group);
	else if (flag_cell == fta_s)
		return (len_stats->l_size);
	else if (flag_cell == fta_t)
		return (len_stats->l_time);
	return (0);
}

static void		change_stat_cells_len(t_cells_len *main_len_stats, \
										t_cells_len *temp_len_stats)
{
	if (temp_len_stats->l_links > main_len_stats->l_links)
		main_len_stats->l_links = temp_len_stats->l_links;
	if (temp_len_stats->l_user > main_len_stats->l_user)
		main_len_stats->l_user = temp_len_stats->l_user;
	if (temp_len_stats->l_group > main_len_stats->l_group)
		main_len_stats->l_group = temp_len_stats->l_group;
	if (temp_len_stats->l_size > main_len_stats->l_size)
		main_len_stats->l_size = temp_len_stats->l_size;
	if (temp_len_stats->l_time > main_len_stats->l_time)
		main_len_stats->l_time = temp_len_stats->l_time;
}

static int32_t	get_stat_time_date_len(time_t mtime)
{
	int64_t		now_time;
	char		*str_date;

	now_time = time(NULL);
	if (!(str_date = ctime(&mtime)))
		return (0);
	if (now_time - mtime > SIX_MONTH)
		return (ft_strlen(str_date + 20));
	else
		return (4);
}

t_cells_len		*update_stat_cells_len(const struct stat *stats)
{
	static t_cells_len	main_len_stats = {0, 0, 0, 0, 0};
	t_cells_len			temp_len_stats;
	struct group		*grp;
	struct passwd		*pw;

	if (!stats)
		return (&main_len_stats);
	temp_len_stats.l_links = ft_numlen(stats->st_nlink, 10);
	if ((pw = getpwuid(stats->st_uid)))
		temp_len_stats.l_user = ft_strlen(pw->pw_name);
	else
		temp_len_stats.l_user = ft_numlen(stats->st_gid, 10);
	if ((grp = getgrgid(stats->st_gid)))
		temp_len_stats.l_group = ft_strlen(grp->gr_name);
	else
		temp_len_stats.l_group = ft_numlen(stats->st_gid, 10);
	temp_len_stats.l_size = ft_numlen(stats->st_size, 10);
	temp_len_stats.l_time = get_stat_time_date_len(stats->st_mtime);
	change_stat_cells_len(&main_len_stats, &temp_len_stats);
	return (&main_len_stats);
}
