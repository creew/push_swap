/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:01:35 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/02 17:01:36 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	find_left_values(t_stack *st, int val, int *vals)
{
	int pos;

	pos = st->pos;
	while (pos--)
	{
		if (val >= st->stack[get_prev_i(st, pos)] && val <= st->stack[pos])
		{
			*vals = (int)st->pos - 1 - pos;
			break ;
		}
	}
}

static void	find_right_values(t_stack *st, int val, int *vals)
{
	int pos;

	pos = 0;
	while (pos < (int)st->pos)
	{
		if (val >= st->stack[get_prev_i(st, pos)] && val <= st->stack[pos])
		{
			*vals = -(pos + 1);
			break ;
		}
		pos++;
	}
}

static int	find_place_to_paste(t_stack *st, int val, int vals[2])
{
	int		min_index;

	min_index = find_min_index(st);
	vals[0] = (int)st->pos - 1 - min_index;
	vals[1] = -(min_index + 1);
	if (min_index != -1)
	{
		find_left_values(st, val, vals + 0);
		find_right_values(st, val, vals + 1);
	}
	return (0);
}

static int	find_optimal(t_stack *st1, t_stack *st2, t_diff *gres)
{
	int		size;
	t_diff	res;
	int		s1[2];
	int		s2[2];

	size = (int)st2->pos;
	if (size--)
	{
		s2[0] = (int)st2->pos - 1 - size;
		s2[1] = -(size + 1);
		find_place_to_paste(st1, st2->stack[size], s1);
		find_min_diff(s1, s2, gres);
		while (size--)
		{
			s2[0] = (int)st2->pos - 1 - size;
			s2[1] = -(size + 1);
			find_place_to_paste(st1, st2->stack[size], s1);
			find_min_diff(s1, s2, &res);
			if (get_actual_diff(&res) < get_actual_diff(gres))
				set_tdiff(gres, res.s1_diff, res.s2_diff);
		}
	}
	return (0);
}

int			calc_optimal(t_stg *stg)
{
	size_t	size;
	int		count;
	t_diff	gres;

	count = 0;
	if (!is_stack_sorted_index(&stg->st1))
	{
		size = stg->st1.pos;
		while (size-- > 3 && !is_stack_sorted_index(&stg->st1))
			run_commands(stg, S_PB, &count);
		sort3items(stg, &count);
		while (stg->st2.pos)
		{
			find_optimal(&stg->st1, &stg->st2, &gres);
			paste_optimal(stg, &gres, &count);
		}
	}
	normalize_stack(stg, &count);
	return (count);
}
