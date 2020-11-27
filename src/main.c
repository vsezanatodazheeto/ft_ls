/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:08:49 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/27 18:08:56 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int i = 0;

void				set_newpath(t_file *d_fl, char *new_path, char *old_path)
{
	*new_path = '\0';
	old_path ? ft_strcat(new_path, old_path) : ft_strcat(new_path, d_fl->name);
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

void				set_fullpath_tofile(char *fullpath, const char *newpath, const char *name)
{
	*fullpath = '\0';
	ft_strcat(fullpath, newpath);
	ft_strcat(fullpath, "/");
	ft_strcat(fullpath, name);
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

	set_newpath(d_fl, new_path, old_path);
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
		{
			exit(1);
		}
		{
			set_fullpath_tofile(full_path, new_path, fls->name);
		}
		if (lstat(full_path, &fls->stat) < 0)
		{
			ERR_STATF(fls->name);
			fls->is_ex = fi_noex;
		}
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
	merge_sort2(&fls);
	// if (i++)
	// 	ft_printf("\n");
	// if (d_fl->next || d_fl->prev)
	// 	ft_printf("%s:\n", new_path);
	format_output_print(fls, total);
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
	if (S_ISREG(fls->stat.st_mode) && !ISFLAG(flag_R))
		format_file_print(fls);
	if (S_ISDIR(fls->stat.st_mode))
		form_new_fls(fls, path);
}

void printFileProperties(struct stat stats);

int			main(int ac, char *av[])
{
	t_file	*fls;
	t_file	*fls_copy;

    fls = parse_args(ac, av);
	// merge_Sort2(&fls);
	fls_copy = fls;
    while(fls)
    {
    	ft_ls(fls, NULL);
        fls = fls->next;
	}
	file_list_free(&fls_copy);




// 	DIR				*dir;
// 	struct dirent	*entry;
// 	t_file			*fls;
// 	struct group	*grp;
// 	struct passwd	*pw;

// 	dir = opendir(".");
// 	while ((entry = readdir(dir)))
// 	{
// 		struct stat alal;
// 		ft_printf("%s\n", entry->d_name);
// 		lstat(entry->d_name, &alal);
// 		if (S_ISLNK(alal.st_mode))
// 		{
// 			DIR		*dir_cp;

// 			ft_printf("{green}is_link{eoc}\n");
// 			struct dirent	*entry;
// 			// dir_cp =
// 			// getxattr()


// 		}
// 		else if (S_ISREG(alal.st_mode))
// 			ft_printf("{green}is_reg{eoc}\n");
// 		printFileProperties(alal);
// 		ft_printf("{red}-------------------{eoc}\n");
// 	}
// 	ft_printf("\n");

	return (0);
}

// /**
//  * Function to print file properties.
//  */
// void printFileProperties(struct stat stats)
// {
//     struct tm dt;

//     // File permissions
//     printf("\nFile access: ");
//     if (stats.st_mode & R_OK)
//         printf("read ");
//     if (stats.st_mode & W_OK)
//         printf("write ");
//     if (stats.st_mode & X_OK)
//         printf("execute");

//     // File size
//     printf("\nFile size: %lld", stats.st_size);

//     // Get file creation time in seconds and 
//     // convert seconds to date and time format
//     dt = *(gmtime(&stats.st_ctime));
//     printf("\nCreated on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
//                                               dt.tm_hour, dt.tm_min, dt.tm_sec);

//     // File modification time
//     dt = *(gmtime(&stats.st_mtime));
//     printf("\nModified on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
//                                               dt.tm_hour, dt.tm_min, dt.tm_sec);

// }
