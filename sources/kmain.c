/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:23:35 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:59:39 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "screen.h"
#include "delay.h"
#include "print.h"

void
print_logo()
{
	printk("\n\n\n\n\n\n\n\n");

    const char* logo =
    "                           ____       _ _ _             \n"
    "                          / ___|__ __| (_) | ___  ___   \n"
    "                         | |  _/ _`  | | | |/ _ \\/ _ \\  \n"
    "                         | |_| | (_| | | | |  __/ (_) | \n"
    "                          \\____|\\__,_|_|_|_|\\___|\\___/  \n"
    "                                                       \n"
    "                            Kernel Project by mgama\n";

    cprintk(VGA_FORE_CYAN | VGA_BACK_BLACK, "%s", logo);
}

void
ksetup(void)
{
	vga_init();

	ksleep(500);

	disable_cursor();
	vga_clear_screen();
	print_logo();

	ksleep(1000);
	vga_clear_screen();
	enable_cursor(14, 15);
}

void
_stack_grow(const char *str, int max)
{
	if (max <= 0)
	{
		kstackdump();
		return;
	}

	_stack_grow(str, max - 1);
	printk("%c", str[max - 1]);
}

int
kmain(void)
{
	ksetup();

	printk("Welcome to KFS%d!\n", 2);

	_stack_grow("Stack growth test.", 19);

	return (0);
}
