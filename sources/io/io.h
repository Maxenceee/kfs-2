/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:04:28 by mgama             #+#    #+#             */
/*   Updated: 2026/05/18 11:04:29 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
#define IO_H

#include <types.h>

void	outb(uint16_t port, uint8_t data);
void	outw(uint16_t port, uint16_t data);
void	outl(uint16_t port, uint32_t data);

uint8_t		inb(uint16_t port);
uint16_t	inw(uint16_t port);
uint32_t	inl(uint16_t port);

#endif /* IO_H */