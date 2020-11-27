/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_rows_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:16:31 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/27 17:42:07 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			reset_stat_cells_len(void)
{
	t_format_out	*len_stats;

	len_stats = update_stat_cells_len(NULL);
	// len_stats->s_links = 0;
	// len_stats->s_user = 0;
	// &len_stats->s_group = 0;
	// &len_stats->s_size = 0;
	ft_bzero(len_stats, sizeof(t_format_out));
}

int32_t			get_stat_cell_len(t_format_type_attb attb)
{
	t_format_out	*len_stats;

	len_stats = update_stat_cells_len(NULL);
	if (attb == fta_l)
		return (len_stats->s_links);
	else if (attb == fta_u)
		return (len_stats->s_user);
	else if (attb == fta_g)
		return (len_stats->s_group);
	else if (attb == fta_s)
		return (len_stats->s_size);
	return (0);
}

static void		change_stat_cells_len(t_format_out *main_len_stats, \
										t_format_out *temp_len_stats)
{
	if (temp_len_stats->s_links > main_len_stats->s_links)
		main_len_stats->s_links = temp_len_stats->s_links;
	if (temp_len_stats->s_user > main_len_stats->s_user)
		main_len_stats->s_user = temp_len_stats->s_user;
	if (temp_len_stats->s_group > main_len_stats->s_group)
		main_len_stats->s_group = temp_len_stats->s_group;
	if (temp_len_stats->s_size > main_len_stats->s_size)
		main_len_stats->s_size = temp_len_stats->s_size;
}

t_format_out	*update_stat_cells_len(const struct stat *stats)
{
	static t_format_out	main_len_stats = {0, 0, 0, 0};
	t_format_out		temp_len_stats;
	struct group		*grp;
	struct passwd		*pw;

	if (!stats)
		return (&main_len_stats);
	temp_len_stats.s_links = ft_numlen(stats->st_nlink, 10);
	if ((pw = getpwuid(stats->st_uid)))
		temp_len_stats.s_user = ft_strlen(pw->pw_name);
	else
		temp_len_stats.s_user = ft_numlen(stats->st_gid, 10);
	if ((grp = getgrgid(stats->st_gid)))
		temp_len_stats.s_group = ft_strlen(grp->gr_name);
	else
		temp_len_stats.s_group = ft_numlen(stats->st_gid, 10);
	temp_len_stats.s_size = ft_numlen(stats->st_size, 10);
	change_stat_cells_len(&main_len_stats, &temp_len_stats);
	return (&main_len_stats);
}
