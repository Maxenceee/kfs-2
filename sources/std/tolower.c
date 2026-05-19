/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tolower.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:38:48 by mgama             #+#    #+#             */
/*   Updated: 2026/05/19 10:38:49 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std/std.h"

char	*kstr_tolower(char *str)
{
	uint32_t	i;

	i = -1;
	while (str[++i])
		str[i] = ktolower(str[i]);
	return (str);
}

int	ktolower(int num)
{
	if (num >= 65 && num <= 90)
		num += 32;
	return (num);
}
