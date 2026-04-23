/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _irq_kbd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:22:10 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 14:34:37 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "io.h"

void
_irq_kbd_handler(void)
{
    uint8_t scancode = inb(0x60);

    if (!(scancode & 0x80))
	{
        printk("Keyboard scancode = 0x%x\n", scancode);
    }
}
