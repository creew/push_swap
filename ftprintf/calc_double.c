/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 13:24:24 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/18 23:40:13 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_longb_len(t_longb *longb)
{
	int			len;
	t_uint		val;

	len = 0;
	if (longb->size)
	{
		if (longb->size == 1 && longb->val[0] == 0)
			len = 1;
		else
		{
			if (longb->size != 1)
				len += ((longb->size - 1) * 9);
			val = longb->val[longb->size - 1];
			while (val)
			{
				len++;
				val /= 10;
			}
		}
	}
	return (len);
}

int		calc_lval(t_fpoint *fdata, t_longb *lval)
{
	t_longb 	help;
	long		size;

	init_longb(lval, 0);
	if (fdata->exp >= 0)
	{
		size = 0;
		init_longb(&help, 1);
		while (size < fdata->exp && size < 64)
		{
			if (fdata->lval & (1ull << size))
				add_longb(lval, &help);
			add_longb(&help, &help);
			size++;
		}
		while (size < fdata->exp)
		{
			add_longb(lval, lval);
			size++;
		}
	}
	return (get_longb_len(lval));
}

int			init_max_val(t_longb *val)
{
	ft_memset(val, 0, sizeof(*val));
	init_longb(val, 0);
	val->val[val->max_size - 1] = 5 * 1000 * 1000 * 100;
	val->size = val->max_size;
	return (get_longb_len(val));
}

int			calc_rval(t_fpoint *fdata,	t_longb *rval, int *maxlen)
{
	t_longb		bignum;
	long		bits;

	bits = fdata->exp > 0 ? 0 : fdata->exp;
	*maxlen = init_max_val(&bignum);
	init_longb(rval, 0);
	while (bits < 0)
	{
		div2_longb_uint(&bignum);
		bits++;
	}
	while (bits < 64)
	{
		if (fdata->rval & (1ull << (63 - bits)))
			add_longb(rval, &bignum);
		div2_longb_uint(&bignum);
		bits++;
	}
	return (get_longb_len(rval));
}
