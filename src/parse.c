/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:08:44 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/28 00:34:56 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int is_flags_parsing = 1;

static t_file	*update_files(char ***splited_av)
{
	t_file		*fls;
	uint8_t		is_wrong_files;
	struct stat	stat_temp;
	
	fls = NULL;
	is_wrong_files = 0;
	for (int i = 0; splited_av[i]; i++)
	{
		ft_printf("%s\n", splited_av[i][0]);
		for (int j = 0; splited_av[i][j]; j++)
		{
			ft_bzero(&stat_temp, sizeof(struct stat));
			// if ((splited_av[i][j][0] != '-' && splited_av[i][j][0] != '\0')
			// || (splited_av[i][j][0] == '-' && splited_av[i][j][1] == '\0')) // + обработка фалйа с названием '-'
			{
				ft_printf("{pink}%s\n{eoc}", splited_av[i][j]);
				if (lstat(splited_av[i][j], &stat_temp) < 0)
				{
					ft_printf("{yellow}------{eoc}\n");
					ERR_STATF(splited_av[i][j]);
					is_wrong_files = 1;
				}
				else
				{
					file_add(&fls);
					ft_memcpy(&fls->stat, &stat_temp, sizeof(struct stat));
					update_stat_cells_len(&fls->stat);
					if (!(fls->name = ft_strdup(splited_av[i][j])))
						ERR_STRDUP;
				}
			}
		}
	}
	if(!fls && !is_wrong_files)
	{
		ft_printf("{red}-------------------------------\n{eoc}");
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

static void		parse_set_flags(char *av)
{
	e_flags		shift;
	int32_t		i;

	if (!av)
		return ;
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
			{
				is_flags_parsing = 0;
				break ;
			}
			else
				ERR_LSFLAG(av[i]);
		}
		else
			ERR_LSFLAG(av[i]);
		update_flags(shift);
		i++;
	}
}

static char		***parse_check_flags(char ***splited_av)
{
	int32_t		i;
	int32_t		j;
	char		***splited_av_new;

	i = 0;
	while (splited_av[i] && is_flags_parsing)
	{
		if (splited_av[i][0] && splited_av[i][0][0] != CH_FLAG)
			break ;
		j = 0;
		while (splited_av[i][j] && is_flags_parsing)
		{
			if (splited_av[i][j][0] != CH_FLAG)
				break ;
			ft_printf("{orange}%s\n{eoc}", splited_av[i][j]);
			parse_set_flags(splited_av[i][j]);
			j++;
		}
		i++;
	}
	if (splited_av[i])
		splited_av_new = splited_av + i - 1;
	if (splited_av[i - 1][j])
	{
		ft_printf("{red}%s\n{eoc}", splited_av[i - 1][j]);
		splited_av_new = splited_av + (i - 1) * j;
		splited_av_new = &(splited_av[i]) + j;
		// splited_av_new = splited_av  + i - 1;
		// splited_av_new = splited_av_new + j;
	}
	// if (!(*(splited_av + i)))
	// {
	// 	// return (NULL);
	// 	*splited_av_new = *(splited_av + i);
	// }
	// else
	// {
	// 	splited_av_new = splited_av + i;
	// 	// *splited_av_new = *(splited_av + i);
	// 	// **splited_av_new = **(splited_av + j - 1);
	// 	// ***splited_av_new = ***(splited_av_new + 0);
	// }
	for (int k = 0; splited_av_new[k]; k++)
		for(int y = 0; splited_av_new[k][y]; y++)
			ft_printf("{neon}%s\n{eoc}", splited_av_new[k][y]);
	exit(0);
	return (splited_av_new);
}

t_file			*parse_args(int ac, char *av[])
{
	t_file		*fls;
	char		***splited_av;
	char		***splited_av_copy;

	splited_av = av_split(ac, av);
	if (!splited_av)
		ERR_AVSPLIT;
	av_print(splited_av);
	splited_av = parse_check_flags(splited_av);
	fls = update_files(splited_av);
	exit(1);
	av_free(splited_av_copy);
	return (fls);
}