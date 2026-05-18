/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:04:23 by mgama             #+#    #+#             */
/*   Updated: 2026/05/18 12:14:04 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "io/print/print.h"
#include "sys/sys.h"
#include "std/std.h"
#include "io/screen/screen.h"

uint8_t	kbd_read(char *buffer, uint8_t max_length);

#define SHPROMPT "OS Shell> "

void	print_help(void);

void
_stack_grow_fake(void)
{
	uint16_t buffer[16];
	for (int i = 0; i < 16; i++)
		buffer[i] = i;

	buffer[0] = 42;
	printk("Buffer[0] after stack growth: %d\n", buffer[0]);
	kstackdump();
}

struct command
{
	char *name;
	void (*func)(void);
} avail_commands[] = {
	{"help", &print_help},
	{"clear", &vga_clear_screen},
	{"reboot", &kreboot},
	{"shutdown", &kshutdown},
	{"dump", &kstackdump},
	{"fdump", &_stack_grow_fake},
};

void
print_help(void)
{
	printk("Available commands:\n");
	for (size_t i = 0; i < sizeof(avail_commands) / sizeof(avail_commands[0]); i++)
	{
		printk("  - %s\n", avail_commands[i].name);
	}
}

void __dead2
kernel_shell(void)
{
	printk(SHPROMPT);

	char shell_buffer[80];

	while(1)
	{
		uint8_t prompt_len = kbd_read(shell_buffer, sizeof(shell_buffer));
		if (prompt_len == 0)
		{
			printk(SHPROMPT);
			continue;
		}

		int found_command = 0;
		for (size_t i = 0; i < sizeof(avail_commands) / sizeof(avail_commands[0]); i++)
		{
			if (kstrcmp(shell_buffer, avail_commands[i].name) == 0)
			{
				void (*command_func)(void) = avail_commands[i].func;
				if (command_func)
				{
					command_func();
				}
				found_command = 1;
				break;
			}
		}
		if (!found_command)
		{
			printk("Unknown command: %s\n", shell_buffer);
		}

		printk(SHPROMPT);
	}
}
