/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:42:57 by mgama             #+#    #+#             */
/*   Updated: 2026/05/18 14:15:32 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/screen/screen.h"
#include "timer/delay.h"
#include "io/print/print.h"
#include "io/shell/shell.h"
#include "booting/booting.h"

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
	kbd_enable();
}

int
kmain(void)
{
	ksetup();

	printk("Welcome to KFS%d!\n", 2);

	kernel_shell();

	return (0);
}
