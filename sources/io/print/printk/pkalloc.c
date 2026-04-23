/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:19:10 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:32:25 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"

#define stack_alloc(size) __builtin_alloca(size)

#define PRINTK_BUFFER_SIZE 1024
static uint8_t  __pk_stack[PRINTK_BUFFER_SIZE];
static uint32_t __pk_ptr = 0;

void*
__printk_alloc(uint32_t size)
{
	uint32_t next_offset;

    if (__builtin_add_overflow(__pk_ptr, size, &next_offset))
    {
        return (NULL);
    }

    if (next_offset > PRINTK_BUFFER_SIZE)
    {
        return (NULL);
    }

    void *res = (void *)(__pk_stack + __pk_ptr);
    __pk_ptr = next_offset;

    return (res);
}

void
__printk_free(void * __unused ptr)
{
	__pk_ptr = 0;
}
