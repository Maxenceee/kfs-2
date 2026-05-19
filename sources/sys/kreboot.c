/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kreboot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:03:57 by mgama             #+#    #+#             */
/*   Updated: 2026/05/19 10:39:10 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/print/print.h"
#include "timer/delay.h"

void
kreboot(void)
{
	uint8_t timer = 3;
	while (timer > 0)
	{
		printk("The kernel will reboot in %ds...\r", timer);
		ksleep(1000);
		timer--;
	}
	printk("\nRebooting...\n");

	// This is a common method to trigger a reboot by causing a triple fault,
	// which forces the CPU to reset.
	__asm__ volatile (
        "lidt (%0) \n"
        "int $3"
        : : "r" (0)
    );
}
