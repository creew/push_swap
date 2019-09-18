/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:17:51 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/13 19:14:43 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	get_ullong_val(t_print *print, va_list *ptr)
{
	t_ullong val;

	if (print->type == 'p')
		val = (unsigned long long)va_arg(*ptr, void *);
	else if (print->lenmod == LENMOD_HH)
		val = va_arg(*ptr, unsigned int);
	else if (print->lenmod == LENMOD_H)
		val = va_arg(*ptr, unsigned int);
	else if (print->lenmod == LENMOD_L)
		val = va_arg(*ptr, unsigned long);
	else if (print->lenmod == LENMOD_LL)
		val = va_arg(*ptr, unsigned long long);
	else if (print->lenmod == LENMOD_T)
		val = va_arg(*ptr, size_t);
	else
		val = va_arg(*ptr, unsigned int);
	return (val);
}

static int			calc_pre_len(t_print *print)
{
	int		pre_len;

	pre_len = 0;
	if (print->type == 'x' || print->type == 'X')
	{
		if (print->flags & FLAG_HASH && print->is_val)
			pre_len = 2;
	}
	if (print->type == 'p')
		pre_len = 2;
	if (print->type == 'o' && print->flags & FLAG_HASH && print->is_val)
		pre_len = 1;
	return (pre_len);
}

int					parse_unsigned_base(t_print *print, va_list *ptr, int base)
{
	t_ullong	val;
	int			writed;

	writed = 0;
	val = get_ullong_val(print, ptr);
	if (val)
		print->is_val = 1;
	print->str_len = get_unsigned_length(val, base, NULL);
	print->pre_len = calc_pre_len(print);
	if (print->is_precision && print->precision > print->str_len)
		print->str_len = print->precision;
	writed += add_pre_paddings(print);
	writed += add_unsigned_base(print, val, base);
	writed += add_post_paddings(print);
	return (writed);
}
