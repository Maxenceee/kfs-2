/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _frames.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:36:02 by mgama             #+#    #+#             */
/*   Updated: 2026/06/10 12:14:43 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FRAMES_H
#define _FRAMES_H

#include "anim/render/render.h"

#include "_knot_frames.h"
#include "_parrot_frames.h"
#include "_nyan_frames.h"
#include "_bomb_frames.h"

#define DEFINE_ANIM_RENDER_FUNC(min_name, maj_name) \
void run_##min_name(int loops) { \
    render_anim(loops, _##maj_name##_HEIGHT, _##maj_name##_WIDTH, (const uint16_t *)_##min_name##_frames, _##maj_name##_FRAME_COUNT); \
}

DEFINE_ANIM_RENDER_FUNC(knot, KNOT)
DEFINE_ANIM_RENDER_FUNC(parrot, PARROT)
DEFINE_ANIM_RENDER_FUNC(nyan, NYAN)
DEFINE_ANIM_RENDER_FUNC(bomb, BOMB)

#endif /* _FRAMES_H */