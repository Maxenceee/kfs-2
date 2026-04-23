/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:51:16 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:05:06 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

char	*ft_str_tolower(char *str)
{
	uint32_t	i;

	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);
	return (str);
}

int	ft_tolower(int num)
{
	if (num >= 65 && num <= 90)
		num += 32;
	return (num);
}
