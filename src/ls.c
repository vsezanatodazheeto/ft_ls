/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:08:49 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/29 16:23:11 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int32_t		g_printed = 0;

static void	set_path(t_file *d_fl, char *path, char *old_path)
{
	*path = '\0';
	old_path ? ft_strcat(path, old_path) : ft_strcat(path, d_fl->name);
}

void		set_fullpath_tofile(char *fullpath, const char *path, \
										const char *fl_name)
{
	ft_strcat(fullpath, path);
	ft_strcat(fullpath, fl_name);
}

static void	ls_recursion(t_file *fls, const char *path)
{
	char new_path[PATH_MAX + NAME_MAX];

	while (fls)
	{
		if (S_ISDIR(fls->stat.st_mode) \
			&& (ft_strcmp(fls->name, D_CURR) != 0) \
			&& (ft_strcmp(fls->name, D_PREV) != 0))
		{
			*new_path = '\0';
			ft_strcat(new_path, path);
			ft_strcat(new_path, fls->name);
			ls_base(fls, new_path);
		}
		fls = fls->next;
	}
}

static void	ls_form_new_fls(DIR *dir, t_file **fls, const char *path, \
									uint64_t *total)
{
	struct dirent	*entry;
	struct stat		stat_temp;
	char			full_path[PATH_MAX + NAME_MAX];

	while ((entry = readdir(dir)))
	{
		ft_bzero(&stat_temp, sizeof(struct stat));
		ft_bzero(full_path, PATH_MAX + NAME_MAX);
		set_fullpath_tofile(full_path, path, entry->d_name);
		if (lstat(full_path, &stat_temp) < 0)
			ERR_STATF(entry->d_name);
		else
		{
			file_add(fls);
			ft_memcpy(&(*fls)->stat, &stat_temp, sizeof(struct stat));
			if (!((*fls)->name = ft_strdup(entry->d_name)))
				ERR_STRDUP;
			if (ISFLAG(flag_a) || (!ISFLAG(flag_a) && (*fls)->name[0] != '.'))
			{
				*total += (*fls)->stat.st_blocks;
				update_stat_cells_len(&(*fls)->stat);
			}
		}
	}
}

void		ls(t_file *d_fl, char *old_path)
{
	DIR			*dir;
	t_file		*fls;
	uint64_t	total;
	char		new_path[PATH_MAX];

	set_path(d_fl, new_path, old_path);
	fls = NULL;
	total = 0;
	if (!ISFLAG(flag_a) && d_fl->name[0] == '.' && d_fl->name[1])
		return ;
	reset_stat_cells_len();
	if (!(dir = opendir(new_path)))
		ERR_OPEND(new_path);
	if (g_printed)
		ft_printf("\n");
	if (d_fl->next || d_fl->prev)
		ft_printf("%s:\n", new_path);
	ft_strcat(new_path, "/");
	ls_form_new_fls(dir, &fls, new_path, &total);
	closedir(dir);
	merge_sort(&fls);
	format_output_print(fls, total, new_path);
	if (ISFLAG(flag_R))
		ls_recursion(fls, new_path);
	file_list_free(&fls);
}
