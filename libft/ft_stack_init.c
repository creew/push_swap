/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 12:44:12 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/05 12:54:39 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stack_init(t_ftstack *stack, size_t init_val)
{
	if (stack)
	{
		if (init_val == 0)
			init_val = 64;
		ft_bzero(stack, sizeof(stack));
		stack->init_val = init_val;
		return (0);
	}
	return (1);
}
