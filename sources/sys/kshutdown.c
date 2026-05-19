/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kshutdown.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:03:50 by mgama             #+#    #+#             */
/*   Updated: 2026/05/19 11:22:36 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/print/print.h"
#include "io/io.h"
#include "timer/delay.h"

void
kshutdown(void)
{
	uint8_t timer = 3;
	while (timer > 0)
	{
		printk("The kernel will shut down in %ds...\r", timer);
		kmsleep(1000);
		timer--;
	}
	printk("\nShutting down...\n");

	// This command works on QEMU and Bochs to trigger a shutdown.
	// It sends 0x2000 (success value) to port 0x604 (QEMU/Bochs shutdown port)
	outw(0x604, 0x2000);

	// Legacy method for older QEMU versions and Bochs, sending 0x2000 to port 0xB004
	outw(0xB004, 0x2000);

	printk("\nShutdown failed. You can safely turn off your computer.");
	while(1)
	{
		__asm__ volatile ("hlt");
	}
}
