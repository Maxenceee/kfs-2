/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:53:45 by mgama             #+#    #+#             */
/*   Updated: 2026/06/10 17:45:32 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "uname.h"
#include "_kshell.h"
#include "sys/sys.h"
#include "std/std.h"
#include "timer/delay.h"
#include "io/screen/screen.h"
#include "io/print/print.h"
#include "anim/sl/sl.h"
#include "anim/anim.h"

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

EXPORT_SHCMD(uname)
{
	int show_sysname = 0;
	int show_release = 0;
	int show_machine = 0;
	int show_date    = 0;

	if (!args || args[0] == '\0')
	{
		show_sysname = 1;
	}
	else
	{
		for (int i = 0; args[i] != '\0'; i++)
		{
			if (args[i] == ' ' || args[i] == '-')
			{
				continue;
			}

			switch (args[i])
			{
				case 'a':
					show_sysname = 1;
					show_release = 1;
					show_machine = 1;
					show_date    = 1;
					break;
				case 's': show_sysname = 1; break;
				case 'r': show_release = 1; break;
				case 'm': show_machine = 1; break;
				case 'v': show_date = 1;    break;
				default:
					printk("uname: option invalide -- '%c'\n", args[i]);
					return;
			}
		}
	}

	int need_space = 0;

	if (show_sysname)
	{
		printk("%s", kuname.sysname);
		need_space = 1;
	}
	if (show_release)
	{
		if (need_space) printk(" ");
		printk("%s", kuname.release);
		need_space = 1;
	}
	if (show_date)
	{
		if (need_space) printk(" ");
		printk("%s", kuname.date);
		need_space = 1;
	}
	if (show_machine)
	{
		if (need_space) printk(" ");
		printk("%s", kuname.machine);
	}

	printk("\n");
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

EXPORT_SHCMD(sl)
{
	run_sl(args);
}

EXPORT_SHCMD(parrot)
{
	run_parrot(-1);
}

EXPORT_SHCMD(knot)
{
	run_knot(-1);
}

EXPORT_SHCMD(nyan)
{
	run_nyan(-1);
}

EXPORT_SHCMD(bomb)
{
	run_bomb(1);
}
