/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:13:27 by mgama             #+#    #+#             */
/*   Updated: 2026/05/17 18:36:34 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "io/print/print.h"
#include "sys/sys.h"
#include "io/screen/screen.h"

extern char keyboard_buffer[80];
extern uint8_t keyboard_buffer_index;
extern volatile uint8_t command_ready;

int
ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	print_help(void);

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
};

void
print_help(void)
{
	printk("Commands:\n");
	for (size_t i = 0; i < sizeof(avail_commands) / sizeof(avail_commands[0]); i++)
	{
		printk("- %s\n", avail_commands[i].name);
	}
}

void __dead2
kernel_shell(void)
{
	printk("OS Shell> ");

	while(1)
	{
		if (command_ready)
		{
			int found_command = 0;
			for (size_t i = 0; i < sizeof(avail_commands) / sizeof(avail_commands[0]); i++)
			{
				if (ft_strcmp(keyboard_buffer, avail_commands[i].name) == 0)
				{
					avail_commands[i].func();
					found_command = 1;
					break;
				}
			}
			if (!found_command)
			{
				printk("Unknown command: %s\n", keyboard_buffer);
			}

			command_ready = 0;
			printk("OS Shell> ");
		}
		
		__asm__ volatile("hlt"); 
	}
}
