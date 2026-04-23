/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkprintf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:33:24 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:23:18 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "io/print/print.h"

static t_flags	pkflags(uint8_t attrib)
{
	t_flags		flags;

	flags.dot = -1;
	flags.minus = 0;
	flags.star = 0;
	flags.type = 0;
	flags.width = 0;
	flags.zero = 0;
	flags.plus = 0;
	flags.hex = 0;
	flags.blank = 0;
	flags.attrib = attrib;
	return (flags);
}

static void	pkswitch_types(int type, va_list *argp, int *count, t_flags flags)
{
	if (type == '%')
		pkprint_char('%', count, flags, 1);
	else if (type == 'c')
		pkprint_char(va_arg(*argp, long), count, flags, 0);
	else if (type == 's')
		pkprint_str(va_arg(*argp, char *), count, flags);
	else if (type == 'd' || type == 'i')
		pkprint_int(va_arg(*argp, long), count, flags);
	else if (type == 'u')
		pkprint_u_int(va_arg(*argp, unsigned long), count, flags);
	else if (type == 'x')
		pkprint_hex(va_arg(*argp, uint32_t), 1, count, flags);
	else if (type == 'X')
		pkprint_hex(va_arg(*argp, uint32_t), 0, count, flags);
	else if (type == 'p')
		pkprint_pointer(va_arg(*argp, unsigned long int), count, flags);
}

static void	pkprint_type(const char *fmt, va_list *argp, int *count, uint8_t attrib)
{
	int		i;
	t_flags	flags;

	i = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] != '%')
		{
			pkputchar_c(fmt[i++], count, attrib);
			continue ;
		}
		flags = pkflags(attrib);
		i++;
		pkcheck_flags(fmt, argp, &flags, &i);
		if (pkis_valid_type(fmt[i]))
			pkswitch_types(flags.type, argp, count, flags);
		else
			pkputchar_c(fmt[i], count, attrib);
		if (*count == -1)
			return ;
		i++;
	}
}

int	printk(const char *fmt, ...)
{
	va_list	listp;
	int		count;

	count = 0;
	va_start(listp, fmt);
	pkprint_type(fmt, &listp, &count, VGA_FORE_WHITE | VGA_BACK_BLACK);
	va_end(listp);
	return (count);
}

int	cprintk(uint8_t attrib, const char *fmt, ...)
{
	va_list	listp;
	int		count;

	count = 0;
	va_start(listp, fmt);
	pkprint_type(fmt, &listp, &count, attrib);
	va_end(listp);
	return (count);
}