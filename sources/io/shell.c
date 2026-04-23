/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:13:27 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 15:26:43 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "io/print/print.h"
#include "io/screen/screen.h"
#include "io/ps2/PS2KeyMap.h"

extern PS2KeyMap g_keymap;
extern char keyboard_buffer[80];
extern uint8_t keyboard_buffer_index;
extern volatile uint8_t command_ready;

void __dead2
kernel_shell(void)
{
	PS2KeyMap_init(&g_keymap);
	PS2KeyMap_selectMap(&g_keymap, "US");

	printk("Galileo OS ready.\nkfs# ");

	while (1)
	{
		if (command_ready)
		{
			printk("Unknown command: %s\n", keyboard_buffer);

			keyboard_buffer_index = 0;
			command_ready = 0;
			printk("kfs# ");
		}

		asm volatile("hlt");
	}
}