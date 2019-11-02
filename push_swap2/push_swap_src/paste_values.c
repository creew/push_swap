/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:04:15 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/02 17:04:17 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	paste_positive(t_stack *st1, t_stack *st2, t_diff *gres, int *count)
{
	while (gres->s1_diff && gres->s2_diff)
	{
		run_commands(st1, st2, S_RR, count);
		gres->s1_diff--;
		gres->s2_diff--;
	}
	while (gres->s1_diff--)
		run_commands(st1, st2, S_RA, count);
	while (gres->s2_diff--)
		run_commands(st1, st2, S_RB, count);
}

static void	paste_negative(t_stack *st1, t_stack *st2, t_diff *gres, int *count)
{
	while (gres->s1_diff && gres->s2_diff)
	{
		run_commands(st1, st2, S_RRR, count);
		gres->s1_diff++;
		gres->s2_diff++;
	}
	while (gres->s1_diff++ < 0)
		run_commands(st1, st2, S_RRA, count);
	while (gres->s2_diff++ < 0)
		run_commands(st1, st2, S_RRB, count);
}

static void	paste_both(t_stack *st1, t_stack *st2, t_diff *gres, int *count)
{
	while (gres->s1_diff < 0)
	{
		run_commands(st1, st2, S_RRA, count);
		gres->s1_diff++;
	}
	while (gres->s2_diff < 0)
	{
		run_commands(st1, st2, S_RRB, count);
		gres->s2_diff++;
	}
	while (gres->s1_diff > 0)
	{
		run_commands(st1, st2, S_RA, count);
		gres->s1_diff--;
	}
	while (gres->s2_diff > 0)
	{
		run_commands(st1, st2, S_RB, count);
		gres->s2_diff--;
	}
}

void		paste_optimal(t_stack *st1, t_stack *st2, t_diff *gres, int *count)
{
	if (gres->s1_diff >= 0 && gres->s2_diff >= 0)
		paste_positive(st1, st2, gres, count);
	else if (gres->s1_diff <= 0 && gres->s2_diff <= 0)
		paste_negative(st1, st2, gres, count);
	else
		paste_both(st1, st2, gres, count);
	run_commands(st1, st2, S_PA, count);
}

int			get_prev_i(t_stack *st, int index)
{
	if (index + 1 >= (int)st->pos)
		return (0);
	return (index + 1);
}
