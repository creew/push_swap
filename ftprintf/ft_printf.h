/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:36:34 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/18 12:39:10 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <wchar.h>
# include "libft.h"

# define FLAGS_STR "+- #0"
# define FLAG_PLUS	1
# define FLAG_MINUS	2
# define FLAG_SPACE	4
# define FLAG_HASH	8
# define FLAG_NULL	16
# define FLAG_APOSTROFE 32

# define TYPES_STR "cCsSpdDiIoOuUxXfF"

# define DEPRECATED_STR "DOUB"

# define LENMOD_STR "hljtzL"
# define LENMOD_HH	1
# define LENMOD_H	2
# define LENMOD_L	3
# define LENMOD_LL	4
# define LENMOD_J	5
# define LENMOD_T	6
# define LENMOD_Z	7
# define LENMOD_BL	8

typedef unsigned long long t_ullong;

typedef unsigned long		t_ulong;

typedef long long			t_llong;

typedef long double			t_ldouble;

typedef unsigned int		t_uint;

typedef union	u_bldouble
{
	t_ldouble		n;
	struct		s_bit_ldouble {
		t_ulong		bit_m:	64;
		t_ulong		bit_e:	15;
		t_ulong		bit_es:	1;
	}				s_bitd;
}				t_bldouble;

typedef union  u_ldouble
{
    long double	val;
    struct b_double
    {
        t_ulong	man:64;
        t_ulong	exp:15;
        t_ulong	sign:1;
    }			bldbl;
}               t_ldouble;

typedef struct	s_print
{
	char		buf[1024];
	size_t		buf_len;

	int			type;
	int			is_precision;
	int			flags;
	int			width;
	int			precision;
	int			lenmod;
	int			pre_len;
	int			pad_len;
	int			str_len;
	int			is_val;
	int			is_neg;
}				t_print;

typedef struct	s_fpoint
{
	t_ulong		is_neg;
	long		shift;
	t_ulong		exp;
	t_ulong		mant;
}				t_fpoint;

typedef struct  s_longb
{
    t_uint      val[65];
    size_t      max_size;
    size_t      size;
    size_t      base;
}               t_longb;

int				add_to_out(t_print *print, char c);
int				addw_to_out(t_print *print, wint_t wc);
void			flush_buf(t_print *print);

int				parse_flags(t_print *print, const char *format);
int				parse_width(t_print *print, const char *format, va_list *ptr);
int				parse_precision(t_print *print, const char *format,
								va_list *ptr);
int				parse_type(t_print *print, const char *format);
int				parse_lenmod(t_print *print, const char *format);

int				parse_format(t_print *print, va_list *ptr);
int				parse_character(char type, t_print *print, va_list *ptr);
int				parse_string(char type, t_print *print, va_list *ptr);

int				add_c_with_flag(t_print *print, char *c, int len);
int				add_wc_with_flag(t_print *print, wint_t *wc, int len);
int				add_pre_paddings(t_print *print);
int				add_post_paddings(t_print *print);
int				add_prefix(t_print *print);

int				get_unsigned_length(unsigned long long val, size_t base,
						unsigned long long *powout);
int				add_unsigned_base(t_print *print, unsigned long long val,
						size_t base);
int				parse_unsigned_base(t_print *print, va_list *ptr, int base);
int				parse_signed_base(t_print *print, va_list *ptr, int base);
int				parse_double(t_print *print, va_list *ptr);

t_ullong		reverse_bits(t_ullong data, int bits);
#endif
