/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printk.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:33:24 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 12:50:48 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_printk.h"
#include "print.h"

# define DIGITS "0123456789abcdef0123456789ABCDEF"

uint32_t
strlen(const char *str)
{
	uint32_t	count;

	count = 0;
	while (*str != '\0')
	{
		str++;
		count++;
	}
	return (count);
}

uint32_t
nbrsize_l(long int nb)
{
	uint32_t	i;
	int		div;

	i = 0;
	div = 1;
	while (nb / div > 9)
	{
		i++;
		div *= 10;
	}
	return (i);
}

uint32_t
nbrsize_ul(unsigned long int nb)
{
	uint32_t	i;
	int		div;

	i = 0;
	div = 1;
	while (nb / div > 9)
	{
		i++;
		div *= 10;
	}
	return (i);
}

void
putchar(char c, int *count, uint8_t attrib)
{
	vga_put(c, attrib);
	(*count)++;
}

void
putstr_fd(char *s, int *count, uint8_t attrib)
{
	uint32_t	c;

	if (!s)
		s = "(null)";
	c = strlen(s);
	vga_puts(s, c, attrib);
	(*count) += c;
}

void
putnbr(int nb, int *count, uint8_t attrib)
{
	if (nb == -2147483648)
	{
		putstr_fd("-2147483648", count, attrib);
		return ;
	}
	if (nb < 0)
	{
		putchar('-', count, attrib);
		nb = -nb;
	}
	if (nb > 9)
	{
		putnbr(nb / 10, count, attrib);
		putnbr(nb % 10, count, attrib);
	}
	else
		putchar(nb + 48, count, attrib);
}

void
putnbr_u(uint32_t nb, int *count, uint8_t attrib)
{
	if (nb > 9)
	{
		putnbr(nb / 10, count, attrib);
		putnbr(nb % 10, count, attrib);
	}
	else
		putchar(nb + 48, count, attrib);
}

void
putnbr_base(uint32_t nbr, int capitals, int *count, uint8_t attrib)
{
	if (nbr >= 16)
	{
		putnbr_base(nbr / 16, capitals, count, attrib);
		putnbr_base(nbr % 16, capitals, count, attrib);
	}
	else
		putchar(DIGITS[nbr + capitals], count, attrib);
}

void
putnbr_base_p(unsigned long int nbr, int capitals, int *count, uint8_t attrib)
{
	if (nbr >= 16)
	{
		putnbr_base_p(nbr / 16, capitals, count, attrib);
		putnbr_base_p(nbr % 16, capitals, count, attrib);
	}
	else
		putchar(DIGITS[nbr + capitals], count, attrib);
}

void
puthex(uint32_t n, int capitals, int *count, uint8_t attrib)
{
	putnbr_base(n, capitals, count, attrib);
}

void
puthex_p(unsigned long int n, int *count, uint8_t attrib)
{
	if (!n)
		return ((void)putstr_fd("(nil)", count, attrib));
	putstr_fd("0x", count, attrib);
	putnbr_base_p(n, 0, count, attrib);
}

void
switch_types(const char *fmt, va_list *argp, int *count, uint8_t attrib)
{
	if (*fmt == '%')
		putchar('%', count, attrib);
	else if (*fmt == 'c')
		putchar(va_arg(*argp, long), count, attrib);
	else if (*fmt == 's')
		putstr_fd(va_arg(*argp, char *), count, attrib);
	else if (*fmt == 'd' || *fmt == 'i')
		putnbr(va_arg(*argp, long), count, attrib);
	else if (*fmt == 'u')
		putnbr_u(va_arg(*argp, unsigned long), count, attrib);
	else if (*fmt == 'x')
		puthex(va_arg(*argp, uint32_t), 0, count, attrib);
	else if (*fmt == 'X')
		puthex(va_arg(*argp, uint32_t), 16, count, attrib);
	else if (*fmt == 'p')
		puthex_p(va_arg(*argp, unsigned long int), count, attrib);
}

void
print_type(const char *fmt, va_list *argp, int *count, uint8_t attrib)
{
	uint32_t	i;

	i = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] != '%')
		{
			putchar(fmt[i++], count, attrib);
			continue ;
		}
		i++;
		switch_types(fmt + i, argp, count, attrib);
		if (*count == -1)
			return ;
		i++;
	}
}

int
printk(const char *fmt, ...)
{
	va_list	listp;
	int		count;

	count = 0;
	va_start(listp, fmt);
	print_type(fmt, &listp, &count, VGA_FORE_WHITE | VGA_BACK_BLACK);
	va_end(listp);
	return (count);
}

int
cprintk(uint8_t attrib, const char *fmt, ...)
{
	va_list	listp;
	int		count;

	count = 0;
	va_start(listp, fmt);
	print_type(fmt, &listp, &count, attrib);
	va_end(listp);
	return (count);
}