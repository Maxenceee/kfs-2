/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:17:12 by mgama             #+#    #+#             */
/*   Updated: 2026/05/18 11:59:51 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STD_H
#define STD_H

#include "types.h"

/* mem */
void	*kmemcpy(void *dst, const void *src, uint32_t n);
void	*kmemset(void *b, int c, uint32_t len);

/* strlen */
uint32_t	kstrlen(const char *str);

/* strcmp */
int		kstrcmp(const char *s1, const char *s2);

/* isdigit */
int		kisdigit(int num);

/* strlcat */
int		kstrlcat(char *dest, char *src, uint32_t size);

/* strcat */
char	*kstrcat(char *dest, char *src);

/* tolower */
char	*kstr_tolower(char *str);
int		ktolower(int num);

/* bzero */
void	kbzero(void *s, uint32_t n);

/* math */
int		kmin(int a, int b);
int		kmax(int a, int b);

#endif /* STD_H */