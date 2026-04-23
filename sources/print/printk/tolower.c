/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pktolower_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:51:16 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:05:06 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

char	*pkstr_tolower(char *str)
{
	uint32_t	i;

	i = -1;
	while (str[++i])
		str[i] = pktolower(str[i]);
	return (str);
}

int	pktolower(int num)
{
	if (num >= 65 && num <= 90)
		num += 32;
	return (num);
}
