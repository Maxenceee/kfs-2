/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkprint_pointer_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:47:22 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:17:27 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

static void	pkprint_in_pointer_spaces(char *pointer, uint32_t or,
	int *count, t_flags flags)
{
	uint32_t	len;

	len = pkstrlen(pointer);
	if (or)
		pkputstrprec("0x", 2, count, flags.attrib);
	if (flags.dot >= 0)
	{
		pkprint_width(flags.dot, len, 1, count);
		pkputstrprec(pointer, flags.dot, count, flags.attrib);
	}
	else
		pkputstrprec(pointer, len, count, flags.attrib);
}

void	pkprint_pointer(uint32_t ull, int *count, t_flags flags)
{
	char	*pointer;
	uint32_t	len;

	if (ull == 0 && flags.dot == 0)
	{
		pkputstrprec("0x", 2, count, flags.attrib);
		pkprint_width(flags.width, 0, 1, count);
		return ;
	}
	if (ull)
		pointer = pkconvert_base(ull, 16);
	else
		pointer = pkstrdup("(nil)");
	if (!pointer)
		return ;
	len = pkstrlen(pointer);
	pointer = pkstr_tolower(pointer);
	if ((uint32_t)flags.dot < len)
		flags.dot = len;
	if (flags.minus == 1)
		pkprint_in_pointer_spaces(pointer, ull, count, flags);
	pkprint_width(flags.width, len + (2 * (ull > 0)), 0, count);
	if (flags.minus == 0)
		pkprint_in_pointer_spaces(pointer, ull, count, flags);
	__printk_free(pointer);
}
