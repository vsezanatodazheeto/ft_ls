#include "ft_ls.h"

void        print_files(void)
{
    printf("PRINT FILES\n");
}

void		print_files_a(t_file *fls)
{
	for (; fls; fls = fls->next)
		ft_printf("%s\n", fls->name);
}

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
	char			new_path[PATH_MAX];
	char			full_path[PATH_MAX + NAME_MAX];
	
	set_new_path(d_fl, new_path, old_path);

	ft_printf("{green}%s:\n{eoc}", new_path);

	fls = NULL;
	dir = opendir(new_path);

	if (!dir)
	{
		ft_printf("{neon} could not open dir: %s\n{eoc}", new_path);
		exit(1);
	}


	while ((entry = readdir(dir)))
	{
		if ((ft_strcmp(entry->d_name, ".") != 0) && (ft_strcmp(entry->d_name, "..") != 0) && (entry->d_name[0] != '.'))
		{
			add_file(&fls);
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
		}
	}
	print_files_a(fls);
	if (update_flags(-1) & 1 << fl_R)
	{
		for (; fls; fls = fls->next)
			if (S_ISDIR(fls->stat.st_mode))
			{
				char gg_path[PATH_MAX + NAME_MAX];

				gg_path[0] = '\0';
				ft_strcat(gg_path, new_path);
				ft_strcat(gg_path, fls->name);
				ft_ls(fls, gg_path);
			}
	}
	closedir(dir);
}

void        ft_ls(t_file *fls, char *path)
{
	ft_printf("------------------------------------------------------------\n");
	ft_printf("{pink}DIR: [%s]\n{eoc}", fls->name);
	if (S_ISREG(fls->stat.st_mode) && !((update_flags(-1) & 1 << fl_R)))
		print_files();
	if (S_ISDIR(fls->stat.st_mode))
	{
		print_dir_contains(fls, path);
	}
}

int main(int ac, char *av[])
{
	t_file	*fls;

    fls = parse_args(ac, av);
    while(fls)
    {
    	ft_ls(fls, NULL);
        fls = fls->next;
	}
	return (0);
}
