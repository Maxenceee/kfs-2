/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _irq_kbd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:22:10 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 16:02:26 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/print/print.h"
#include "io/io.h"
#include "io/ps2/PS2KeyAdvanced.h"
#include "io/ps2/PS2KeyMap.h"

PS2KeyMap g_keymap;
static uint16_t g_current_modifiers = 0;

char keyboard_buffer[80];
uint8_t keyboard_buffer_index = 0;
volatile uint8_t command_ready = 0;

void
_irq_kbd_handler(void)
{
	uint8_t scancode = inb(0x60);

	uint8_t is_break = (scancode & 0x80);
	uint8_t key = (scancode & 0x7F);

	if (key == 0x2A || key == 0x36) {
		if (is_break) g_current_modifiers &= ~PS2_SHIFT;
		else g_current_modifiers |= PS2_SHIFT;
		return; 
	}
	if (!is_break)
	{
		// printk("Scancode: 0x%02X key=0x%02X\n", scancode, key);
		uint8_t ascii = PS2KeyMap_remapKeyByte(&g_keymap, scancode);

		if (ascii != 0) {
			printk("%c", ascii);
		}
	}
}
