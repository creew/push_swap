/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_sec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:36:21 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/25 11:53:15 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		is_stack_sorted(t_stack *st, size_t n, int backward)
{
	int		val;
	int		count;

	count = st->pos;
	if (n > 1 && count > 1)
	{
		n--;
		val = st->stack[--count];
		while (n && count)
		{
			if (backward ? val < st->stack[--count] : val > st->stack[--count])
				return (ERROR_NOT_SORTED_STACK);
			val = st->stack[count];
		}
	}
	return (RET_OK);
}

int 	stack_free(t_stack *st)
{
	free(st->stack);
	return (RET_OK);
}

int 	stack_swap(t_stack *st)
{
	int		tmp;

	if (st->pos > 1)
	{
		tmp = st->stack[st->pos - 2];
		st->stack[st->pos - 2] = st->stack[st->pos - 1];
		st->stack[st->pos - 1] = tmp;
		return (RET_OK);
	}
	return (ERROR_INCORRECT_STACK_SIZE);
}

int 	stack_rotate(t_stack *st)
{
	int		tmp;

	if	 (st->pos > 1)
	{
		tmp = st->stack[st->pos - 1];
		ft_intmove(st->stack + 1, st->stack, st->pos - 1);
		st->stack[0] = tmp;
		return (RET_OK);
	}
	return (ERROR_INCORRECT_STACK_SIZE);
}

int 	stack_rrotate(t_stack *st)
{
	int		tmp;

	if (st->pos > 1)
	{
		tmp = st->stack[0];
		ft_intmove(st->stack, st->stack + 1, st->pos - 1);
		st->stack[st->pos - 1] = tmp;
		return (RET_OK);
	}
	return (ERROR_INCORRECT_STACK_SIZE);
}
