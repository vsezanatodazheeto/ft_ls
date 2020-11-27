#include "ft_ls.h"

extern int i;

int32_t			get_row_stat_len(t_format_type_attb attb)
{
	t_format_out	*len_stats;

	len_stats = update_row_stats_len(NULL);
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

static void		change_row_stats_len(t_format_out *main_len_stats, t_format_out *temp_len_stats)
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

t_format_out	*update_row_stats_len(const struct stat *stat)
{
	static t_format_out	main_len_stats = {0, 0, 0, 0};
	t_format_out		temp_len_stats;
	struct group		*grp;
	struct passwd		*pw;

	// ft_bzero(&temp_len_stats, sizeof(t_format_out)); // это больше не нужно
	if (!stat)
		return (&main_len_stats);
	temp_len_stats.s_links = ft_numlen(stat->st_nlink, 10);
	if ((pw = getpwuid(stat->st_uid)))
		temp_len_stats.s_user = ft_strlen(pw->pw_name);
	else
		temp_len_stats.s_user = ft_numlen(stat->st_gid, 10);
	if ((grp = getgrgid(stat->st_gid)))
		temp_len_stats.s_group = ft_strlen(grp->gr_name);
	else
		temp_len_stats.s_user = ft_numlen(stat->st_gid, 10);
	temp_len_stats.s_size = ft_numlen(stat->st_size, 10);
	change_row_stats_len(&temp_len_stats, &main_len_stats);
	return (&main_len_stats);
}
