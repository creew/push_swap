/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:23:40 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/20 20:52:22 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_writed(t_print *print, char c, int *writed, int len)
{
	*writed += add_to_out(print, c);
	return (*writed == len);
}

int		print_longb(t_print *print, t_longb *longb, int len)
{
	int			count;
	size_t		base;
	t_ullong	val;
	int			writed;

	writed = 0;
	count = longb->size;
	while (count--)
	{
		val = longb->val[count];
		base = longb->base / 10;
		if (count == longb->size - 1)
		{
			while (base >= 10 && val / base == 0)
			{
				val %= base;
				base /= 10;
			}
		}
		while (base >= 10)
		{
			if (check_writed(print, val / base + '0', &writed, len))
				return (writed);
			val %= base;
			base /= 10;
		}
		if (check_writed(print, val + '0', &writed, len))
			return (writed);
	}
	if (!longb->size)
	{
		if (check_writed(print, '0', &writed, len))
			return (writed);
	}
	return (writed);
}

int		round_double(t_print *print, t_fpoint *fdata,
						t_longb *lval, t_longb *rval)
{
	t_longb		round;
	int			order;

	calc_lval(fdata, lval);
	calc_rval(fdata, rval);
	init_max_val(&round);
	print->max_rlen = get_longb_len(&round);
	order = 1;
	while (order++ < print->point_len)
		div_longb_uint(&round, 10);
	if (!add_longb(rval, &round))
		add_longb_uint(lval, 1);
	return (0);
}

int		add_double(t_print *print, t_longb *lval, t_longb *rval)
{
	int			writed;
	int			r_len;
	int			lpoint;

	writed = print_longb(print, lval, -1);
	if (print->point_len)
	{
		writed += add_to_out(print, '.');
		lpoint = print->point_len - 1;
		r_len = get_longb_len(rval);
		while (r_len++ < print->max_rlen && lpoint-- > 0)
			writed += add_to_out(print, '0');
		if (lpoint > 0)
			writed += print_longb(print, rval, lpoint);
	}
	return (writed);
}
