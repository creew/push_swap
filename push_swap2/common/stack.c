/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:25:25 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/25 16:07:48 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		stack_init(t_stack *st)
{
	st->stack = NULL;
	st->pos = 0;
	st->max_size = 0;
	return (RET_OK);
}

int		stack_push(t_stack *st, int a)
{
	int		*newst;

	if ((st->pos + 1) >= st->max_size)
	{
		newst = (int *)ft_calloc(STACK_SIZE + st->max_size, sizeof(int));
		if (!newst)
			return (ERROR_ENOMEM);
		if (st->stack)
			ft_intmove(newst, st->stack, st->max_size);
		free(st->stack);
		st->stack = newst;
		st->max_size += STACK_SIZE;
	}
	st->stack[st->pos++] = a;
	return (RET_OK);
}

int		stack_pop(t_stack *st, int *a)
{
	if (st->pos > 0)
	{
		*a = st->stack[st->pos - 1];
		st->pos--;
		return (RET_OK);
	}
	return (ERROR_GETEMPTY_STACK);
}
