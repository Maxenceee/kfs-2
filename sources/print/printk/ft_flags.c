/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:47:14 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:09:47 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

void	ft_check_flags(const char *fmt, va_list *argp, t_flags *flags, int *idx)
{
	while (fmt[*idx])
	{
		if (!ft_isdigit(fmt[*idx]) && !ft_is_valid_type(fmt[*idx])
			&& !ft_is_valid_flag(fmt[*idx]))
			break ;
		ft_check_flags_identifiers(fmt, argp, flags, idx);
		if (ft_is_valid_type(fmt[*idx]))
		{
			flags->type = fmt[*idx];
			break ;
		}
		(*idx)++;
	}
}

void	ft_check_flags_identifiers(const char *fmt, va_list *argp,
	t_flags *flags, int *idx)
{
	if (fmt[*idx] == '0' && flags->width == 0 && flags->minus == 0)
		flags->zero = 1;
	if (fmt[*idx] == '.')
		ft_dot_flag(fmt, idx, flags, argp);
	if (fmt[*idx] == '-')
		ft_minus_flag(flags);
	if (fmt[*idx] == '#')
		ft_hex_flag(flags);
	if (fmt[*idx] == '+')
		ft_plus_flag(flags);
	if (fmt[*idx] == ' ')
		ft_blank_flag(flags, fmt, idx);
	if (fmt[*idx] == '*')
		ft_width_flag(argp, flags);
	if (ft_isdigit(fmt[*idx]))
		ft_digit_flag(fmt[*idx], flags);
}

void	ft_hex_flag(t_flags *flags)
{
	flags->hex = 1;
}

void	ft_blank_flag(t_flags *flags, const char *s, int *idx)
{
	while (s[*idx] == ' ')
		(*idx)++;
	if (flags->plus != 1)
		flags->blank = 1;
	(*idx)--;
}

void	ft_minus_flag(t_flags *flags)
{
	flags->minus = 1;
	flags->zero = 0;
}

void	ft_plus_flag(t_flags *flags)
{
	flags->plus = 1;
	flags->blank = 0;
}

void	ft_digit_flag(char c, t_flags *flags)
{
	if (flags->star == 1)
		flags->width = 0;
	flags->width = (flags->width * 10) + (c - '0');
}

void	ft_width_flag(va_list *args, t_flags *flags)
{
	flags->star = 1;
	flags->width = va_arg(*args, int);
	if (flags->width < 0)
	{
		flags->minus = 1;
		flags->width *= -1;
	}
}

void	ft_dot_flag(const char *save, int *start,
	t_flags *flags, va_list *args)
{
	(*start)++;
	if (save[*start] == '*')
	{
		flags->dot = va_arg(*args, int);
		(*start)++;
	}
	else
	{
		flags->dot = 0;
		while (ft_isdigit(save[*start]))
		{
			flags->dot = (flags->dot * 10) + (save[(*start)++] - '0');
		}
	}
}
