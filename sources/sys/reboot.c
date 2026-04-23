/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reboot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:23:57 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 16:35:19 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/print/print.h"
#include "timer/delay.h"

void
kreboot(void)
{
	printk("The kernel will reboot in 1 second...\n");
	ksleep(1000);

	// This is a common method to trigger a reboot by causing a triple fault, which forces the CPU to reset.
	__asm__ volatile (
        "lidt (%0) \n"
        "int $3"
        : : "r" (0)
    );
}
