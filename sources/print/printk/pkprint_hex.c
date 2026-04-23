/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkprint_hex_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:26:50 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:17:27 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

static void	pkprint_hex_prefix(char *hexa, int lower,
	int *count, t_flags *flags)
{
	(void)hexa;
	if (flags->hex == 1)
	{
		if (lower == 1)
			pkputstrprec("0x", 2, count, flags->attrib);
		else
			pkputstrprec("0X", 2, count, flags->attrib);
		flags->width -= 2;
		flags->hex = 0;
	}
}

static void	pkprint_in_hex_spaces(char *hexa, int lower,
	int *count, t_flags flags)
{
	uint32_t	len;

	len = pkstrlen(hexa);
	pkprint_hex_prefix(hexa, lower, count, &flags);
	if (flags.dot >= 0)
		pkprint_width(flags.dot - 1, len - 1, 1, count);
	pkputstrprec(hexa, len, count, flags.attrib);
}

static void	pkprint_hex_spaces(char *hexa, int lower,
	int *count, t_flags flags)
{
	uint32_t	len;

	len = pkstrlen(hexa);
	if (flags.minus == 1)
		pkprint_in_hex_spaces(hexa, lower, count, flags);
	if (flags.zero == 1 && flags.dot == -1)
		pkprint_hex_prefix(hexa, lower, count, &flags);
	if (flags.dot >= 0 && (uint32_t)flags.dot < len)
		flags.dot = len;
	if (flags.dot >= 0)
	{
		flags.width -= flags.dot;
		pkprint_width(flags.width, (2 * flags.hex), 0, count);
	}
	else
		pkprint_width(flags.width,
			len + (2 * flags.hex), flags.zero, count);
	if (flags.minus == 0)
		pkprint_in_hex_spaces(hexa, lower, count, flags);
}

void	pkprint_hex(uint32_t ui, int lower, int *count, t_flags flags)
{
	char	*hexa;

	ui = (uint32_t)(4294967295 + 1
			+ ui);
	if (flags.dot == 0 && ui == 0)
	{
		pkprint_width(flags.width, 0, 0, count);
		return ;
	}
	if (ui == 0)
		flags.hex = 0;
	hexa = pkconvert_base((uint32_t)ui, 16);
	if (!hexa)
		return ;
	if (lower == 1)
		hexa = pkstr_tolower(hexa);
	pkprint_hex_spaces(hexa, lower, count, flags);
	__printk_free(hexa);
}
