/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:48:29 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:09:34 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

void	*ft_memcpy(void *dst, const void *src, uint32_t n)
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

void	*ft_memset(void *b, int c, uint32_t len)
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

void	ft_bzero(void *s, uint32_t n)
{
	ft_memset(s, '\0', n);
}
