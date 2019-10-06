/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 12:46:37 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/06 15:35:47 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	voidcpy(void **dst, void **src, size_t size)
{
	while (size)
	{
		*dst++ = *src++;
		size--;
	}
}

int			ft_stack_push(t_ftstack *stack, void *data)
{
	void	**newstack;
	void	**old;

	if (stack->pos >= stack->size)
	{
		newstack = ft_memalloc(stack->size + stack->init_val);
		if (!newstack)
			return (1);
		if (stack->data)
			voidcpy(newstack, stack->data, stack->size);
		old = stack->data;
		stack->data = newstack;
		stack->size += stack->init_val;
		ft_memdel((void **)&old);
	}
	stack->data[stack->pos++] = data;
	return (0);
}
