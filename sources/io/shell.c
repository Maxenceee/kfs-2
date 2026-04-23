/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:13:27 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 16:30:08 by mgama            ###   ########.fr       */
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

void __dead2
kernel_shell(void)
{
	printk("OS Shell> ");

	while(1)
	{
		if (command_ready)
		{
			if (ft_strcmp(keyboard_buffer, "help") == 0)
			{
				printk("Commands: help, clear, reboot, shutdown\n");
			} 
			else if (ft_strcmp(keyboard_buffer, "clear") == 0)
			{
				vga_clear_screen();
			}
			else if (ft_strcmp(keyboard_buffer, "reboot") == 0)
			{
				reboot();
			}
			else if (ft_strcmp(keyboard_buffer, "shutdown") == 0)
			{
				shutdown();
			}
			else
			{
				printk("Unknown command: %s\n", keyboard_buffer);
			}

			command_ready = 0;
			printk("OS Shell> ");
		}
		
		__asm__ volatile("hlt"); 
	}
}