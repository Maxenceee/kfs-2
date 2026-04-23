/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkprint_width_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:57:03 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:03:49 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

void	pkprint_width(int width, int minus, int has_zero, int *count)
{
	while (width - minus > 0)
	{
		if (has_zero)
			pkputchar('0');
		else
			pkputchar(' ');
		width -= 1;
		(*count)++;
	}
}

void	pkprint_max_width(int width, int max, int has_zero, int *count)
{
	if (max < width)
		return ;
	while (width - max > 0)
	{
		if (has_zero)
			pkputchar('0');
		else
			pkputchar(' ');
		width -= 1;
		(*count)++;
	}
}
