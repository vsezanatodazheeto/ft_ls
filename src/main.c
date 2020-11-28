/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:08:49 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/27 21:56:40 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int i = 0;

void				set_path(t_file *d_fl, char *path, char *old_path)
{
	*path = '\0';
	old_path ? ft_strcat(path, old_path) : ft_strcat(path, d_fl->name);
	// if (old_path)
	// {
	// 	ft_strcat(new_path, old_path);
	// 	// ft_strcat(new_path, "/");
	// }
	// else
	// {
	// 	ft_strcat(new_path, d_fl->name);
	// 	// ft_strcat(new_path, "/");
	// }
}

void				set_fullpath_tofile(char *fullpath, const char *path, \
										const char *fl_name)
{
	*fullpath = '\0';
	ft_strcat(fullpath, path);
	ft_strcat(fullpath, "/");
	ft_strcat(fullpath, fl_name);
}

void				form_new_fls(t_file *d_fl, char *old_path)
{
	DIR				*dir;
	struct dirent	*entry;
	t_file			*fls;
	t_file			*fls_copy;
	uint64_t		total;
	char			new_path[PATH_MAX];
	char			full_path[PATH_MAX + NAME_MAX];

	set_path(d_fl, new_path, old_path);
	fls = NULL;
	if (!ISFLAG(flag_a) && d_fl->name[0] == '.' && d_fl->name[1])
		return ;
	reset_stat_cells_len();
	dir = opendir(new_path);
	if (!dir)
		ERR_OPEND(new_path);
	total = 0;
	if (i)
		ft_printf("\n");
	if (d_fl->next || d_fl->prev)
		ft_printf("%s:\n", new_path);
	ft_strcat(new_path, "/");
	while ((entry = readdir(dir)))
	{
		file_add(&fls);
		if (!(fls->name = ft_strdup(entry->d_name)))
			ERR_STRDUP;
		set_fullpath_tofile(full_path, new_path, fls->name);
		if (lstat(full_path, &fls->stat) < 0)
			ERR_STATF(fls->name);
		else
		{
			if (ISFLAG(flag_a))
			{
				total += fls->stat.st_blocks;
				update_stat_cells_len(&fls->stat);
			}
			else if (fls->name[0] != '.')
			{
				total += fls->stat.st_blocks;
				update_stat_cells_len(&fls->stat);
			}
		}
	}
	merge_sort(&fls);
	format_output_print(fls, total, new_path);
	fls_copy = fls;
	if (ISFLAG(flag_R))
	{
		for (; fls; fls = fls->next)
			if (S_ISDIR(fls->stat.st_mode) && (ft_strcmp(fls->name, ".") != 0) && (ft_strcmp(fls->name, "..") != 0))
			{
				char gg_path[PATH_MAX + NAME_MAX];

				*gg_path = '\0';
				ft_strcat(gg_path, new_path);
				ft_strcat(gg_path, fls->name);
				ft_ls(fls, gg_path);
			}
	}
	file_list_free(&fls_copy);
	closedir(dir);
}

void		ft_ls(t_file *fls, char *path)
{
	if (!S_ISDIR(fls->stat.st_mode) && !ISFLAG(flag_R))
		format_file_print(fls, path);
	else
		form_new_fls(fls, path);
	// if (S_ISDIR(fls->stat.st_mode))
		// format_file_print(fls, fls->name);
}

void printFileProperties(struct stat stats);

int			main(int ac, char *av[])
{
	t_file	*fls;
	t_file	*fls_copy;

    fls = parse_args(ac, av);
	ftype_merge_sort(&fls);
	fls_copy = fls;
    while(fls)
    {
    	ft_ls(fls, NULL);
        fls = fls->next;
	}
	file_list_free(&fls_copy);
	return (0);
}
