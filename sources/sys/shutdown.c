/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:26:29 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 16:35:14 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/print/print.h"
#include "io/io.h"
#include "timer/delay.h"

void
kshutdown(void)
{
	printk("The kernel will shut down in 1 second...\n");
	ksleep(1000);

	// This command works on QEMU if you launched it with the correct arguments
	// It sends 0x2000 (success value) to port 0x604 (QEMU/Bochs shutdown port)
	outw(0x604, 0x2000);

	// Legacy method for older QEMU versions and Bochs, sending 0x2000 to port 0xB004
	outw(0xB004, 0x2000);

	printk("\nShutdown failed. You can safely turn off your computer.");
	while(1)
	{
		__asm__("hlt");
	}
}