/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:38:22 by mgama             #+#    #+#             */
/*   Updated: 2026/05/19 10:38:23 by mgama            ###   ########.fr       */
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
