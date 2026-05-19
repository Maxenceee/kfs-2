/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkstrdup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:58:11 by mgama             #+#    #+#             */
/*   Updated: 2026/05/19 10:58:12 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "io/print/print.h"

char	*pkstrdup(const char *src)
{
	char	*str;
	int		i;

	if (!src)
		return (NULL);
	i = kstrlen(src);
	str = __printk_alloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	kmemcpy(str, src, i);
	kmemset(str + i, '\0', sizeof(char));
	return (str);
}
