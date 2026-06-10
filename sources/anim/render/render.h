/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 18:06:24 by mgama             #+#    #+#             */
/*   Updated: 2026/06/09 18:32:19 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
#define RENDER_H

#include "types.h"

void	render_anim(int loops, int height, int width, const uint16_t *frames, int frame_count);

#endif /* RENDER_H */