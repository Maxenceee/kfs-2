/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:26:04 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 12:34:14 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "screen.h"
#include "delay.h"

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

    if (c == '\n')
    {
        cursor_pos += VGA_WIDTH - (cursor_pos % VGA_WIDTH);
    }
    else
    {
        buffer[cursor_pos] = (uint16_t)((attrib << 8) | c);
        cursor_pos++;
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
