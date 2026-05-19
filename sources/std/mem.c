/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:37:57 by mgama             #+#    #+#             */
/*   Updated: 2026/05/19 10:37:59 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std/std.h"

void	*kmemcpy(void *dst, const void *src, uint32_t n)
{
	uint32_t	i;
	void	*lst_dst;

	if (n == 0 || dst == src)
		return (dst);
	i = 0;
	lst_dst = dst;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (lst_dst);
}

void	*kmemset(void *b, int c, uint32_t len)
{
	uint32_t	i;

	i = 0;
	while (i < len)
	{
		((char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	kbzero(void *s, uint32_t n)
{
	kmemset(s, '\0', n);
}
