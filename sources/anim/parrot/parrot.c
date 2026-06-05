/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parrot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 14:58:26 by mgama             #+#    #+#             */
/*   Updated: 2026/06/05 14:58:27 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "booting/booting.h"
#include "std/std.h"
#include "io/screen/screen.h"
#include "timer/delay.h"
#include "parrot_frames.h"

static uint16_t back_buffer[VGA_HEIGHT * VGA_WIDTH];

void run_parrot(int loops)
{
	vga_clear_screen();
	disable_cursor();

	uint16_t blank_char = (uint16_t)(' ' | ((VGA_BACK_BLACK | VGA_FORE_WHITE) << 8));
	volatile uint16_t *vga_hardware = (uint16_t *)VGA_TEXT_BUFFER;

	int start_y = (VGA_HEIGHT - PARROT_HEIGHT) / 2;
	int start_x = (VGA_WIDTH - PARROT_WIDTH) / 2;

	for (int l = 0; l < loops || loops == -1; ++l)
	{
		for (int frame = 0; frame < PARROT_FRAME_COUNT; ++frame)
		{
			for (int idx = 0; idx < VGA_HEIGHT * VGA_WIDTH; idx++)
			{
				back_buffer[idx] = blank_char;
			}

			for (int y = 0; y < PARROT_HEIGHT; ++y)
			{
				int target_y = start_y + y;
				if (target_y < 0 || target_y >= VGA_HEIGHT)
					continue;

				for (int x = 0; x < PARROT_WIDTH; ++x)
				{
					int target_x = start_x + x;
					if (target_x >= 0 && target_x < VGA_WIDTH)
					{
						back_buffer[target_y * VGA_WIDTH + target_x] = parrot_frames[frame][y][x];
					}
				}
			}

			kmemcpy((void *)vga_hardware, back_buffer, sizeof(back_buffer));

			if (kbd_getc_nonblock() == 'q')
			{
				goto end;
			}

			kmsleep(65);
		}
	}

end:
	vga_clear_screen();
	enable_cursor(14, 15);
}
