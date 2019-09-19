/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:23:40 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/19 19:41:21 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_longb(t_print *print, t_longb *longb, int len)
{
	size_t		count;
	size_t		base;
	t_ullong	val;
	int			writed;

	writed = 0;
	count = longb->size;
	if (count--)
	{
		val = longb->val[count];
		base = longb->base / 10;
		while (base >= 10 && val / base == 0)
		{
			val %= base;
			base /= 10;
		}
		while (base >= 10)
		{
			writed += add_to_out(print, val / base + '0');
			if (writed == len)
				return (writed);
			val %= base;
			base /= 10;
		}
		writed += add_to_out(print, val + '0');
		if (writed == len)
			return (writed);
		while (count--)
		{
			val = longb->val[count];
			base = longb->base / 10;
			while (base >= 10)
			{
				writed += add_to_out(print, val / base + '0');
				if (writed == len)
					return (writed);
				val %= base;
				base /= 10;
			}
			writed += add_to_out(print, val + '0');
			if (writed == len)
				return (writed);
		}
	}
	else
	{
		writed += add_to_out(print, '0');
		if (writed == len)
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
		lpoint = print->point_len - 1;
		writed += add_to_out(print, '.');
		r_len = get_longb_len(rval);
		while (r_len++ < print->max_rlen && lpoint-- > 0)
			writed += add_to_out(print, '0');
		if (lpoint > 0)
			writed += print_longb(print, rval, lpoint);
	}
	return (writed);
}
