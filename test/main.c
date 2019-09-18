/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 10:48:33 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/18 17:12:11 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "main.h"


void test_longa(t_ullong val, t_ullong bits)
{
	t_longb longb;

	calc_big_double(&longb, val, bits);
	print_longb(&longb);
	printf("\n");
}

void test_longb(t_ullong val, t_ullong bits)
{
	t_longb longb;

	calc_big_double1(&longb, val, bits);
	print_longb(&longb);
	printf("\n");
}

int print_bits(t_ulong a)
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

void test_double(long double va)
{
	t_ulong		lval;
	t_ulong		rval;
	long		exp;
	long		shift;
	t_ldouble	a;

	a.val = va;
	print_bits(a.bldbl.sign);
	print_bits(a.bldbl.exp);
	print_bits(a.bldbl.man);
	exp = a.bldbl.exp - 16382;
	if (exp < 0)
		lval = 0;
	else if (exp < 64)
		lval = a.bldbl.man >> (64 - exp);
	else
		lval = a.bldbl.man;
	if (exp < 0)
		rval = a.bldbl.man;
	else if (exp < 64)
		rval = a.bldbl.man << (exp);
	else
		rval = 0;
	printf("lval: %lu\n", lval);
	print_bits(lval);
	printf("rval: %lu\n", rval);
	print_bits(rval);
	printf("exp: %ld\n", exp);
	printf("%.20Lf\n", va);
	test_longa(lval, exp < 0 ? 0 : exp);
	test_longb(rval, exp < 0 ? exp: 0);
}

int main(int ac, char *av[])
{
	(void)(ac);
	(void)(av);
	int a = 0;
	long double b = 0.0001235;
	if (ac > 1)
	{
		a = atoi(av[1]);
		b = atof(av[1]);
	}
	(void)(a);
	test_double(b);
	return (0);
}
