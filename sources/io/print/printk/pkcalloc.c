/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkcalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:00:07 by mgama             #+#    #+#             */
/*   Updated: 2026/05/19 11:00:08 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "io/print/print.h"

void	*pkcalloc(uint32_t count, uint32_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	uint32_t total;
    if (__builtin_mul_overflow(count, size, &total))
	{
        return (NULL);
	}
	ptr = __printk_alloc(count * size);
	if (ptr)
		kbzero(ptr, count * size);
	return (ptr);
}
