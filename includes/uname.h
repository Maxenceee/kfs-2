/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uname.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:33:31 by mgama             #+#    #+#             */
/*   Updated: 2026/06/10 17:48:23 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNAME_H
#define UNAME_H

struct utsname_s {
	char sysname[32];
	char release[32];
	char machine[16];
	char date[32];
};

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

#endif /* UNAME_H */