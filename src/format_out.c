/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:08:54 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/26 00:34:59 by yshawn           ###   ########.fr       */
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

void			format_file_print(t_file *fls)
{
	struct group	*grp;
	struct passwd	*pw;

	if (ISFLAG(fl_l))
	{
		ft_printf("%s  ", f_permissions(fls->stat.st_mode));
		ft_printf("%*d ", get_row_stat_len(fta_l), fls->stat.st_nlink);
		if ((pw = getpwuid(fls->stat.st_uid)))
			ft_printf("%*s  ", get_row_stat_len(fta_u), pw->pw_name);
		else
			ft_printf("%*d ", get_row_stat_len(fta_u), fls->stat.st_gid);
		if ((grp = getgrgid(fls->stat.st_gid)) != NULL)
			ft_printf("%*s  ", get_row_stat_len(fta_g), grp->gr_name);
		else
			ft_printf("%*d ", get_row_stat_len(fta_g), fls->stat.st_gid);
		ft_printf("%*d ", get_row_stat_len(fta_s), fls->stat.st_size);
		ft_printf("%.12s ", ctime(&fls->stat.st_mtime) + 4);
	}
	ft_printf("%s\n", fls->name);
	i++;
}

void			format_output_print(t_file *fls, uint64_t total)
{
	if (ISFLAG(fl_l))
		ft_printf("total %u\n", total);
	while (fls)
	{
		if (ISFLAG(fl_a))
			format_file_print(fls);
		else if ((*fls->name != CH_DOT))
			format_file_print(fls);
		fls = fls->next;
	}
}
