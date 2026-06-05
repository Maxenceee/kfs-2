/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irq_kbd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:04:55 by mgama             #+#    #+#             */
/*   Updated: 2026/06/05 15:59:09 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/io.h"
#include "io/print/print.h"
#include "std/std.h"
#include "io/screen/screen.h"

#define KBD_BUFFER_SIZE 256
static char irq_kbd_buffer[KBD_BUFFER_SIZE];
volatile uint8_t irq_kbd_buffer_index = 0;
volatile uint8_t irq_kbd_cursor_offset = 0;
volatile uint8_t irq_kbd_command_ready = 0;
volatile uint8_t irq_kbd_is_shift_pressed = 0;

volatile int irq_kbd_enabled = 0;
volatile int irq_kdb_extended = 0;

static uint16_t prompt_start_cursor_pos = 0;

volatile char kbd_last_pressed_char = 0;

static const char irq_kbd_qwerty_map[128] = {
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 0x00 - 0x09 */
	'9', '0', '-', '=', '\b',   /* Backspace */
	'\t',           /* Tab */
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter */
	0,          /* 0x1D - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, /* Left Shift */
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, /* Right Shift */
	'*',
	0,		/* Alt */
	' ',	/* Space bar */
	0,		/* Caps lock */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* F1 - F10 */
	0,	/* Num lock */
	0,	/* Scroll lock */
	0,	/* Home key */
	0,	/* Up arrow */
	0,	/* Page up */
	'-',
	0,	/* Left arrow */
	0,
	0,	/* Right arrow */
	'+',
	0,	/* End key */
	0,	/* Down arrow */
	0,	/* Page down */
	0,	/* Insert key */
	0,	/* Delete key */
	0, 0, 0,
	0,	/* F11 key */
	0,	/* F12 key */
	0,	/* All others undefined */
};

static const char irq_kbd_qwerty_shift_map[128] = {
	0,  27, '!', '@', '#', '$', '%', '^', '&', '*', /* 0x00 - 0x09 */
	'(', ')', '_', '+', '\b',   /* Backspace */
	'\t',           /* Tab */
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', /* Enter */
	0,          /* Control */
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, /* Left Shift */
	'|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, /* Right Shift */
	'*',
	0,		/* Alt */
	' ',	/* Space bar */
	0,		/* Caps lock */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* F1 - F10 */
	0,	/* Num lock */
	0,	/* Scroll lock */
	0,	/* Home key */
	0,	/* Up arrow */
	0,	/* Page up */
	'-',
	0,	/* Left arrow */
	0,
	0,	/* Right arrow */
	'+',
	0,	/* End key */
	0,	/* Down arrow */
	0,	/* Page down */
	0,	/* Insert key */
	0,	/* Delete key */
	0, 0, 0,
	0,	/* F11 key */
	0,	/* F12 key */
	0,	/* All others undefined */
};

void
kbd_enable(void)
{
	irq_kbd_enabled = 1;
}

void
kbd_disable(void)
{
	irq_kbd_enabled = 0;
}

char
kbd_getc_nonblock(void)
{
	char c = kbd_last_pressed_char;
	kbd_last_pressed_char = 0;
	return c;
}

static void
refresh_tail(void)
{
	uint16_t saved_cursor = cursor_pos;

	for (uint8_t i = irq_kbd_cursor_offset; i < irq_kbd_buffer_index; i++)
	{
		printk("%c", irq_kbd_buffer[i]);
	}
	printk(" ");

	cursor_pos = saved_cursor;
	move_cursor(cursor_pos);
}

void
_irq_kbd_handler(void)
{
	uint8_t scancode = inb(0x60);

	if (scancode == 0xE0)
	{
		irq_kdb_extended = 1;
		return;
	}

	if (scancode & 0x80)
	{
		uint8_t released_code = scancode & 0x7F;
		if (released_code == 0x2A || released_code == 0x36)
			irq_kbd_is_shift_pressed = 0;

		return;
	}

	if (scancode == 0x2A || scancode == 0x36)
	{
		irq_kbd_is_shift_pressed = 1;
		return;
	}

	char ascii = irq_kbd_is_shift_pressed ? irq_kbd_qwerty_shift_map[scancode] : irq_kbd_qwerty_map[scancode];

	if (ascii != 0)
	{
		kbd_last_pressed_char = ascii;
	}

	if (!irq_kbd_enabled)
	{
		return;
	}

	if (irq_kdb_extended)
	{
		irq_kdb_extended = 0;

		if (scancode & 0x80)
		{
			return;
		}

		switch (scancode)
		{
			case 0x49: // Page Up
				vga_scroll_up();
				break;

			case 0x51: // Page Down
				vga_scroll_down();
				break;
			case 0x48: // Flèche Haut
				break;
			case 0x50: // Flèche Bas
				break;
			case 0x4B: // Flèche Gauche
				if (irq_kbd_cursor_offset > 0)
				{
					irq_kbd_cursor_offset--;
					cursor_pos--;
					move_cursor(cursor_pos);
				}
				break;
			case 0x4D: // Flèche Droite
				if (irq_kbd_cursor_offset < irq_kbd_buffer_index)
				{
					irq_kbd_cursor_offset++;
					cursor_pos++;
					move_cursor(cursor_pos);
				}
				break;
			default:
				break;
		}
		return;
	}

	if (irq_kbd_command_ready)
	{
		return;
	}

	if (ascii != 0)
	{
		if (ascii == '\n')
		{
			irq_kbd_buffer[irq_kbd_buffer_index] = '\0';
			irq_kbd_command_ready = 1;
			printk("\n");
		} 
		else if (ascii == '\b')
		{
			if (irq_kbd_cursor_offset > 0)
			{
				for (uint8_t i = irq_kbd_cursor_offset - 1; i < irq_kbd_buffer_index - 1; i++)
				{
					irq_kbd_buffer[i] = irq_kbd_buffer[i + 1];
				}
				irq_kbd_buffer_index--;
				irq_kbd_cursor_offset--;

				cursor_pos--;
				move_cursor(cursor_pos);
				refresh_tail();
			}
		} 
		else
		{
			if (irq_kbd_buffer_index < KBD_BUFFER_SIZE - 1) // Prevent overflow
			{
				for (uint8_t i = irq_kbd_buffer_index; i > irq_kbd_cursor_offset; i--)
				{
					irq_kbd_buffer[i] = irq_kbd_buffer[i - 1];
				}

				irq_kbd_buffer[irq_kbd_cursor_offset] = ascii;
				irq_kbd_buffer_index++;

				printk("%c", ascii);
				irq_kbd_cursor_offset++;

				if (irq_kbd_cursor_offset < irq_kbd_buffer_index)
				{
					refresh_tail();
				}
			}
		}
	}
}

size_t
kbd_read(char *buffer, size_t max_length)
{
	prompt_start_cursor_pos = cursor_pos;
	irq_kbd_buffer_index = 0;
	irq_kbd_cursor_offset = 0;

	kbd_enable();
	while (!irq_kbd_command_ready)
	{
		__asm__ volatile ("hlt");
	}

	const size_t length_to_copy = kmin(irq_kbd_buffer_index, max_length - 1);

	kmemcpy(buffer, irq_kbd_buffer, length_to_copy);
	buffer[length_to_copy] = '\0';

	irq_kbd_buffer_index = 0;
	irq_kbd_cursor_offset = 0;
	irq_kbd_command_ready = 0;

	kbd_disable();
	return length_to_copy;
}
