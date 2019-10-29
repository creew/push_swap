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
		newst = (int *)malloc(sizeof(int) * (STACK_SIZE + st->max_size));
		if (!newst)
			return (ERROR_ENOMEM);
		if (st->stack)
			ft_intmove(newst, st->stack, st->max_size);
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

int		stack_get_first(t_stack *st, int *a)
{
	if (st->pos > 0)
	{
		*a = st->stack[0];
		ft_intmove(st->stack, st->stack + 1, st->pos - 1);
		st->pos--;
		return (RET_OK);
	}
	return (ERROR_GETEMPTY_STACK);
}

int		stack_add_first(t_stack *st, int a)
{
	int		*newst;

	if ((st->pos + 1) >= st->max_size)
	{
		newst = (int *)malloc(sizeof(int) * (STACK_SIZE + st->max_size));
		if (!newst)
			return (ERROR_ENOMEM);
		if (st->stack)
			ft_intmove(newst + 1, st->stack, st->max_size);
		st->stack = newst;
		st->max_size += STACK_SIZE;
	}
	else
		ft_intmove(st->stack + 1, st->stack, st->max_size);
	st->stack[0] = a;
	st->pos++;
	return (RET_OK);
}
