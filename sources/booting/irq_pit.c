/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irq_pit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:04:50 by mgama             #+#    #+#             */
/*   Updated: 2026/05/19 11:05:36 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io/print/print.h"
#include "io/io.h"
#include "timer/time.h"

volatile uint32_t jiffies = 0;

void
_irq_pit_handler(void)
{
    jiffies++;
}
