/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:08:49 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/26 00:35:27 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int i = 0;

void				set_new_path(t_file *d_fl, char *new_path, char *old_path)
{
	*new_path = '\0';
	if (old_path)
	{
		ft_strcat(new_path, old_path);
		// ft_strcat(new_path, "/");
	}
	else
	{
		ft_strcat(new_path, d_fl->name);
		// ft_strcat(new_path, "/");
	}
}

void				print_dir_contains(t_file *d_fl, char *old_path)
{
	DIR				*dir;
	struct dirent	*entry;
	t_file			*fls;
	t_file			*fls_copy;
	uint64_t		total;
	char			new_path[PATH_MAX];
	char			full_path[PATH_MAX + NAME_MAX];

	set_new_path(d_fl, new_path, old_path);
	fls = NULL;
	if (!ISFLAG(fl_a) && d_fl->name[0] == '.' && d_fl->name[1])
		return ;
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
		{
			exit(1);
		}
		{
			full_path[0] = '\0';
			ft_strcat(full_path, new_path);
			ft_strcat(full_path, "/");
			ft_strcat(full_path, fls->name);
		}
		if (lstat(full_path, &fls->stat) < 0)
		{
			ERR_STATF(fls->name);
			fls->is_ex = fi_noex;
		}
		else
		{
			if (ISFLAG(fl_a))
			{
				total += fls->stat.st_blocks;
				set_format_attb(&fls->stat);

			}
			else if (fls->name[0] != '.')
			{
				total += fls->stat.st_blocks;
				set_format_attb(&fls->stat);
			}
		}
	}
	merge_Sort2(&fls);
	// if (i++)
	// 	ft_printf("\n");
	// if (d_fl->next || d_fl->prev)
	// 	ft_printf("%s:\n", new_path);
	format_output_print(fls, total);
	fls_copy = fls;
	if (ISFLAG(fl_R))
	{
		for (; fls; fls = fls->next)
			if (S_ISDIR(fls->stat.st_mode) && (ft_strcmp(fls->name, ".") != 0) && (ft_strcmp(fls->name, "..") != 0))
			{
				char gg_path[PATH_MAX + NAME_MAX];

				gg_path[0] = '\0';
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
	if (S_ISREG(fls->stat.st_mode) && !ISFLAG(fl_R))
		format_file_print(fls);
	if (S_ISDIR(fls->stat.st_mode))
		print_dir_contains(fls, path);
}

int			main(int ac, char *av[])
{
	t_file	*fls;
	t_file	*fls_copy;

    fls = parse_args(ac, av);
	merge_Sort2(&fls);
	fls_copy = fls;
    while(fls)
    {
    	ft_ls(fls, NULL);
        fls = fls->next;
	}
	file_list_free(&fls_copy);
	return (0);
}
