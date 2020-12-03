/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:08:49 by yshawn            #+#    #+#             */
/*   Updated: 2020/12/03 20:45:09 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			format_output_print(t_file *fls, uint64_t total, \
									const char *path)
{
	if (ISFLAG(flag_l))
		ft_printf("total %u\n", total);
	while (fls)
	{
		if (ISFLAG(flag_a))
			format_file_print(fls, path);
		else if ((*fls->name != CH_DOT))
			format_file_print(fls, path);
		fls = fls->next;
	}
}

void			ls_base(t_file *fls, char *path)
{
	if (!S_ISDIR(fls->stat.st_mode) && !ISFLAG(flag_R))
		format_file_print(fls, path);
	else
		ls(fls, path);
}

t_file			*parse_args(int ac, char *argv[])
{
	t_file		*fls;
	char		**av;
	char		**av_copy;

	if (!(av = av_split(ac, (const char **)argv)))
	{
		if (AV_EMPTY_ARGS)
			ERR_LSEMPAR;
		ERR_AVSPLIT;
	}
	av_copy = av;
	av = parse_check_flags(av);
	fls = update_files(av);
	ft_arrdel((void ***)&av_copy);
	return (fls);
}

int				main(int ac, char *av[])
{
	t_file		*fls;
	t_file		*fls_copy;

	fls = parse_args(ac, av);
	ftype_merge_sort(&fls);
	fls_copy = fls;
	while (fls)
	{
		ls_base(fls, NULL);
		fls = fls->next;
	}
	file_list_free(&fls_copy);
	return (0);
}
