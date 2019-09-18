/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 10:19:14 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/13 15:53:50 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "float.h"

void	get_double_val(t_print *print, va_list *ptr, t_fpoint *fdata)
{
	double		tmp;
	t_bldouble	ld;

	if (print->lenmod == LENMOD_BL)
		ld.n = va_arg(*ptr, t_ldouble);
	else
	{
		tmp = va_arg(*ptr, double);
		ld.n = tmp;
	}
	fdata->exp = reverse_bits(ld.s_bitd.bit_e, 15);
	fdata->is_neg = ld.s_bitd.bit_es;
	fdata->mant = reverse_bits(ld.s_bitd.bit_m, 64);
}

int	parse_double(t_print *print, va_list *ptr)
{
	int				writed;
	t_fpoint		val;

	writed = 0;

	get_double_val(print, ptr, &val);
	//val = val1 < 0 ? (t_ullong)(-val1) : val1;
	//print->str_len = get_unsigned_length(val, NULL);
	//print->pre_len = calc_pre_len(print);
	//if (val)
	//	print->is_val = 1;
	//if (print->is_precision && print->precision > print->str_len)
	//	print->str_len = print->precision;
	writed += add_pre_paddings(print);
	//writed += add_unsigned_base(print, val, base);
	writed += add_post_paddings(print);
	return (writed);
}
