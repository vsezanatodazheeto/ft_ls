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

static int32_t		get_format_attb(t_format_type_attb attb)
{
	t_format_out	*f_out;

	f_out = set_format_attb(NULL);
	if (attb == fta_l)
		return (f_out->s_links);
	else if (attb == fta_u)
		return (f_out->s_user);
	else if (attb == fta_g)
		return (f_out->s_group);
	else if (attb == fta_s)
		return (f_out->s_size);
	return (0);
}

t_format_out	*set_format_attb(const struct stat *stat)
{
	static t_format_out	f_out = {0, 0, 0, 0};
	t_format_out		temp;
	struct group		*grp;
	struct passwd		*pw;

	ft_bzero(&temp, sizeof(t_format_out));
	if (!stat)
		return (&f_out);
	temp.s_links = ft_numlen(stat->st_nlink, 10);
	if ((pw = getpwuid(stat->st_uid)))
		temp.s_user = ft_strlen(pw->pw_name);
	if ((grp = getgrgid(stat->st_gid)))
		temp.s_group = ft_strlen(grp->gr_name);
	temp.s_size = ft_numlen(stat->st_size, 10);
	if (temp.s_links > f_out.s_links)
		f_out.s_links = temp.s_links;
	if (temp.s_user > f_out.s_user)
		f_out.s_user = temp.s_user;
	if (temp.s_group > f_out.s_group)
		f_out.s_group = temp.s_group;
	if (temp.s_size > f_out.s_size)
		f_out.s_size = temp.s_size;
	return (&f_out);
}

static char		f_type(mode_t mode)
{
	char		c;
	mode_t		type;

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
		ft_printf("%*d ", get_format_attb(fta_l), fls->stat.st_nlink);
		if ((pw = getpwuid(fls->stat.st_uid)))
			ft_printf("%*s  ", get_format_attb(fta_u), pw->pw_name);
		else
			ft_printf("%*d ", get_format_attb(fta_u), fls->stat.st_gid);
		if ((grp = getgrgid(fls->stat.st_gid)) != NULL)
			ft_printf("%*s  ", get_format_attb(fta_g), grp->gr_name);
		else
			ft_printf("%*d ", get_format_attb(fta_g), fls->stat.st_gid);
		ft_printf("%*d ", get_format_attb(fta_s), fls->stat.st_size);
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
		else if ((fls->name[0] != CH_DOT))
			format_file_print(fls);
		fls = fls->next;
	}
}
