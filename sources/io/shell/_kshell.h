/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _kshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:03:31 by mgama             #+#    #+#             */
/*   Updated: 2026/05/18 14:34:27 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KSHELL_H
#define KSHELL_H

#include "types.h"

#define SHPROMPT "OS Shell> "

#define EXPORT_SHCMD(cmd) void (__shcmd_##cmd)(const char *args __unused)
#define DECLARE_SHCMD(cmd) {(#cmd), &__shcmd_##cmd}

struct command
{
	char *name;
	void (*func)(const char *args);
};

#define COMMAND_LIST \
	X(help)          \
	X(clear)         \
	X(reboot)        \
	X(shutdown)      \
	X(dump)          \
	X(fdump)         \
	X(echo)

#define X(cmd) EXPORT_SHCMD(cmd);
COMMAND_LIST
#undef X

extern struct command avail_commands[];
extern const size_t avail_commands_count;

#endif /* KSHELL_H */