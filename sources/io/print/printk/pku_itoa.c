/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pku_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:59:41 by rchallie          #+#    #+#             */
/*   Updated: 2026/04/23 13:25:18 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "io/print/print.h"

static int	get_num_ulen(unsigned long num)
{
	uint32_t	count;

	count = 0;
	while (num != 0)
	{
		num = num / 10;
		count++;
	}
	if (count == 0)
		count = 1;
	return (count);
}

static char	*pkgen(char *rtn, unsigned long nbr, int len)
{
	if (nbr == 0)
		return (pkstrdup("0"));
	rtn = __printk_alloc(sizeof(char) * (len + 1));
	if (!rtn)
		return (NULL);
	rtn[len] = '\0';
	while (--len)
	{
		rtn[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	rtn[0] = (nbr % 10) + '0';
	return (rtn);
}

char	*pku_itoa(uint32_t n)
{
	int		len;
	long	nbr;

	nbr = n;
	len = get_num_ulen(nbr);
	return (pkgen(NULL, nbr, len));
}
