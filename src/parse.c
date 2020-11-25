/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:08:44 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/25 21:37:51 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	*update_files(char ***splited_av)
{
	t_file		*fls;

	fls = NULL;
	for (int i = 0; splited_av[i]; i++)
	{
		for (int j = 0; splited_av[i][j]; j++)
		{
			if (splited_av[i][j][0] != '-' && splited_av[i][j][0] != '\0')
			{
				file_add(&fls);
				if (lstat(splited_av[i][j], &fls->stat) < 0)
					fls->fe_err = fe_noex; // тут доделать обработчик, может быть еще один тип
				else
					set_format_attb(&fls->stat);
				if (!(fls->name = ft_strdup(splited_av[i][j])))
					ERR_STRDUP;
			}
		}
	}
	if(!fls)
	{
		file_add(&fls);
		if (!(fls->name = ft_strdup(D_CURR)))
			ERR_STRDUP;
		if (lstat(fls->name, &fls->stat) < 0)
		{
			// не знаю, нужно ли тут это, в коем веке мы не можем узнать инфу о папке, в которой находимся
			fls->fe_err = fe_noex; // тут доделать обработчик, может быть еще один тип
		}
	}
	return (fls);
}

/*
** accept at the entrance char * that starts from "-...""
*/

static void		parse_set_flags(char *av)
{
	e_flags		shift;

	if (!av)
		return ;
	av++;
	shift = fl_noex;
	while (*av)
	{
		if (*av == 'a')
			shift = fl_a;
		else if (*av == 'l')
			shift = fl_l;
		else if (*av == 'r')
			shift = fl_r;
		else if (*av == 't')
			shift = fl_t;
		else if (*av == 'R')
			shift = fl_R;
		else
			ERR_LSFLAG(*av);
		update_flags(shift);
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

t_file			*parse_args(int ac, char *av[])
{
	t_file		*fls;
	char		***splited_av;

	splited_av = av_split(ac, av);
	if (!splited_av)
		ERR_AVSPLIT;
	parse_check_flags(splited_av);
	fls = update_files(splited_av);
	av_free(splited_av);
	return (fls);
}