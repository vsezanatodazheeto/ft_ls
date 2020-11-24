#include "ft_ls.h"

void				set_new_path(t_file *d_fl, char *new_path, char *old_path)
{
	*new_path = '\0';
	if (old_path)
	{
		ft_strcat(new_path, old_path);
		ft_strcat(new_path, "/");
	}
	else
	{
		ft_strcat(new_path, d_fl->name);
		ft_strcat(new_path, "/");
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
	// int				(*f_ptr)(t_file *, t_file *);

	set_new_path(d_fl, new_path, old_path);
	ft_printf("{green}%s:\n{eoc}", new_path);
	fls = NULL;
	dir = opendir(new_path);
	total = 0;

	if (!dir)
		ERR_OPD_NOEX;
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
			exit(200);
		else
		{
			if ((update_flags(-1) & 1 << fl_a))
				total += fls->stat.st_blocks;
			else if (fls->name[0] != '.')
				total += fls->stat.st_blocks;
			format_output_set(&fls->stat);
		}
	}
	fls = merge_Sort(fls);
	format_print_files(fls, total);
	fls_copy = fls;
	if (update_flags(-1) & 1 << fl_R)
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
	if (S_ISREG(fls->stat.st_mode) && !((update_flags(-1) & 1 << fl_R)))
		;
		// print_files(NULL);
	if (S_ISDIR(fls->stat.st_mode))
		print_dir_contains(fls, path);
}

int			main(int ac, char *av[])
{
	t_file	*fls;
	t_file	*fls_copy;

    fls = parse_args(ac, av);
	fls_copy = fls;
    while(fls)
    {
    	ft_ls(fls, NULL);
        fls = fls->next;
	}
	file_list_free(&fls_copy);
	return (0);
}
