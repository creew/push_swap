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

static void	paste_positive(t_stg *stg, t_diff *gres, int *count)
{
	while (gres->s1_diff && gres->s2_diff)
	{
		run_commands(stg, S_RR, count);
		gres->s1_diff--;
		gres->s2_diff--;
	}
	while (gres->s1_diff--)
		run_commands(stg, S_RA, count);
	while (gres->s2_diff--)
		run_commands(stg, S_RB, count);
}

static void	paste_negative(t_stg *stg, t_diff *gres, int *count)
{
	while (gres->s1_diff && gres->s2_diff)
	{
		run_commands(stg, S_RRR, count);
		gres->s1_diff++;
		gres->s2_diff++;
	}
	while (gres->s1_diff++ < 0)
		run_commands(stg, S_RRA, count);
	while (gres->s2_diff++ < 0)
		run_commands(stg, S_RRB, count);
}

static void	paste_both(t_stg *stg, t_diff *gres, int *count)
{
	while (gres->s1_diff < 0)
	{
		run_commands(stg, S_RRA, count);
		gres->s1_diff++;
	}
	while (gres->s2_diff < 0)
	{
		run_commands(stg, S_RRB, count);
		gres->s2_diff++;
	}
	while (gres->s1_diff > 0)
	{
		run_commands(stg, S_RA, count);
		gres->s1_diff--;
	}
	while (gres->s2_diff > 0)
	{
		run_commands(stg, S_RB, count);
		gres->s2_diff--;
	}
}

void		paste_optimal(t_stg *stg, t_diff *gres, int *count)
{
	if (gres->s1_diff >= 0 && gres->s2_diff >= 0)
		paste_positive(stg, gres, count);
	else if (gres->s1_diff <= 0 && gres->s2_diff <= 0)
		paste_negative(stg, gres, count);
	else
		paste_both(stg, gres, count);
	run_commands(stg, S_PA, count);
}

int			get_prev_i(t_stack *st, int index)
{
	if (index + 1 >= (int)st->pos)
		return (0);
	return (index + 1);
}
