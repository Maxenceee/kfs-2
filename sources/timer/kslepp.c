/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kslepp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:04:07 by mgama             #+#    #+#             */
/*   Updated: 2026/05/19 11:22:55 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "time.h"

void
kmsleep(uint32_t ms)
{
	uint32_t delay_jiffies = (ms * HZ) / 1000;
	uint32_t end = jiffies + delay_jiffies;

	while (jiffies < end)
	{
		__asm__ volatile("hlt"); 
	}
}

void
ksleep(uint32_t s)
{
	uint32_t delay_jiffies = (s * HZ);
	uint32_t end = jiffies + delay_jiffies;

	while (jiffies < end)
	{
		__asm__ volatile("hlt"); 
	}
}
