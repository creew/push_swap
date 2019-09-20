/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 10:19:14 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/20 19:45:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "float.h"

int			print_bits(t_ullong a)
{
	int count;

	count = 0;
	while (count < 64)
	{
		ft_putchar(((a >> (63 - count)) & 1) + '0');
		count++;
		if (count % 8 == 0)
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}

void		get_double_val(t_print *print, va_list *ptr, t_fpoint *fdata)
{
	t_bldouble	ld;
	long		exp;

	if (print->lenmod == LENMOD_BL)
		ld.val = va_arg(*ptr, t_ldouble);
	else
		ld.val = va_arg(*ptr, double);
	fdata->exp = ld.bldbl.exp;
	fdata->is_neg = ld.bldbl.sign;
	fdata->mant = ld.bldbl.man;
	exp = ld.bldbl.exp - 16382;
	fdata->exp = exp;
	if (exp < 0)
		fdata->lval = 0;
	else if (exp < 64)
		fdata->lval = fdata->mant >> (64 - exp);
	else
		fdata->lval = fdata->mant;
	if (exp < 0)
		fdata->rval = fdata->mant;
	else if (exp < 64)
		fdata->rval = fdata->mant << exp;
	else
		fdata->rval = 0;
}

static int	calc_dpre_len(t_print *print, t_fpoint *fdata)
{
	int		pre_len;

	pre_len = 0;
	if (fdata->is_neg || (print->flags & FLAG_SPACE) ||
		(print->flags & FLAG_PLUS))
		pre_len = 1;
	return (pre_len);
}

int			parse_double(t_print *print, va_list *ptr)
{
	int				writed;
	t_fpoint		val;
	t_longb			lval;
	t_longb			rval;

	writed = 0;
	print->point_len = print->is_precision ? print->precision : 6;
	if (print->point_len || print->flags & FLAG_HASH)
		print->point_len++;
	get_double_val(print, ptr, &val);
	round_double(print, &val, &lval, &rval);
	print->is_neg = val.is_neg;
	print->str_len = get_longb_len(&lval);
	print->pre_len = calc_dpre_len(print, &val);
	print->str_len += print->point_len;
	writed += add_pre_paddings(print);
	writed += add_double(print, &lval, &rval);
	writed += add_post_paddings(print);
	return (writed);
}
