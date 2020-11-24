#include "ft_ls.h"

void		foo(void)
{
	static t_file file = {NULL, 0, 0, NULL};

	return ;
}

static char	f_type(mode_t mode)
{
    char	c;
	mode_t	type;

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

static char	*f_permissions(mode_t mode)
{
	static char *rwx[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
    static char bits[11];

	bits[0] = f_type(mode);
	strcpy(&bits[1], rwx[(mode >> 6)& 7]);
    strcpy(&bits[4], rwx[(mode >> 3)& 7]);
    strcpy(&bits[7], rwx[(mode & 7)]);
	if (mode & S_ISUID)
        bits[3] = (mode & S_IXUSR) ? 's' : 'S';
    if (mode & S_ISGID)
        bits[6] = (mode & S_IXGRP) ? 's' : 'l';
    if (mode & S_ISVTX)
        bits[9] = (mode & S_IXOTH) ? 't' : 'T';
    bits[10] = '\0';
    return(bits);
}

// static char	*f_date(char* str, time_t val)
// {
// 	time()
// 	strftime(str, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
// 	return str;
// }


// -l flag is here
void		print_files(t_file *fls)
{
	struct group	*grp;
	struct passwd	*pw;

	if (update_flags(-1) & 1 << fl_l)
	{
		// permissons
		ft_printf("%s ", f_permissions(fls->stat.st_mode));

		// count of links
		ft_printf("%d ", fls->stat.st_nlink);

		// author
		if ((pw = getpwuid(fls->stat.st_uid)))
			ft_printf("%s ", pw->pw_name);
		else
			ft_printf("%d ", fls->stat.st_gid);

		// group
		if ((grp = getgrgid(fls->stat.st_gid)) != NULL)
			ft_printf("%s ", grp->gr_name);
		else
			ft_printf("%d ", fls->stat.st_gid);

		// size
		ft_printf("%d ", fls->stat.st_size);

		//time
		// ЕБУЧЕЕ КОСТЫЛИЩЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕ БЛЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯТЬ
		ft_printf("%.12s ", ctime(&fls->stat.st_mtime) + 4);
	}
	ft_printf("%s\n", fls->name);
}

void		format_print_files(t_file *fls)
{
	for (; fls; fls = fls->next)
	{
		// -a
		if (update_flags(-1) & 1 << fl_a)
			print_files(fls);
		else if ((fls->name[0] != '.'))
			print_files(fls);
	}
	// ft_printf("\n");
}
