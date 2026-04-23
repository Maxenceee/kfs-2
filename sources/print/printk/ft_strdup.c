/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:42:36 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:17:21 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

char	*ft_strdup(const char *src)
{
	char	*str;
	int		i;

	if (!src)
		return (NULL);
	i = ft_strlen(src);
	str = __printk_alloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, src, i);
	ft_memset(str + i, '\0', sizeof(char));
	return (str);
}
