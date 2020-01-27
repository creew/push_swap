/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:16:21 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/02 17:16:22 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		get_actual_diff(t_diff *d)
{
	if (d->s1_diff >= 0 && d->s2_diff >= 0)
		return (ft_max(d->s1_diff, d->s2_diff));
	if (d->s1_diff <= 0 && d->s2_diff <= 0)
		return (ft_max(ft_abs(d->s1_diff), ft_abs(d->s2_diff)));
	return (ft_abs(d->s1_diff) + ft_abs(d->s2_diff));
}

void	set_tdiff(t_diff *d, int s1_diff, int s2_diff)
{
	d->s1_diff = s1_diff;
	d->s2_diff = s2_diff;
}

int		find_min_diff(t_vals *left, t_vals *right, t_diff *d)
{
	t_diff	temp;

	set_tdiff(d, left->up, right->up);
	set_tdiff(&temp, left->up, right->down);
	if (get_actual_diff(&temp) < get_actual_diff(d))
		set_tdiff(d, left->up, right->down);
	set_tdiff(&temp, left->down, right->up);
	if (get_actual_diff(&temp) < get_actual_diff(d))
		set_tdiff(d, left->down, right->up);
	set_tdiff(&temp, left->down, right->down);
	if (get_actual_diff(&temp) < get_actual_diff(d))
		set_tdiff(d, left->down, right->down);
	return (0);
}
