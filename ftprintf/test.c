/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:30:42 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/23 10:31:43 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <limits.h>
#include <float.h>

int			main(int ac, char *av[])
{
	int				len;
	unsigned int	xren;

	//xren = 0x0001AA00;
	//char *str = "hello";
	//long double dr = 3.324233;
	unsigned int dr = 0xffff4444;
	//if (ac > 1)
	//	xren = atoi(av[1]);
#define VAL "123456789101112131415"
#define VAL2 DBL_MIN
#define VAL3 24
	const char *format = "%.20000f";
	len = ft_printf(format, VAL2, VAL3, VAL);
	printf("len: %d\n", len);
	len = printf(format, VAL2, VAL3, VAL);
	printf("len: %d\n", len);
	return (0);
}