/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 10:19:14 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/18 18:12:31 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "float.h"

int print_bits(t_ullong a)
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

void	get_double_val(t_print *print, va_list *ptr, t_fpoint *fdata)
{
	t_bldouble	ld;
	long		exp;

	if (print->lenmod == LENMOD_BL)
		ld.val = va_arg(*ptr, t_ldouble);
	else
		ld.val = va_arg(*ptr, double);
	fdata->exp = ld.bldbl.exp;
	print_bits(fdata->exp);
	fdata->is_neg = ld.bldbl.sign;
	fdata->mant = ld.bldbl.man;
	print_bits(fdata->mant);
	exp = ld.bldbl.exp - 16382;
	fdata->exp = exp;
	ft_putstr("exp:");
	ft_putnbr(exp);
	ft_putchar('\n');
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
	print_bits(fdata->lval);
	print_bits(fdata->rval);
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

int	parse_double(t_print *print, va_list *ptr)
{
	int				writed;
	t_fpoint		val;
	t_longb			lval;
	writed = 0;

	get_double_val(print, ptr, &val);
	print->str_len = calc_lval(&val, &lval);
	print->pre_len = calc_dpre_len(print, &val);
	print->point_len = print->is_precision ? print->precision : 6;
	if (print->point_len)
		print->point_len++;
	print->str_len += print->point_len;
	writed += add_pre_paddings(print);
	writed += add_double(print, &val, &lval);
	writed += add_post_paddings(print);
	return (writed);
}
