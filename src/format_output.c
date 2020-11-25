#include "ft_ls.h"

uint64_t			fo_get(int i)
{
	t_format_output	*f_out;

	f_out = format_output_set(NULL);
	if (i == 1)
	{
		// ft_printf("{blue}%ld\n{eoc}", f_out->s_links);
		return (f_out->s_links);
	}
	else if (i == 2)
	{
		// ft_printf("{blue}%ld\n{eoc}", f_out->s_user);
		return (f_out->s_user);
	}
	else if (i == 3)
	{
		// ft_printf("{blue}%ld\n{eoc}", f_out->s_group);
		return (f_out->s_group);
	}
	else if (i == 4)
	{
		// ft_printf("{blue}%ld\n{eoc}", f_out->s_size);
		return (f_out->s_size);
	}
	return (0);
}

t_format_output		*format_output_set(const struct stat *stat)
{
	static t_format_output	f_out = {0, 0, 0, 0};
	t_format_output			temp;
	struct group			*grp;
	struct passwd			*pw;

	if (!stat)
		return (&f_out);
	temp.s_links = ft_numlen(stat->st_nlink, 10);
	if ((pw = getpwuid(stat->st_uid)))
		temp.s_user = ft_strlen(pw->pw_name);
	else
		temp.s_user = ft_numlen(stat->st_gid, 10);
	if ((grp = getgrgid(stat->st_gid)))
		temp.s_group = ft_strlen(grp->gr_name);
	else
		temp.s_group = ft_numlen(stat->st_gid, 10);
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
		ft_printf("%*d ", fo_get(1), fls->stat.st_nlink);

		// user
		if ((pw = getpwuid(fls->stat.st_uid)))
			ft_printf("%*s  ", fo_get(2), pw->pw_name);
		else
			ft_printf("%*d ", fo_get(2), fls->stat.st_gid);

		// group
		if ((grp = getgrgid(fls->stat.st_gid)) != NULL)
			ft_printf("%*s  ", fo_get(3), grp->gr_name);
		else
			ft_printf("%*d ", fo_get(3), fls->stat.st_gid);

		// size
		ft_printf("%*d ", fo_get(4), fls->stat.st_size);

		//time
		// ЕБУЧЕЕ КОСТЫЛИЩЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕ БЛЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯЯТЬ
		ft_printf("%.12s ", ctime(&fls->stat.st_mtime) + 4);
	}
	ft_printf("%s\n", fls->name);
}

void		format_print_files(t_file *fls, uint64_t total)
{
	if (update_flags(-1) & 1 << fl_l)
		ft_printf("total %u\n", total);
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
