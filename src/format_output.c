/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:08:54 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/29 17:08:56 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern int32_t	g_printed;

static char		f_type(mode_t mode)
{
	mode_t		type;
	char		c;

	type = mode & S_IFMT;
	if (type == S_IFBLK)
		c = 'b';
	else if (type == S_IFCHR)
		c = 'c';
	else if (type == S_IFDIR)
		c = 'd';
	else if (type == S_IFIFO)
		c = 'p';
	else if (type == S_IFLNK)
		c = 'l';
	else if (type == S_IFREG)
		c = '-';
	else if (type == S_IFSOCK)
		c = 's';
	else
		c = '?';
	return (c);
}

static char		*f_permissions(mode_t mode)
{
	static char *rwx[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", \
							"rwx"};
	static char bits[11];

	bits[0] = f_type(mode);
	strcpy(&bits[1], rwx[(mode >> 6) & 7]);
	strcpy(&bits[4], rwx[(mode >> 3) & 7]);
	strcpy(&bits[7], rwx[(mode & 7)]);
	if (mode & S_ISUID)
		bits[3] = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
		bits[6] = (mode & S_IXGRP) ? 's' : 'l';
	if (mode & S_ISVTX)
		bits[9] = (mode & S_IXOTH) ? 't' : 'T';
	bits[10] = '\0';
	return (bits);
}

/*
** "awesome print time handling"
*/

static void		format_date_print(time_t mtime)
{
	int64_t		now_time;
	char		*str_date;

	now_time = time(NULL);
	if (!(str_date = ctime(&mtime)))
		return ;
	ft_printf("%.6s ", str_date + 4);
	if (now_time - mtime > SIX_MONTH)
		ft_printf("%*.4s ", get_stat_cell_len(fta_t), str_date + 20);
	else
		ft_printf("%*.5s ", get_stat_cell_len(fta_t), str_date + 11);
}

void			format_file_link_print(t_file *fls, const char *path)
{
	char		linked_f_name[PATH_MAX + NAME_MAX];
	char		full_path_tolink[PATH_MAX + NAME_MAX];

	ft_bzero(linked_f_name, PATH_MAX + NAME_MAX);
	ft_bzero(full_path_tolink, PATH_MAX + NAME_MAX);
	if (path)
		set_fullpath_tofile(full_path_tolink, path, fls->name);
	else
		ft_strcat(full_path_tolink, fls->name);
	if ((readlink(full_path_tolink, linked_f_name, PATH_MAX + NAME_MAX)) > 0)
		ft_printf(" -> %s", linked_f_name);
}

void			format_file_print(t_file *fls, const char *path)
{
	struct group	*grp;
	struct passwd	*pw;

	if (ISFLAG(flag_l))
	{
		ft_printf("%s  ", f_permissions(fls->stat.st_mode));
		ft_printf("%*d ", get_stat_cell_len(fta_l), fls->stat.st_nlink);
		if ((pw = getpwuid(fls->stat.st_uid)))
			ft_printf("%-*s  ", get_stat_cell_len(fta_u), pw->pw_name);
		else
			ft_printf("%-*d  ", get_stat_cell_len(fta_u), fls->stat.st_gid);
		if ((grp = getgrgid(fls->stat.st_gid)) != NULL)
			ft_printf("%-*s  ", get_stat_cell_len(fta_g), grp->gr_name);
		else
			ft_printf("%-*d ", get_stat_cell_len(fta_g), fls->stat.st_gid);
		ft_printf("%*d ", get_stat_cell_len(fta_s), fls->stat.st_size);
		format_date_print(fls->stat.st_mtime);
	}
	ft_printf("%s", fls->name);
	if (S_ISLNK(fls->stat.st_mode))
		format_file_link_print(fls, path);
	ft_printf("\n");
	g_printed++;
}
