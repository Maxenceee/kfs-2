/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:04:23 by mgama             #+#    #+#             */
/*   Updated: 2026/05/18 14:48:30 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "_kshell.h"
#include "std/std.h"
#include "io/print/print.h"
#include "booting/booting.h"

#define X(cmd) DECLARE_SHCMD(cmd),
struct command avail_commands[] = {
	COMMAND_LIST
};
#undef X

const size_t avail_commands_count = sizeof(avail_commands) / sizeof(avail_commands[0]);

uint8_t
find_first(const char *str, char c)
{
	for (size_t i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == c)
			return (i);
	}
	return (INT8_MAX);
}

void __dead2
kernel_shell(void)
{
	printk(SHPROMPT);

	char shell_buffer[256];

	while(1)
	{
		uint8_t prompt_len = kbd_read(shell_buffer, sizeof(shell_buffer));
		if (prompt_len == 0)
		{
			printk(SHPROMPT);
			continue;
		}

		uint8_t first_word = find_first(shell_buffer, ' ');
		char command_name[first_word];
		kmemcpy(command_name, shell_buffer, first_word);
		command_name[first_word] = '\0';
		char *args = shell_buffer + first_word + 1;

		int found_command = 0;
		for (size_t i = 0; i < avail_commands_count; i++)
		{
			if (kstrcmp(command_name, avail_commands[i].name) == 0)
			{
				void (*command_func)(const char *) = avail_commands[i].func;
				if (command_func)
				{
					command_func(args);
				}
				found_command = 1;
				break;
			}
		}
		if (!found_command)
		{
			printk("Unknown command: %s\n", command_name);
		}

		printk(SHPROMPT);
	}
}
