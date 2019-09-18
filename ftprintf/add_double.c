/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:23:40 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/18 18:33:21 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_longb(t_print *print, t_longb *longb)
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
		while (base >= 10 && val/base == 0)
		{
			val %= base;
			base /= 10;
		}
		while (base >= 10)
		{
			writed += add_to_out(print, val / base + '0');
			val %= base;
			base /= 10;
		}
		writed += add_to_out(print, val + '0');
		while(count--)
		{
			val = longb->val[count];
			base = longb->base / 10;
			while (base >= 10)
			{
				writed += add_to_out(print, val / base + '0');
				val %= base;
				base /= 10;
			}
			writed += add_to_out(print, val + '0');
		}
	}
	else
	{
		writed += add_to_out(print, '0');
	}
	return (writed);
}



int		add_double(t_print *print, t_fpoint *fdata, t_longb *lval)
{
	t_longb		rval;
	t_longb		round;
	int			writed;
	int			r_len;
	int			r_maxlen;

	writed = print_longb(print, lval);
	if (print->point_len)
	{
		writed += add_to_out(print, '.');
		calc_rval(fdata, &rval, &r_maxlen);
		init_max_val(&round);
		r_len = 1;
		while (r_len++ <= print->point_len)
			div_longb_uint(&round, 10);
		add_longb(&rval, &round);
		r_len = calc_rval(fdata, &rval, &r_maxlen);
		while (r_len < r_maxlen)
		{
			writed += add_to_out(print, '0');
			r_len++;
		}
		writed += print_longb(print, &rval);
	}
	return (writed);
}
