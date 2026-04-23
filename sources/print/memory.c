/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 12:35:15 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:32:05 by mgama            ###   ########.fr       */
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
    uint32_t nb_words = diff / sizeof(uint32_t);

    printk("\n=== FULL STACK DUMP ===");
    printk("\nESP: %p | Base: %p | Size: %d bytes\n", esp, stack_base, diff);

    uint32_t *ptr = (uint32_t *)esp;

    for (uint32_t i = 0; i < nb_words; i++) {
        if (i % 4 == 0) printk("\n%p: ", (uint32_t)(ptr + i));
        
        printk("%08x ", ptr[i]);
    }
    printk("\n=======================\n");
}
