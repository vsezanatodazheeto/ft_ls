#include "ft_ls.h"

void        print_files(void)
{
    printf("PRINT FILES\n");
}

t_file		*print_dir_contains(t_file *arg)
{
	DIR				*dir;
	struct dirent	*entry;
	t_file			*new_args;

	dir = opendir(arg->name);
	new_args = NULL;
	if (!dir)
	{
		ft_printf("{neon} could not open dir: %s\n{eoc}", arg->name);
		exit(1);
	}
	while ((entry = readdir(dir)))
	{
		ft_printf("%s\n", entry->d_name);
		if (ft_strcmp(entry->d_name, ".") != 0 && ft_strcmp(entry->d_name, "..") != 0)
		{
			add_file(&new_args);
			if (!(new_args->name = ft_strdup(entry->d_name)))
				exit(1);
			if (stat(new_args->path, &new_args->stat) < 0)
				exit(2);
		}
	}
	closedir(dir);
	return (new_args);
}

void        ft_ls(t_file *args)
{
    t_file  *cur;
    t_file  *possible_new_args;

    cur = args;
	ft_printf("------------------------------------------------------------\n");
    while(cur)
    {
        if (S_ISREG(cur->stat.st_mode) && !(update_flags(-1) & 1 << fl_R))
            print_files();
        else if (S_ISDIR(cur->stat.st_mode))
        {
			ft_printf("{pink}DIR: [%s]\n{eoc}", cur->name);
            if (!(possible_new_args = print_dir_contains(cur)))
				break ;
            if(update_flags(-1) & 1 << fl_R)
            {
                ft_ls(possible_new_args);
            }
        }
        cur = cur->next;
    }
}


int			main(int ac, char *av[])
{
	t_file	*fls;

    fls = parse_args(ac, av);
    // ft_ls(st->args);
	return (0);
}
