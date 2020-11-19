#include "ft_ls.h"

int32_t			update_flags(const int8_t shift)
{
	static int32_t flags = 0;

	flags = flags | 1 << shift;
	return (flags);
}

static t_list	*update_args(char ***splited_av)
{

}

static void		parse_set_flags(char *av)
{
	e_flags		flag;

	if (!av)
		return ;
	av++; //skip - (minus)
	flag = fl_noex;
	while (*av)
	{
		if (*av == 'a')
			flag = fl_a;
		else if (*av == 'l')
			flag = fl_l;
		else if (*av == 'r')
			flag = fl_r;
		else if (*av == 't')
			flag = fl_t;
		else if (*av == 'R')
			flag = fl_R;
		else
			exit(1);
		update_flags(flag);
		av++;
	}
}

static void		parse_check_flags(char ***splited_av)
{
	int32_t		i;
	int32_t		j;

	i = 0;
	while (splited_av[i])
	{
		if (splited_av[i][0] && splited_av[i][0][0] != CH_FLAG)
			break ;
		j = 0;
		while (splited_av[i][j])
		{
			if (splited_av[i][j][0] != CH_FLAG)
				break ;
			parse_set_flags(splited_av[i][j]);
			j++;
		}
		i++;
	}
}

void			parse_args(t_struct *st, int ac, char *av[])
{
	char		***splited_av;

	splited_av = av_split(ac, av);
	if (!splited_av)
		exit (1);
	parse_check_flags(splited_av);
	st->flag = update_flags(fl_noex);
	st->args = update_args(splited_av);
	av_print(splited_av);
	av_free(splited_av);
}