/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_delall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 12:54:42 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/05 13:22:08 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stack_delall(t_ftstack *stack, void (*f)(void *))
{
	while (stack->pos)
	{
		if (f)
			f(stack->data[stack->pos - 1]);
		stack->pos--;
	}
	ft_memdel((void **)&stack->data);
	return (0);
}
