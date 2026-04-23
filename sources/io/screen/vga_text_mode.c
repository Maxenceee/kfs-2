/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:26:04 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 15:28:57 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/screen/screen.h"
#include "timer/delay.h"

uint16_t cursor_pos = 0;

void
vga_init(void)
{
	cursor_pos = get_cursor_position();
}

void
vga_clear_screen(void)
{
	for (int i = 0; i < VGA_HEIGHT; i++)
	{
		vga_scroll_screen();
	}
	cursor_pos = 0;
	move_cursor(cursor_pos);
}

void
vga_put(const char c, uint8_t attrib)
{
	volatile uint16_t *buffer = (uint16_t *)VGA_TEXT_BUFFER;

    switch (c)
    {
        case '\n':
            cursor_pos += VGA_WIDTH - (cursor_pos % VGA_WIDTH);
            break;

        case '\r':
            cursor_pos -= (cursor_pos % VGA_WIDTH);
            break;

        case '\t':
            cursor_pos = (cursor_pos + 8) & ~(8 - 1);
            break;

        case '\b':
            if (cursor_pos > 0)
            {
                cursor_pos--;
                buffer[cursor_pos] = (uint16_t)((attrib << 8) | ' ');
            }
            break;

        default:
            buffer[cursor_pos] = (uint16_t)((attrib << 8) | c);
            cursor_pos++;
            break;
    }

    if (cursor_pos >= VGA_WIDTH * VGA_HEIGHT)
    {
        vga_scroll_screen();
        cursor_pos = (VGA_HEIGHT - 1) * VGA_WIDTH;
    }
    
    move_cursor(cursor_pos);
}

void
vga_puts(const char *str, uint32_t len, uint8_t attrib)
{
	for (uint32_t i = 0; i < len; i++)
	{
		vga_put(str[i], attrib);
	}
}

void
vga_scroll_screen(void)
{
	volatile uint16_t *buffer = (uint16_t *)VGA_TEXT_BUFFER;

	for (int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++)
	{
		buffer[i] = buffer[i + VGA_WIDTH];
	}

	for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < VGA_HEIGHT * VGA_WIDTH; i++)
	{
		buffer[i] = 0x0F00;
	}
}
