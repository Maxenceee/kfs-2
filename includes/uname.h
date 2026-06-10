/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uname.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:33:31 by mgama             #+#    #+#             */
/*   Updated: 2026/06/10 17:42:30 by mgama            ###   ########.fr       */
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

extern const struct utsname_s kuname;

#endif /* UNAME_H */