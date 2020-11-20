#include "ft_ls.h"

int32_t			update_flags(const int8_t shift)
{
	static int32_t flags = 0;

	flags = flags | 1 << shift;
	return (flags);
}

t_args			*create_arg(void)
{
	t_args		*arg;

	arg = (t_args *)malloc(sizeof(t_args));
	if (!arg)
		exit(1);
	arg->name = NULL;
	arg->next = NULL;
	return (arg);
}

void			add_arg(t_args **arg)
{
	t_args		*new_arg;

	new_arg = create_arg();
	if (*arg)
		new_arg->next = *arg;
	*arg = new_arg;
}

static t_args	*update_args(char ***splited_av)
{
	t_args		*arg;

	arg = NULL;
	for (int i = 0; splited_av[i]; i++)
	{
		for (int j = 0; splited_av[i][j]; j++)
		{
			if (splited_av[i][j][0] != '-' && splited_av[i][j][0] != '\0')
			{
				add_arg(&arg);
				arg->name = ft_strdup(splited_av[i][j]);
			}
		}
	}
	return (arg);
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
			;
			// exit(1);
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
	for (; st->args; st->args = st->args->next)
		ft_printf("{pink}%s\n{eoc}", st->args->name);
	av_free(splited_av);
}