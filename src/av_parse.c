/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   av_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:39:17 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/25 22:12:26 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** вынести в библиотеку как мини парсер для аргументов
** из стандартного потока ввода
*/

/*
** consider any cases:
** ./ft_ls -l -r ... args
** ./ft_ls "-l -r ...args"
** ./ft_ls "-l" ... "-r" ... "args_2"
*/

void		av_print(char ***splited_av)
{
	int32_t i;
	int32_t j;

	i = 0;
	while (splited_av[i])
	{
		j = 0;
		while (splited_av[i][j])
		{
			ft_printf("{green}%s\n{eoc}", splited_av[i][j]);
			j++;
		}
		i++;
	}
}

void		av_free(char ***splited_av)
{
	int32_t	i;

	i = 0;
	while (splited_av[i])
	{
		ft_arrdel((void ***)&splited_av[i]);
		i++;
	}
	free(splited_av);
}

char		***av_split(int ac, char *av[])
{
	int32_t	i;
	char	***splited_av;

	i = 0;
	{
		ac--;
		av++;
	}
	splited_av = (char ***)malloc(sizeof(char **) * (ac + 1));
	if (!splited_av)
		return (NULL);
	splited_av[ac] = NULL;
	while (i < ac)
	{
		splited_av[i] = ft_strsplit(av[i], ' ');
		if (!splited_av[i])
		{
			av_free(splited_av);
			return (NULL);
		}
		i++;
	}
	return (splited_av);
}
