/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkitoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:38:19 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:16:39 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

static int	pkabs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}

static void	pkstrrev(char *str)
{
	uint32_t	length;
	uint32_t	i;
	char	tmp;

	length = pkstrlen(str);
	i = 0;
	while (i < length / 2)
	{
		tmp = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = tmp;
		i++;
	}
}

int	get_num_len(int num)
{
	int	count;

	count = 0;
	if (num < 0)
		num = -num;
	while (num != 0)
	{
		num = num / 10;
		count++;
	}
	if (count == 0)
		count = 1;
	return (count);
}

char	*pkitoa(long int n)
{
	char	*str;
	int		is_neg;
	uint32_t	length;

	is_neg = (n < 0);
	str = pkcalloc(get_num_len(n) + 1 + is_neg, sizeof(*str));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + pkabs(n % 10);
		n = (n / 10);
	}
	if (is_neg)
		str[length] = '-';
	pkstrrev(str);
	return (str);
}

