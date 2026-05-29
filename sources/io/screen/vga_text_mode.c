/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vga_text_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:04:34 by mgama             #+#    #+#             */
/*   Updated: 2026/05/18 14:55:18 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/screen/screen.h"
#include "timer/delay.h"

static uint16_t vga_history[VGA_HISTORY_LINES][VGA_WIDTH];
static int history_total_lines = VGA_HEIGHT;
static int scroll_offset = 0;

uint16_t cursor_pos = 0;

void
vga_init(void)
{
	uint16_t clear_val = (uint16_t)(' ' | ((VGA_BACK_BLACK | VGA_FORE_WHITE) << 8));
    for (int y = 0; y < VGA_HISTORY_LINES; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            vga_history[y][x] = clear_val;
        }
    }
    cursor_pos = get_cursor_position();
}

static void
vga_flush(void)
{
    volatile uint16_t *vga_hardware = (uint16_t *)VGA_TEXT_BUFFER;

    int start_line = history_total_lines - VGA_HEIGHT - scroll_offset;
    if (start_line < 0)
        start_line = 0;

    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        int current_history_line = start_line + y;
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            vga_hardware[y * VGA_WIDTH + x] = vga_history[current_history_line][x];
        }
    }

    if (scroll_offset == 0)
    {
        move_cursor(cursor_pos);
    }
    else
    {
        move_cursor(VGA_WIDTH * VGA_HEIGHT);
    }
}

void
vga_clear_screen(void)
{
	uint16_t clear_val = (uint16_t)(' ' | ((VGA_BACK_BLACK | VGA_FORE_WHITE) << 8));

    for (int y = 0; y < VGA_HISTORY_LINES; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            vga_history[y][x] = clear_val;
        }
    }

    history_total_lines = VGA_HEIGHT;
    scroll_offset = 0;
    cursor_pos = 0;
    vga_flush();
}

static void
vga_scroll_screen(void)
{
	uint16_t clear_val = (uint16_t)(' ' | ((VGA_BACK_BLACK | VGA_FORE_WHITE) << 8));

	if (history_total_lines < VGA_HISTORY_LINES)
    {
        history_total_lines++;
    }
    else
    {
        for (int y = 0; y < VGA_HISTORY_LINES - 1; y++)
        {
            for (int x = 0; x < VGA_WIDTH; x++)
            {
                vga_history[y][x] = vga_history[y + 1][x];
            }
        }

        for (int x = 0; x < VGA_WIDTH; x++)
        {
            vga_history[VGA_HISTORY_LINES - 1][x] = clear_val;
        }
    }
}

void
vga_put(const char c, uint8_t attrib)
{
	if (scroll_offset != 0)
    {
        scroll_offset = 0;
    }

    int current_line = (history_total_lines - VGA_HEIGHT) + (cursor_pos / VGA_WIDTH);

    switch (c)
    {
        case '\n':
            cursor_pos += VGA_WIDTH - (cursor_pos % VGA_WIDTH);
            break;

        case '\r':
            cursor_pos -= (cursor_pos % VGA_WIDTH);
            break;

        case '\t':
            // cursor_pos = (cursor_pos + 8) & ~(8 - 1);
            cursor_pos++;
            break;

        case '\b':
            if (cursor_pos > 0)
            {
                cursor_pos--;
                vga_history[current_line][cursor_pos % VGA_WIDTH] = (uint16_t)((attrib << 8) | ' ');
            }
            break;

        default:
            vga_history[current_line][cursor_pos % VGA_WIDTH] = (uint16_t)((attrib << 8) | c);
            cursor_pos++;
            break;
    }

    if (cursor_pos >= VGA_WIDTH * VGA_HEIGHT)
    {
        vga_scroll_screen();
        cursor_pos = (VGA_HEIGHT - 1) * VGA_WIDTH;
    }

    vga_flush();
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
vga_scroll_up(void)
{
    if (scroll_offset < (history_total_lines - VGA_HEIGHT))
    {
        scroll_offset++;
        vga_flush();
    }
}

void
vga_scroll_down(void)
{
    if (scroll_offset > 0)
    {
        scroll_offset--;
        vga_flush();
    }
}
