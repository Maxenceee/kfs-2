/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:26:34 by mgama             #+#    #+#             */
/*   Updated: 2026/05/19 11:27:23 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std/std.h"

int
katoi(const char *str)
{
	int					i;
	unsigned long int	nbr;
	int					sign;

	i = 0;
	nbr = 0;
	sign = 0;
	if (!str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if ((char)str[i] == '-' || (char)str[i] == '+')
		if ((char)str[i++] == '-')
			sign++;
	while ((char)str[i] >= '0' && (char)str[i] <= '9')
		nbr = nbr * 10 + ((char)str[i++] - '0');
	if (sign % 2 == 1)
		return (nbr * -1);
	return (nbr);
}
