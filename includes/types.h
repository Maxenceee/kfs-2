/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:25:29 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:25:09 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
#define TYPES_H

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;

typedef char            int8_t;
typedef short           int16_t;
typedef int             int32_t;

typedef uint32_t		  size_t;

#define UINT32_MAX 4294967295
#define UINT16_MAX 65535
#define UINT8_MAX 255

#define INT32_MAX 2147483647
#define INT16_MAX 32767
#define INT8_MAX 127

#define SIZE_MAX UINT32_MAX

#ifndef __dead2
#if defined(__GNUC__) || defined(__clang__)
#define __dead2 __attribute__((noreturn))
#else
#define __dead2
#endif
#endif /* __dead2 */

#ifndef __unused
#if defined(__GNUC__) || defined(__clang__)
#define __unused __attribute__((unused))
#else
#define __unused
#endif
#endif /* __unused */

#ifndef __nullable
#if defined(__GNUC__) || defined(__clang__)
#define __nullable __attribute__((nullable))
#else
#define __nullable
#endif
#endif /* __nullable */

#ifndef __nonnull
#if defined(__GNUC__) || defined(__clang__)
#define __nonnull __attribute__((nonnull))
#else
#define __nonnull
#endif
#endif /* __nonnull */

#endif /* TYPES_H */