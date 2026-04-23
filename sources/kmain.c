/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:23:35 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 15:54:43 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/screen/screen.h"
#include "timer/delay.h"
#include "io/print/print.h"

extern void	kernel_shell(void);

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

	ksleep(1500);

	disable_cursor();
	vga_clear_screen();
	print_logo();

	ksleep(2500);
	vga_clear_screen();
	enable_cursor(14, 15);
}

void
_stack_grow_2(int a, int b, int c, int d, int e)
{
	int ab = a + b;
	int cd = c + d;
	int abcde = ab + cd + e;
	printk("Stack growth test: %d\n", abcde);
	kstackdump();
}

void
_stack_grow_1(void)
{
	uint16_t buffer[256];
	for (int i = 0; i < 256; i++)
		buffer[i] = i;
	
	_stack_grow_2(1, 2, 3, 4, 5);
	buffer[0] = 42;
	printk("Buffer[0] after stack growth: %d\n", buffer[0]);
}

int
kmain(void)
{
	ksetup();

	printk("Welcome to KFS%d!\n", 2);

	// ksleep(1500);

	// _stack_grow_1();

	kernel_shell();

	return (0);
}
