/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:26:25 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 12:25:44 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_H
#define SCREEN_H

#include <types.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_TEXT_BUFFER 0xb8000u

extern uint16_t cursor_pos;

#define VGA_FORE_BLACK			0x0
#define VGA_FORE_BLUE			0x1
#define VGA_FORE_GREEN			0x2
#define VGA_FORE_CYAN			0x3
#define VGA_FORE_RED			0x4
#define VGA_FORE_MAGENTA		0x5
#define VGA_FORE_BROWN			0x6
#define VGA_FORE_LIGHT_GREY		0x7
#define VGA_FORE_DARK_GREY		0x8
#define VGA_FORE_LIGHT_BLUE		0x9
#define VGA_FORE_LIGHT_GREEN	0xA
#define VGA_FORE_LIGHT_CYAN		0xB
#define VGA_FORE_LIGHT_RED		0xC
#define VGA_FORE_LIGHT_MAGENTA	0xD
#define VGA_FORE_LIGHT_BROWN	0xE
#define VGA_FORE_WHITE			0xF

#define VGA_BACK_BLACK			(VGA_FORE_BLACK << 4)
#define VGA_BACK_BLUE			(VGA_FORE_BLUE << 4)
#define VGA_BACK_GREEN			(VGA_FORE_GREEN << 4)
#define VGA_BACK_CYAN			(VGA_FORE_CYAN << 4)
#define VGA_BACK_RED			(VGA_FORE_RED << 4)
#define VGA_BACK_MAGENTA		(VGA_FORE_MAGENTA << 4)
#define VGA_BACK_BROWN			(VGA_FORE_BROWN << 4)
#define VGA_BACK_LIGHT_GREY		(VGA_FORE_LIGHT_GREY << 4)
#define VGA_BACK_DARK_GREY		(VGA_FORE_DARK_GREY << 4)
#define VGA_BACK_LIGHT_BLUE		(VGA_FORE_LIGHT_BLUE << 4)
#define VGA_BACK_LIGHT_GREEN	(VGA_FORE_LIGHT_GREEN << 4)
#define VGA_BACK_LIGHT_CYAN		(VGA_FORE_LIGHT_CYAN << 4)
#define VGA_BACK_LIGHT_RED		(VGA_FORE_LIGHT_RED << 4)
#define VGA_BACK_LIGHT_MAGENTA	(VGA_FORE_LIGHT_MAGENTA << 4)
#define VGA_BACK_LIGHT_BROWN	(VGA_FORE_LIGHT_BROWN << 4)
#define VGA_BACK_WHITE			(VGA_FORE_WHITE << 4)

void	vga_init(void);
void	vga_put(const char c, uint8_t attrib);
void	vga_puts(const char *str, uint32_t len, uint8_t attrib);
void	vga_clear_screen(void);
void	vga_scroll_screen(void);

void		enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void		move_cursor(uint16_t pos);
void		disable_cursor(void);
void		enable_cursor_blinking(void);
void		set_cursor_shape(uint8_t cursor_start, uint8_t cursor_end);
uint16_t	get_cursor_position(void);

#endif /* SCREEN_H */