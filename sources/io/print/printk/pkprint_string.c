/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkprint_string_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:07:51 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:03:25 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "io/print/print.h"

void	pkputstrprec(char *str, int prec, int *count, uint8_t attrib)
{
	int	c;

	c = 0;
	while (str[c] && c < prec)
		pkputchar(str[c++], attrib);
	(*count) += c;
}

static void	pkprint_spaces(char *str, int *count, t_flags flags)
{
	uint32_t	len;

	len = pkstrlen(str);
	if (flags.dot >= 0)
	{
		pkprint_width(flags.dot, len, 0, count, flags.attrib);
		pkputstrprec(str, flags.dot, count, flags.attrib);
	}
	else
	{
		pkputstrprec(str, len, count, flags.attrib);
	}
}


void	pkprint_str(char *s, int *count, t_flags flags)
{
	int		c;
	uint32_t	len;

	c = 0;
	if (!s)
	{
		if (!(flags.dot == -1 || flags.dot >= 6))
			return (pkprint_width(flags.width, 0, 0, count, flags.attrib));
		s = "(null)";
	}
	len = pkstrlen(s);
	if (flags.dot >= 0 && (uint32_t)flags.dot > len)
		flags.dot = len;
	if (flags.minus == 1)
		pkprint_spaces(s, count, flags);
	if (flags.dot >= 0 && flags.width > 0)
		pkprint_width(flags.width, flags.dot, 0, count, flags.attrib);
	else if (flags.dot >= 0)
		pkprint_max_width(flags.width, flags.dot, 0, count, flags.attrib);
	else
		pkprint_width(flags.width, len, 0, count, flags.attrib);
	if (flags.minus == 0)
		pkprint_spaces(s, count, flags);
	(*count) += c;
}
