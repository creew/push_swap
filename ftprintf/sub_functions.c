/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 10:35:33 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/13 19:12:53 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_ullong	reverse_bits(t_ullong data, int bits)
{
	int			count;
	t_ullong	ret;

	ret = 0;
	count = 0;
	while (count < bits)
	{
		if (data & (1 << count))
			ret |= 1 << (bits - count - 1);
		count++;
	}
	return (ret);
}
