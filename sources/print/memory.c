/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 12:35:15 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 14:05:53 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

extern uint32_t stack_space;

static inline uint32_t
get_esp(void)
{
	uint32_t esp;
	asm volatile("mov %%esp, %0" : "=r"(esp));

	return esp;
}

void
kstackdump(void)
{
	uint32_t esp = get_esp();
	uint32_t stack_base = (uint32_t)&stack_space;
	uint32_t diff = stack_base - esp;

	uint32_t nb_words = (diff + 3) / sizeof(uint32_t);
	uint32_t *ptr = (uint32_t *)esp;

	printk("\n=== STACK DUMP | ESP: %p | SIZE: %d ===", esp, diff);

	for (uint32_t i = 0; i < nb_words; i += 4)
	{
		printk("\n%p: ", (uint32_t)(ptr + i));

		for (int j = 0; j < 4; j++)
		{
			if (i + j < nb_words)
				printk("%08x ", ptr[i + j]);
			else
				printk("         ");
		}

		printk(" |");
		for (int j = 0; j < 16; j++)
		{
			if ((i * 4) + j < diff)
			{
				uint8_t c = ((uint8_t *)ptr)[(i * 4) + j];
				if (c >= 32 && c <= 126)
					printk("%c", c);
				else
					printk(".");
			}
		}
		printk("|");
	}
	printk("\n=== STACK DUMP | ESP: %p | SIZE: %d ===\n", esp, diff);
}
