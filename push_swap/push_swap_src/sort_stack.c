/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:12:36 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/02 17:12:37 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		find_min_index(t_stack *st)
{
	size_t	count;
	int		min;
	int		blocked;

	blocked = 0;
	min = st->pos ? (int)st->pos - 1 : -1;
	count = st->pos;
	while (count--)
	{
		if (st->stack[count] < st->stack[min])
		{
			min = (int)count;
			blocked = 1;
		}
		else if (st->stack[count] == st->stack[min])
		{
			if (!blocked && (blocked = 1))
				min = (int)count;
		}
		else
			blocked = 0;
	}
	return (min);
}

int		is_cycle_sorted(t_stack *st, int start)
{
	int		end;
	int		prev_val;

	prev_val = st->stack[start];
	end = start;
	start = start == 0 ? (int)st->pos - 1 : start - 1;
	while (start != end)
	{
		if (prev_val > st->stack[start])
			return (0);
		prev_val = st->stack[start];
		start = start == 0 ? (int)st->pos - 1 : start - 1;
	}
	return (1);
}

void	sort3items(t_stack *st, int *count, t_stg *stg, int command)
{
	int	min_index;

	if (st->pos == 3)
	{
		if ((min_index = find_min_index(st)) != -1)
		{
			if (!is_cycle_sorted(st, min_index))
				run_commands(stg, command, count);
		}
	}
}

int		normalize_stack(t_stg *stg, int *count)
{
	int	min;
	int	n;

	min = find_min_index(&stg->st1);
	if (min != (int)stg->st1.pos - 1)
	{
		if ((int)stg->st1.pos - 1 - min < min + 1)
		{
			n = (int)stg->st1.pos - 1 - min;
			while (n--)
				run_commands(stg, S_RA, count);
		}
		else
		{
			n = min + 1;
			while (n--)
				run_commands(stg, S_RRA, count);
		}
	}
	return (0);
}

int		is_stack_sorted_index(t_stack *st)
{
	int		min_index;

	if ((min_index = find_min_index(st)) != -1)
	{
		if (is_cycle_sorted(st, min_index))
			return (1);
	}
	return (0);
}
