/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 12:35:15 by mgama             #+#    #+#             */
/*   Updated: 2026/06/04 18:41:52 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/print/print.h"

/**
 * The `_kstack_base` symbol is defined by the kernel to be the maximum address of the
 * kernel stack space. It can be used to get the base address of the kernel
 * stack and calculate the size of the stack used by comparing it with the
 * current ESP value.
 * 
 *        <- Highter addresses
 *  +--------+ <- `_kstack_base` (base/end)
 *  |        |
 *  |  USED  |
 *  |        |
 *  +--------+ <- `ESP` (current stack pointer)
 *  |        |
 *  | UNUSED |
 *  |        |
 *  +--------+
 *       <- Lower addresses
 *
 * diff = _kstack_base - ESP (bytes used on stack)
 */
extern uint32_t _kstack_base;

static inline uint32_t
get_esp(void)
{
	uint32_t esp;
	__asm__ volatile("mov %%esp, %0" : "=r"(esp));

	return esp;
}

void
kstackdump(void)
{
	uint32_t esp = get_esp();
	uint32_t stack_base = (uint32_t)&_kstack_base;
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
