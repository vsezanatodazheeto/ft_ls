/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:08:44 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/28 19:19:13 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	*update_files(char **splited_av)
{
	t_file		*fls;
	struct stat	stat_temp;
	uint8_t		is_wrong_files;
	int32_t		i;

	fls = NULL;
	is_wrong_files = 0;
	i = 0;
	while (splited_av[i])
	{
		ft_bzero(&stat_temp, sizeof(struct stat));
		if (lstat(splited_av[i], &stat_temp) < 0)
		{
			ERR_STATF(splited_av[i]);
			is_wrong_files = 1;
		}
		else
		{
			file_add(&fls);
			ft_memcpy(&fls->stat, &stat_temp, sizeof(struct stat));
			update_stat_cells_len(&fls->stat);
			if (!(fls->name = ft_strdup(splited_av[i])))
				ERR_STRDUP;
		}
		i++;
	}
	if (!fls && !is_wrong_files)
	{
		file_add(&fls);
		if (!(fls->name = ft_strdup(D_CURR)))
			ERR_STRDUP;
		if (lstat(fls->name, &fls->stat) < 0)
			ERR_STATF(fls->name);
	}
	return (fls);
}

/*
** accept at the entrance char * that starts from "-...""
*/

static uint8_t	parse_set_flags(char *av)
{
	e_flags		shift;
	int32_t		i;

	if (!av)
		return (0);
	i = 1;
	shift = flag_def;
	while (av[i])
	{
		if (av[i] == 'a')
			shift = flag_a;
		else if (av[i] == 'l')
			shift = flag_l;
		else if (av[i] == 'r')
			shift = flag_r;
		else if (av[i] == 't')
			shift = flag_t;
		else if (av[i] == 'R')
			shift = flag_R;
		else if (av[i] == '1')
			;
		else if (av[i] == '-')
		{
			if (ft_strcmp(av + i - 1, "--") == 0)
				return (1);
			else
				ERR_LSFLAG(av[i]);
		}
		else
			ERR_LSFLAG(av[i]);
		update_flags(shift);
		i++;
	}
	return (0);
}

static char		**parse_check_flags(char *s_av[])
{
	int32_t		i;
	int32_t		j;

	i = 0;
	while (s_av[i])
	{
		if (s_av[i][0] != CH_FLAG)
			break ;
		if (parse_set_flags(s_av[i]) != 0)
			break ;
		i++;
	}
	return (s_av + i);
}

t_file			*parse_args(int ac, char *argv[])
{
	t_file		*fls;
	char		***splited_av;
	char		**av;
	char		**av_copy;

	if (!(splited_av = av_split(ac, argv)))
		ERR_AVSPLIT;
	if (!(av = av_convert(splited_av)))
		ERR_AVSPLIT;
	av_free(splited_av);
	av_copy = av;
	av = parse_check_flags(av);
	fls = update_files(av);
	ft_arrdel((void ***)&av_copy);
	return (fls);
}
