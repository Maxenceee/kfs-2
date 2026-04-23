/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _irq_kbd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:22:10 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 16:46:52 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/print/print.h"
#include "io/io.h"

char keyboard_buffer[80];
uint8_t keyboard_buffer_index = 0;
volatile uint8_t command_ready = 0;
volatile uint8_t is_shift_pressed = 0;

static const char qwerty_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 0x00 - 0x09 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter */
    0,			/* 0x1D - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, /* Left Shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, /* Right Shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
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
_irq_kbd_handler(void)
{
    uint8_t scancode = inb(0x60);

    if (scancode & 0x80)
	{
        uint8_t released_code = scancode & 0x7F;
        if (released_code == 0x2A || released_code == 0x36) is_shift_pressed = 0;
        return;
    }

    if (scancode == 0x2A || scancode == 0x36)
	{
        is_shift_pressed = 1;
        return;
    }

    char ascii = qwerty_map[scancode];

    if (ascii != 0)
	{
        if (is_shift_pressed && ascii >= 'a' && ascii <= 'z')
		{
            ascii -= 32;
        }

        if (ascii == '\n')
		{
            keyboard_buffer[keyboard_buffer_index] = '\0';
            command_ready = 1;
            keyboard_buffer_index = 0;
            printk("\n");
        } 
        else if (ascii == '\b')
		{
            if (keyboard_buffer_index > 0)
			{
                keyboard_buffer_index--;
                printk("\b \b");
            }
        } 
        else
		{
            if (keyboard_buffer_index < 79)
			{
                keyboard_buffer[keyboard_buffer_index++] = ascii;
                printk("%c", ascii);
            }
        }
    }
}