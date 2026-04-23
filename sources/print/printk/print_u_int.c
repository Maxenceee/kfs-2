/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkprint_u_int_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:08:39 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:17:27 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

static void	pkprint_in_u_int_spaces(char *unsi_int, int *count, t_flags flags)
{
	uint32_t	len;

	len = pkstrlen(unsi_int);
	if (flags.dot >= 0)
		pkprint_width(flags.dot - 1, len - 1, 1, count);
	pkputstrprec(unsi_int, len, count);
}

static void	pkprint_u_int_spaces(char *unsi_int, int *count, t_flags flags)
{
	uint32_t	len;

	len = pkstrlen(unsi_int);
	if (flags.minus == 1)
		pkprint_in_u_int_spaces(unsi_int, count, flags);
	if (flags.dot >= 0 && (uint32_t)flags.dot < len)
		flags.dot = len;
	if (flags.dot >= 0)
	{
		flags.width -= flags.dot;
		pkprint_width(flags.width, 0, 0, count);
	}
	else
		pkprint_width(flags.width,
			len, flags.zero, count);
	if (flags.minus == 0)
		pkprint_in_u_int_spaces(unsi_int, count, flags);
}

void	pkprint_u_int(uint32_t unsi, int *count, t_flags flags)
{
	char	*unsi_int;

	unsi = (uint32_t)(4294967295 + 1
			+ unsi);
	if (flags.dot == 0 && unsi == 0)
		return (pkprint_width(flags.width, 0, 0, count));
	unsi_int = pku_itoa(unsi);
	if (!unsi_int)
		return ;
	pkprint_u_int_spaces(unsi_int, count, flags);
	__printk_free(unsi_int);
}
