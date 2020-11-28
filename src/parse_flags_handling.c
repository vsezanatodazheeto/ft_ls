/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:08:44 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/28 22:09:39 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int32_t			update_flags(const int8_t shift)
{
	static int32_t flags = 0;

	flags = flags | 1 << shift;
	return (flags);
}

/*
** accept at the entrance char * that starts from "-...""
*/

static e_flags	flag_cases(const char ch, e_flags *shift)
{
	if (ch == 'a')
		*shift = flag_a;
	else if (ch == 'l')
		*shift = flag_l;
	else if (ch == 'r')
		*shift = flag_r;
	else if (ch == 't')
		*shift = flag_t;
	else if (ch == 'R')
		*shift = flag_R;
	return (*shift);
}

static uint8_t	parse_set_flags(char *av)
{
	e_flags		shift;
	int32_t		i;

	shift = flag_def;
	i = 1;
	while (av[i])
	{
		if (flag_cases(av[i], &shift) >= 0)
			;
		else if (av[i] == '1')
			;
		else if (av[i] == '-')
		{
			if (ft_strcmp(av + i - 1, "--") == 0)
				return (0);
			else
				ERR_LSFLAG(av[i]);
		}
		else
			ERR_LSFLAG(av[i]);
		update_flags(shift);
		i++;
	}
	return (1);
}

char			**parse_check_flags(char *av[])
{
	int32_t		i;

	i = 0;
	while (av[i])
	{
		if (av[i][0] != CH_FLAG)
			break ;
		if (!parse_set_flags(av[i]))
			break ;
		i++;
	}
	return (av + i);
}
