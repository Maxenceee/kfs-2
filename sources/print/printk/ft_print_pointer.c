/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:47:22 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:17:27 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

static void	ft_print_in_pointer_spaces(char *pointer, uint32_t or,
	int *count, t_flags flags)
{
	uint32_t	len;

	len = ft_strlen(pointer);
	if (or)
		ft_putstrprec("0x", 2, count);
	if (flags.dot >= 0)
	{
		ft_print_width(flags.dot, len, 1, count);
		ft_putstrprec(pointer, flags.dot, count);
	}
	else
		ft_putstrprec(pointer, len, count);
}

void	ft_print_pointer(uint32_t ull, int *count, t_flags flags)
{
	char	*pointer;
	uint32_t	len;

	if (ull == 0 && flags.dot == 0)
	{
		ft_putstrprec("0x", 2, count);
		ft_print_width(flags.width, 0, 1, count);
		return ;
	}
	if (ull)
		pointer = ft_convert_base(ull, 16);
	else
		pointer = ft_strdup("(nil)");
	if (!pointer)
		return ;
	len = ft_strlen(pointer);
	pointer = ft_str_tolower(pointer);
	if ((uint32_t)flags.dot < len)
		flags.dot = len;
	if (flags.minus == 1)
		ft_print_in_pointer_spaces(pointer, ull, count, flags);
	ft_print_width(flags.width, len + (2 * (ull > 0)), 0, count);
	if (flags.minus == 0)
		ft_print_in_pointer_spaces(pointer, ull, count, flags);
	__printk_free(pointer);
}
