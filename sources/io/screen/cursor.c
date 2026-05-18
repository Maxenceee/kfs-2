/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:04:43 by mgama             #+#    #+#             */
/*   Updated: 2026/05/18 11:04:44 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/screen/screen.h"
#include "io/io.h"

void
enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, cursor_end);
}

void
move_cursor(uint16_t pos)
{
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void
disable_cursor(void)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, inb(0x3D5) | 0x20);
}

void
enable_cursor_blinking(void)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, inb(0x3D5) & ~0x20);
}

void
set_cursor_shape(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

uint16_t
get_cursor_position(void)
{
	outb(0x3D4, 0x0F);
	uint8_t low = inb(0x3D5);
	outb(0x3D4, 0x0E);
	uint8_t high = inb(0x3D5);

	return (high << 8) | low;
}
