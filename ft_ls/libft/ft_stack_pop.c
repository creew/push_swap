/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 12:52:19 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/05 12:54:39 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stack_pop(t_ftstack *stack, void **data)
{
	if (stack->pos)
	{
		*data = stack->data[--stack->pos];
		return (0);
	}
	return (0);
}
