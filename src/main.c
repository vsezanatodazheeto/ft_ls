#include "ft_ls.h"

int		asc_sort(t_file *f1, t_file *f2)
{
	return(f1->name < f2->name);
}

int		desc_sort(t_file *f1, t_file *f2)
{
	return(f1->name > f2->name);
}

t_file  *merge(t_file* l1, t_file* l2, int	(*f_ptr)(t_file *, t_file *))
{
	t_file dummy[1];
	t_file* p = dummy;

	while (l1 && l2)
	{
		// if (l1->name < l2->name)
		if (f_ptr(l1, l2))
		{
			p->next = l1;
			l1 = l1->next;
		}
		else {
			p->next = l2;
			l2 = l2->next;
		}

		p = p->next;
	}

	if (l1)
		p->next = l1;
	if (l2)
		p->next = l2;

	return dummy->next;
}

t_file* merge_Sort(t_file* head, int (*f_ptr)(t_file *, t_file *))
{

	/* terminating condition */

	if (head == NULL || head->next == NULL)
		return head;


	t_file* slowPtr = head, *fastPtr = head, *prev = NULL;


	while (fastPtr != NULL && fastPtr->next != NULL)
	{
		prev = slowPtr;
		slowPtr = slowPtr->next;
		fastPtr  = fastPtr->next->next;
	}

	/* split the list int two half */
	prev->next = NULL;

	t_file* l1 = merge_Sort(head, f_ptr);
	t_file* l2 = merge_Sort(slowPtr, f_ptr);

	return merge(l1, l2, f_ptr);
}

void        print_files(void)
{
    printf("PRINT FILES\n");
}

void				format_print_files(t_file *fls)
{
	for (; fls; fls = fls->next)
	{
		// -a
		if (update_flags(-1) & 1 << fl_a)
			ft_printf("%s\n", fls->name);
		else if ((fls->name[0] != '.'))
			ft_printf("%s\n", fls->name);
	}
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
	t_file			*fls_copy;
	char			new_path[PATH_MAX];
	char			full_path[PATH_MAX + NAME_MAX];
	int				(*f_ptr)(t_file *, t_file *);

	set_new_path(d_fl, new_path, old_path);
	ft_printf("{green}%s:\n{eoc}", new_path);
	fls = NULL;
	dir = opendir(new_path);

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
	}
	format_print_files(fls);
	ft_printf("\n");
	ft_printf("\n");
	ft_printf("\n");
	f_ptr = asc_sort;
	fls = merge_Sort(fls, f_ptr);
	format_print_files(fls);
	ft_printf("\n");
	ft_printf("\n");
	ft_printf("\n");
	f_ptr = desc_sort;
	fls = merge_Sort(fls, f_ptr);
	format_print_files(fls);
	
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

void        ft_ls(t_file *fls, char *path)
{
	ft_printf("\n");
	if (S_ISREG(fls->stat.st_mode) && !((update_flags(-1) & 1 << fl_R)))
		print_files();
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
