/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:17:12 by mgama             #+#    #+#             */
/*   Updated: 2026/05/19 11:27:16 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STD_H
#define STD_H

#include "types.h"

void	*kmemcpy(void *dst, const void *src, uint32_t n);
void	*kmemset(void *b, int c, uint32_t len);

uint32_t	kstrlen(const char *str);

int		katoi(const char *str);

int		kstrcmp(const char *s1, const char *s2);

int		kisdigit(int num);

int		kstrlcat(char *dest, char *src, uint32_t size);

char	*kstrcat(char *dest, char *src);

char	*kstr_tolower(char *str);
int		ktolower(int num);

void	kbzero(void *s, uint32_t n);

int		kmin(int a, int b);
int		kmax(int a, int b);

#endif /* STD_H */