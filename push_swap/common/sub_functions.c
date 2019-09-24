/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:30:51 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/23 17:16:44 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		safe_atoi(char *arg, int *res)
{
	int		is_neg;
	long	lres;
	int		val;

	lres = 0;
	is_neg = 0;
	if (*arg == '+' || *arg == '-')
	{
		if (*arg == '-')
			is_neg = 1;
		arg++;
	}
	while ((val = *arg++))
	{
		if (val < '0' || val > '9')
			return (ERROR_WRONG_INTEGER);
		val -= '0';
		if (is_neg  && lres >= (MAX_INTMIN / 10) && val >= (MAX_INTMIN % 10))
			return (ERROR_OVERFLOW_INTEGER);
		if (!is_neg && lres >= (MAX_INTMAX / 10) && val >= (MAX_INTMAX % 10))
			return (ERROR_OVERFLOW_INTEGER);
		lres = lres * 10;
		lres += val;
	}
	*res = is_neg ? (int)-lres : (int)lres ;
	return (RET_OK);
}
