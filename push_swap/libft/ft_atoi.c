/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:43:47 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/21 20:08:34 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int				isneg;
	unsigned long	res;
	unsigned long	num;

	isneg = 0;
	res = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			isneg = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (unsigned long)(*str++ - '0');
		if (!isneg && res >= (FT_LMAX / 10) && num >= (FT_LMAX % 10))
			return (-1);
		if (isneg && res >= (FT_LMIN / 10) && num >= (FT_LMIN % 10))
			return (0);
		res *= 10;
		res += num;
	}
	return (isneg ? -(int)res : (int)res);
}
