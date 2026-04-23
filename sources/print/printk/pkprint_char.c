/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkprint_char_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:55:31 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 12:51:08 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

void	pkputchar(char c)
{
	vga_put(c, VGA_FORE_WHITE | VGA_BACK_BLACK);
}

void	pkputchar_c(char c, int *count)
{
	vga_put(c, VGA_FORE_WHITE | VGA_BACK_BLACK);
	(*count)++;
}

void	pkprint_char(char c, int *count, t_flags flags, int percent)
{
	if (percent)
		return ((void)pkputchar_c(c, count));
	if (flags.minus == 1)
		pkputchar_c(c, count);
	pkprint_width(flags.width, 1, 0, count);
	if (flags.minus == 0)
		pkputchar_c(c, count);
}
