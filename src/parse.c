/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:08:44 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/28 22:09:29 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static uint8_t	update_files_stats_handling(t_file **fls, const char *f_name)
{
	struct stat	stat_temp;

	ft_bzero(&stat_temp, sizeof(struct stat));
	if (lstat(f_name, &stat_temp) < 0)
	{
		ERR_STATF(f_name);
		return (1);
	}
	else
	{
		file_add(fls);
		ft_memcpy(&(*fls)->stat, &stat_temp, sizeof(struct stat));
		update_stat_cells_len(&(*fls)->stat);
		if (!((*fls)->name = ft_strdup(f_name)))
			ERR_STRDUP;
	}
	return (0);
}

static t_file	*update_files(char **splited_av)
{
	t_file		*fls;
	uint8_t		is_wrong_files;
	int32_t		i;

	fls = NULL;
	is_wrong_files = 0;
	i = 0;
	while (splited_av[i])
	{
		if (update_files_stats_handling(&fls, splited_av[i]) != 0)
			is_wrong_files = 1;
		i++;
	}
	if (!fls && !is_wrong_files)
		update_files_stats_handling(&fls, D_CURR);
	return (fls);
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
