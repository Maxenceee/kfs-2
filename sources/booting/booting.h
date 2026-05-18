/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   booting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:14:32 by mgama             #+#    #+#             */
/*   Updated: 2026/05/18 14:40:17 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOOTING_H
#define BOOTING_H

#include "types.h"

void	kbd_enable(void);
void	kbd_disable(void);
size_t	kbd_read(char *buffer, size_t max_length);

#endif /* BOOTING_H */