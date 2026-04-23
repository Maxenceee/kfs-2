/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _printk.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 12:48:27 by mgama             #+#    #+#             */
/*   Updated: 2026/04/23 13:40:57 by mgama            ###   ########.fr       */
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
int		pkprintf(const char *fmt, ...);

/* print_width */
void	pkprint_width(int width, int minus, int has_zero, int *count);
void	pkprint_max_width(int width, int max, int has_zero, int *count);

/* print_char */
void	pkputchar(char c);
void	pkputchar_c(char c, int *count);
void	pkprint_char(char c, int *count, t_flags flags, int percent);

/* print_string */
void	pkput_str(char *str, int *count);
void	pkputstrprec(char *str, int prec, int *count);
void	pkprint_str(char *s, int *count, t_flags flags);

/* print_int */
void	pkprint_int(int i, int *count, t_flags flags);

/* print_u_int */
void	pkprint_u_int(uint32_t unsi, int *count, t_flags flags);

/* print_float */
void	pkprint_float(double i, int *count, t_flags flags);

/* print_hex */
void	pkprint_hex(uint32_t ui, int lower,
			int *count, t_flags flags);

/* print_pointer */
void	pkprint_pointer(uint32_t ull, int *count,
			t_flags flags);

/* strlen */
uint32_t	pkstrlen(const char *str);

/* isdigit */
int		pkisdigit(int num);

/* is_valid */
int		pkis_valid_type(int c);
int		pkis_valid_flag(int c);

/* calloc */
void	*pkcalloc(uint32_t count, uint32_t size);

/* itoa */
int		get_num_len(int num);
char	*pkitoa(long int n);

/* uitoa*/
char	*pku_itoa(uint32_t n);

/* ftoa*/
char	*pkftoa(double x, int max);

/* strdup */
char	*pkstrdup(const char *src);

/* strlcat */
int		pkstrlcat(char *dest, char *src, uint32_t size);

/* strcat */
char	*pkstrcat(char *dest, char *src);

/* strjoin */
char	*pkstrjoin(char *s1, char *s2);

/* tolower */
char	*pkstr_tolower(char *str);
int		pktolower(int num);

/* convert base */
char	*pkconvert_base(uint32_t ull, int base);

/* pkcalloc */
void	*pkcalloc(uint32_t count, uint32_t size);

/* mem */
void	*pkmemcpy(void *dst, const void *src, uint32_t n);
void	*pkmemset(void *b, int c, uint32_t len);

/* pkbzero */
void	pkbzero(void *s, uint32_t n);

/* pkpow */
double	pkpow(double x, double y);

int		pkmin(int a, int b);

void	pkcheck_flags(const char *fmt, va_list *argp,
			t_flags *flags, int *idx);
void	pkcheck_flags_identifiers(const char *fmt, va_list *argp,
			t_flags *flags, int *idx);
void	pkhex_flag(t_flags *flags);
void	pkblank_flag(t_flags *flags, const char *s, int *idx);
void	pkminus_flag(t_flags *flags);
void	pkdigit_flag(char c, t_flags *flags);
void	pkwidth_flag(va_list *args, t_flags *flags);
void	pkdot_flag(const char *save, int *start,
			t_flags *flags, va_list *args);
void	pkplus_flag(t_flags *flags);

#endif /* PRINTK_H */