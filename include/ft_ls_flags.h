/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_flags.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 23:15:54 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/28 23:17:56 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_FLAGS_H
# define FT_LS_FLAGS_H

# include <inttypes.h>

/*
** there is english alphabet for you:
** A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z.
** file type
*/
typedef enum		e_flags
{
	flag_def = -1,
	flag_a,
	flag_l,
	flag_r,
	flag_t,
	flag_R
}					t_flags;

# define ISFLAG(shift) ({update_flags(-1) & 1 << shift;})

int32_t		update_flags(const int8_t shift);

#endif
