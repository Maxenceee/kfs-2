/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _frames.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:36:02 by mgama             #+#    #+#             */
/*   Updated: 2026/06/10 11:49:55 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FRAMES_H
#define _FRAMES_H

#include "anim/render/render.h"

#include "knot_frames.h"
#include "parrot_frames.h"
#include "nyan_frames.h"
#include "bomb_frames.h"

#define DEFINE_ANIM_RENDER_FUNC(min_name, maj_name) \
void run_##min_name(int loops) { \
    render_anim(loops, maj_name##_HEIGHT, maj_name##_WIDTH, (const uint16_t *)min_name##_frames, maj_name##_FRAME_COUNT); \
}

DEFINE_ANIM_RENDER_FUNC(knot, KNOT)
DEFINE_ANIM_RENDER_FUNC(parrot, PARROT)
DEFINE_ANIM_RENDER_FUNC(nyan, NYAN)
DEFINE_ANIM_RENDER_FUNC(bomb, BOMB)

#endif /* _FRAMES_H */