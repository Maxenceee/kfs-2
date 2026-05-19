/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:04:23 by mgama             #+#    #+#             */
/*   Updated: 2026/05/19 11:38:44 by mgama            ###   ########.fr       */
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

void __dead2
kernel_shell(void)
{
	printk(SHPROMPT);

	char shell_buffer[256];

	while(1)
	{
		size_t prompt_len = kbd_read(shell_buffer, sizeof(shell_buffer));
		if (prompt_len == 0)
		{
			printk(SHPROMPT);
			continue;
		}

		size_t first_space = 0;
        while (first_space < prompt_len && shell_buffer[first_space] != ' ')
        {
            first_space++;
        }

        char command_name[first_space + 1];
        kmemcpy(command_name, shell_buffer, first_space);
        command_name[first_space] = '\0';

        char *args = "";
        size_t arg_idx = first_space;

        while (arg_idx < prompt_len && shell_buffer[arg_idx] == ' ')
        {
            arg_idx++;
        }

        if (arg_idx < prompt_len && shell_buffer[arg_idx] != '\0')
        {
            args = shell_buffer + arg_idx;
        }

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
