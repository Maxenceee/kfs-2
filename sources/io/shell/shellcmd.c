/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:53:45 by mgama             #+#    #+#             */
/*   Updated: 2026/05/18 14:47:30 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "_kshell.h"
#include "sys/sys.h"
#include "io/screen/screen.h"
#include "io/print/print.h"

EXPORT_SHCMD(help)
{
	printk("Available commands:\n");
    for (size_t i = 0; i < avail_commands_count; i++)
    {
        printk("  - %s\n", avail_commands[i].name);
    }
}

EXPORT_SHCMD(clear)
{
	vga_clear_screen();
}

EXPORT_SHCMD(reboot)
{
	kreboot();
}

EXPORT_SHCMD(shutdown)
{
	kshutdown();
}

EXPORT_SHCMD(dump)
{
	kstackdump();
}

EXPORT_SHCMD(fdump)
{
	uint16_t buffer[16];
	for (int i = 0; i < 16; i++)
		buffer[i] = i;

	buffer[0] = 42;
	printk("Buffer[0] after stack growth: %d\n", buffer[0]);
	kstackdump();
}

EXPORT_SHCMD(echo)
{
	printk("%s\n", args);
}
