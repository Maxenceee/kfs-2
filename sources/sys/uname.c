/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uname.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:35:32 by mgama             #+#    #+#             */
/*   Updated: 2026/06/10 17:42:25 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "uname.h"

#define KERNEL_NAME     "Galileo"
#define KERNEL_VERSION  "0.1.0-alpha"
#define KERNEL_DATE     __DATE__ " " __TIME__

#if defined(__x86_64__)
	#define KERNEL_ARCH "x86_64"
#elif defined(__i386__)
	#define KERNEL_ARCH "i386"
#else
	#define KERNEL_ARCH "unknown"
#endif

const struct utsname_s kuname = {
	.sysname = KERNEL_NAME,
	.release = KERNEL_VERSION,
	.machine = KERNEL_ARCH,
	.date    = KERNEL_DATE
};
