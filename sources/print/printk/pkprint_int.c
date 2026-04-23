/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkprint_int_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:17:43 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:17:27 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

static void	pkprint_in_int_spaces(char *d_i, int save_i,
	int *count, t_flags flags)
{
	uint32_t	len;

	len = pkstrlen(d_i);
	if (save_i < 0 && flags.dot >= 0)
		pkputchar_c('-', count, flags.attrib);
	else if (save_i >= 0 && flags.plus == 1)
		pkputchar_c('+', count, flags.attrib);
	else if (save_i >= 0 && flags.blank == 1)
		pkputchar_c(' ', count, flags.attrib);
	if (flags.dot >= 0)
		pkprint_width(flags.dot - 1, len - 1, 1, count, flags.attrib);
	pkputstrprec(d_i, len, count, flags.attrib);
}

static void	pkprint_int_spaces(char *d_i, int save_i,
	int *count, t_flags flags)
{
	uint32_t	len;

	len = pkstrlen(d_i);
	if (flags.minus == 1)
		pkprint_in_int_spaces(d_i, save_i, count, flags);
	if (flags.dot >= 0 && (uint32_t)flags.dot < len)
		flags.dot = len;
	if (flags.dot >= 0)
	{
		flags.width -= flags.dot;
		pkprint_width(flags.width, 0, 0, count, flags.attrib);
	}
	else
		pkprint_width(flags.width, len, flags.zero, count, flags.attrib);
	if (flags.minus == 0)
		pkprint_in_int_spaces(d_i, save_i, count, flags);
}

static void	pkprint_int_flags(t_flags *flags, long int *li, int *count)
{
	if (*li >= 0 && (flags->plus == 1 || flags->blank == 1))
		flags->width--;
	if (!(flags->dot >= 0 || flags->zero == 1))
		return ;
	if (*li < 0)
	{
		if (flags->zero == 1 && flags->dot == -1)
			pkputstrprec("-", 1, count, flags->attrib);
		(*li) *= -1;
		flags->zero = 1;
		flags->width--;
	}
	else if (*li >= 0 && flags->plus == 1
		&& flags->zero == 1 && flags->dot == -1)
	{
		pkputstrprec("+", 1, count, flags->attrib);
		flags->plus = 0;
	}
	else if (*li >= 0 && flags->blank == 1
		&& flags->zero == 1 && flags->dot == -1)
	{
		pkputstrprec(" ", 1, count, flags->attrib);
		flags->blank = 0;
	}
}

void	pkprint_int(int i, int *count, t_flags flags)
{
	char		*d_i;
	long int	li;

	li = i;
	pkprint_int_flags(&flags, &li, count);
	if (li == 0 && flags.dot == 0)
		d_i = __printk_alloc(1 * sizeof(char));
	else
		d_i = pkitoa(li);
	if (!d_i)
		return ;
	pkprint_int_spaces(d_i, i, count, flags);
	__printk_free(d_i);
}
