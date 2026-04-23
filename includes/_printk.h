/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _printk.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 12:48:27 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:20:10 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTK_H
#define PRINTK_H

typedef __builtin_va_list va_list;

#define va_start(v, l)  __builtin_va_start(v, l)
#define va_end(v)       __builtin_va_end(v)
#define va_arg(v, t)    __builtin_va_arg(v, t)
#define va_copy(d, s)   __builtin_va_copy(d, s)

#define NULL ((void *)0)

#include "screen.h"
#include "types.h"

void*	__printk_alloc(uint32_t size);
void	__printk_free(void *ptr);

typedef struct s_flags
{
	int				already_print;
	int				type;
	int				width;
	int				minus;
	int				plus;
	int				zero;
	int				dot;
	int				star;
	int				hex;
	int				blank;
}					t_flags;

/* printf */
int		ft_printf(const char *fmt, ...);

/* print_width */
void	ft_print_width(int width, int minus, int has_zero, int *count);
void	ft_print_max_width(int width, int max, int has_zero, int *count);

/* print_char */
void	ft_putchar(char c);
void	ft_putchar_c(char c, int *count);
void	ft_print_char(char c, int *count, t_flags flags, int percent);

/* print_string */
void	ft_put_str(char *str, int *count);
void	ft_putstrprec(char *str, int prec, int *count);
void	ft_print_str(char *s, int *count, t_flags flags);

/* print_int */
void	ft_print_int(int i, int *count, t_flags flags);

/* print_u_int */
void	ft_print_u_int(uint32_t unsi, int *count, t_flags flags);

/* print_float */
void	ft_print_float(double i, int *count, t_flags flags);

/* print_hex */
void	ft_print_hex(uint32_t ui, int lower,
			int *count, t_flags flags);

/* print_pointer */
void	ft_print_pointer(uint32_t ull, int *count,
			t_flags flags);

/* strlen */
uint32_t	ft_strlen(const char *str);

/* isdigit */
int		ft_isdigit(int num);

/* is_valid */
int		ft_is_valid_type(int c);
int		ft_is_valid_flag(int c);

/* calloc */
void	*ft_calloc(uint32_t count, uint32_t size);

/* itoa */
int		get_num_len(int num);
char	*ft_itoa(long int n);

/* uitoa*/
char	*ft_u_itoa(uint32_t n);

/* ftoa*/
char	*ft_ftoa(double x, int max);

/* strdup */
char	*ft_strdup(const char *src);

/* strlcat */
int		ft_strlcat(char *dest, char *src, uint32_t size);

/* strcat */
char	*ft_strcat(char *dest, char *src);

/* strjoin */
char	*ft_strjoin(char *s1, char *s2);

/* tolower */
char	*ft_str_tolower(char *str);
int		ft_tolower(int num);

/* convert base */
char	*ft_convert_base(uint32_t ull, int base);

/* ft_calloc */
void	*ft_calloc(uint32_t count, uint32_t size);

/* mem */
void	*ft_memcpy(void *dst, const void *src, uint32_t n);
void	*ft_memset(void *b, int c, uint32_t len);

/* ft_bzero */
void	ft_bzero(void *s, uint32_t n);

/* ft_pow */
double	ft_pow(double x, double y);

int		ft_min(int a, int b);

void	ft_check_flags(const char *fmt, va_list *argp,
			t_flags *flags, int *idx);
void	ft_check_flags_identifiers(const char *fmt, va_list *argp,
			t_flags *flags, int *idx);
void	ft_hex_flag(t_flags *flags);
void	ft_blank_flag(t_flags *flags, const char *s, int *idx);
void	ft_minus_flag(t_flags *flags);
void	ft_digit_flag(char c, t_flags *flags);
void	ft_width_flag(va_list *args, t_flags *flags);
void	ft_dot_flag(const char *save, int *start,
			t_flags *flags, va_list *args);
void	ft_plus_flag(t_flags *flags);

#endif /* PRINTK_H */