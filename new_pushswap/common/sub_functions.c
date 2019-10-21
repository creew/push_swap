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
	int		val;

	*res = 0;
	is_neg = 1;
	if (*arg == '+' || *arg == '-')
	{
		if (*arg == '-')
			is_neg = -1;
		arg++;
	}
	while ((val = *arg++))
	{
		if (val < '0' || val > '9')
			return (ERROR_WRONG_INTEGER);
		val = (val - '0') * is_neg;
		if (*res > FT_INTMAX / 10 ||
			(*res == FT_INTMAX / 10 && val > FT_INTMAX % 10))
			return (ERROR_OVERFLOW_INTEGER);
		if (*res < FT_INTMIN / 10 ||
			(*res == FT_INTMIN / 10 && val < FT_INTMIN % 10))
			return (ERROR_OVERFLOW_INTEGER);
		*res = *res * 10;
		*res = *res + val;
	}
	return (RET_OK);
}
