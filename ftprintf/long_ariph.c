/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_ariph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 20:19:22 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/18 12:43:21 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int 	init_longb(t_longb *longb, t_ulong val)
{
	longb->size = 0;
	longb->max_size = sizeof(longb->val) / sizeof(longb->val[0]);
	longb->base = 1 * 1000 * 1000 * 1000;
	if (!val)
		longb->val[longb->size++] = 0;
	else
	{
		while(val)
		{
			longb->val[longb->size++] = val % longb->base;
			val /= longb->base;
		}
	}
	return (1);
}

int		add_longb(t_longb *a, t_longb *b)
{
	size_t		max;
	size_t		count;
	t_ullong	val;
	size_t		add;

	count = 0;
	add = 0;
	max = a->size;
	if (b->size > max)
		max = b->size;
	while (count < max)
	{
		val = (count < a->size ? a->val[count] : (size_t)0) +
				(count < b->size ? b->val[count] : (size_t)0) + add;
		if (count >= a->size)
			a->size++;
		if (val < a->base && !(add = 0))
			a->val[count] = val;
		else if ((add = 1))
			a->val[count] = val - a->base;
		count++;
	}
	if (add)
		a->val[a->size++] = 1;
	return (1);
}

int		div2_longb_uint(t_longb *longb)
{
	int			counta;
	t_ullong	mod;
	t_ullong	rem;

	mod = 0;
	counta = longb->size - 1;
	while (counta >= 0)
	{
		rem = longb->val[counta] & 1;
		longb->val[counta] = (longb->val[counta] + mod * longb->base) >> 1;
		if (!longb->val[counta] && counta == longb->size - 1)
			longb->size--;
		mod = rem;
		counta--;
	}
	return (0);
}

void	print_longb(t_longb *longb)
{
	size_t		count;
	size_t		base;
	t_ullong	val;

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
			ft_putchar(val / base + '0');
			val %= base;
			base /= 10;
		}
		ft_putchar(val + '0');
		while(count--)
		{
			val = longb->val[count];
			base = longb->base / 10;
			while (base >= 10)
			{
				ft_putchar(val / base + '0');
				val %= base;
				base /= 10;
			}
			ft_putchar(val + '0');
		}
	}
	else
	{
		ft_putchar('0');
	}
}

int 	get_longb_len(t_longb *longb)
{
	int len;
	t_uint val;

	len = 0;
	if (longb->size)
	{
		if (longb->size != 1)
			len += ((longb->size - 1) * 9);
		val = longb->val[longb->size - 1];
		while (val)
		{
			len++;
			val/=10;
		}
	}
	return (len);
}

int		calc_big_double(t_longb *longb, t_ullong val, t_ullong bits)
{
	t_longb 	help;
	t_ullong	size;

	size = 0;
	init_longb(longb, 0);
	init_longb(&help, 1);
	while (size < bits && size < 64)
	{
		if (val & (1ull << size))
			add_longb(longb, &help);
		add_longb(&help, &help);
		size++;
	}
	while (size < bits)
	{
		add_longb(longb, longb);
		size++;
	}
	return (0);
}

int		calc_big_double1(t_longb *longb, t_ullong val, long bits)
{
	t_longb		bignum;
	int			size;

	size = -1;
	memset(&bignum, 0, sizeof(bignum));
	init_longb(&bignum, 0);
	bignum.val[bignum.max_size - 1] = 5 * 1000 * 1000 * 100;
	bignum.size = bignum.max_size;
	init_longb(longb, 0);
	while (bits < 0)
	{
		div2_longb_uint(&bignum);
		bits++;
	}
	while (bits < 64)
	{
		if (val & (1ull << (63 - bits)))
			add_longb(longb, &bignum);
		div2_longb_uint(&bignum);
		bits++;
	}
	printf("len: %d\n", get_longb_len(&bignum));
	return (0);
}
