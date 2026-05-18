/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kstrcat_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:13:52 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:04:18 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std/std.h"

char	*kstrcpy(char *dest, char *src)
{
	uint32_t	i;

	i = 0;
	while (*src != '\0')
	{
		dest[i] = *src;
		src++;
		i++;
	}
	while (dest[i])
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*kstrcat(char *dest, char *src)
{
	kstrcpy(dest + kstrlen(dest), src);
	return (dest);
}
