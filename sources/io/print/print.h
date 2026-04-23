/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 12:03:46 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:22:13 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
#define PRINT_H

#include "types.h"

int	printk(const char *fmt, ...);
int	cprintk(uint8_t attrib, const char *fmt, ...);

void	kstackdump(void);

#endif /* PRINT_H */