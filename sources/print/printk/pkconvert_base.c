/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkconvert_base_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:39:03 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:17:21 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

static char	*pkput_base(uint32_t ull_save, int base,
	char *rtn, int count)
{
	while (ull_save != 0)
	{
		if ((ull_save % base) < 10)
			rtn[count - 1] = (ull_save % base) + 48;
		else
			rtn[count - 1] = (ull_save % base) + 55;
		ull_save /= base;
		count--;
	}
	return (rtn);
}

char	*pkconvert_base(uint32_t ull, int base)
{
	char		*rtn;
	uint32_t	ull_save;
	int			count;

	rtn = 0;
	count = 0;
	ull_save = ull;
	if (ull == 0)
		return (pkstrdup("0"));
	while (ull != 0)
	{
		ull /= base;
		count++;
	}
	rtn = __printk_alloc(sizeof(char) * (count + 1));
	if (!rtn)
		return (NULL);
	rtn[count] = '\0';
	rtn = pkput_base(ull_save, base, rtn, count);
	return (rtn);
}