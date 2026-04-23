/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kslepp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:23:02 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 14:32:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "time.h"

void
ksleep(uint32_t ms)
{
	uint32_t delay_jiffies = (ms * HZ) / 1000;
	uint32_t end = jiffies + delay_jiffies;

	while (jiffies < end)
	{
		asm volatile("hlt"); 
	}
}
