/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:55:07 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/25 20:55:10 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_flags.h"

int32_t			update_flags(const int8_t shift)
{
	static int32_t flags = 0;

	flags = flags | 1 << shift;
	return (flags);
}
