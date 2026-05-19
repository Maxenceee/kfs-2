/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:53:45 by mgama             #+#    #+#             */
/*   Updated: 2026/05/19 11:39:15 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "_kshell.h"
#include "sys/sys.h"
#include "std/std.h"
#include "timer/delay.h"
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

EXPORT_SHCMD(echo)
{
	printk("%s\n", args);
}

EXPORT_SHCMD(sleep)
{
	int s = katoi(args);
	if (s <= 0)
	{
		printk("Usage: sleep <seconds>\n");
		return;
	}

	ksleep(s);
}
