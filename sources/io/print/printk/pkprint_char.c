/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkprint_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:59:34 by mgama             #+#    #+#             */
/*   Updated: 2026/05/19 10:59:35 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "io/print/print.h"

void	pkputchar(char c, uint8_t attrib)
{
	vga_put(c, attrib);
}

void	pkputchar_c(char c, int *count, uint8_t attrib)
{
	vga_put(c, attrib);
	(*count)++;
}

void	pkprint_char(char c, int *count, t_flags flags, int percent)
{
	if (percent)
		return ((void)pkputchar_c(c, count, flags.attrib));
	if (flags.minus == 1)
		pkputchar_c(c, count, flags.attrib);
	pkprint_width(flags.width, 1, 0, count, flags.attrib);
	if (flags.minus == 0)
		pkputchar_c(c, count, flags.attrib);
}
