/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:08:54 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/27 21:59:21 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern int i;

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
** awesome print time handling
*/

void			format_file_print(t_file *fls, const char *path)
{
	struct group	*grp;
	struct passwd	*pw;

	if (ISFLAG(flag_l))
	{
		ft_printf("%s  ", f_permissions(fls->stat.st_mode));
		ft_printf("%*d ", get_stat_cell_len(fta_l), fls->stat.st_nlink);
		if ((pw = getpwuid(fls->stat.st_uid)))
			ft_printf("%*s  ", get_stat_cell_len(fta_u), pw->pw_name);
		else
			ft_printf("%*d  ", get_stat_cell_len(fta_u), fls->stat.st_gid);
		if ((grp = getgrgid(fls->stat.st_gid)) != NULL)
			ft_printf("%*s  ", get_stat_cell_len(fta_g), grp->gr_name);
		else
			ft_printf("%*d ", get_stat_cell_len(fta_g), fls->stat.st_gid);
		ft_printf("%*d ", get_stat_cell_len(fta_s), fls->stat.st_size);
		ft_printf("%.12s ", ctime(&fls->stat.st_mtime) + 4);
	}
	ft_printf("%s", fls->name);
	if (S_ISLNK(fls->stat.st_mode))
	{
		char kek[PATH_MAX];
		char full[PATH_MAX];
		ft_bzero(full, PATH_MAX);
		ft_bzero(kek, PATH_MAX);
		set_fullpath_tofile(full, path, fls->name);
		readlink(full, kek, PATH_MAX);
		ft_printf(" -> %s", kek);
	}
	ft_printf("\n");

	i++;
}

void			format_output_print(t_file *fls, uint64_t total, const char *path)
{
	if (ISFLAG(flag_l))
		ft_printf("total %u\n", total);
	while (fls)
	{
		if (ISFLAG(flag_a))
			format_file_print(fls, path);
		else if ((*fls->name != CH_DOT))
			format_file_print(fls, path);
		fls = fls->next;
	}
}
