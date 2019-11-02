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

int		find_min_diff(int s1[], int s2[], t_diff *d)
{
	t_diff	temp;

	set_tdiff(d, s1[0], s2[0]);
	set_tdiff(&temp, s1[0], s2[1]);
	if (get_actual_diff(&temp) < get_actual_diff(d))
		set_tdiff(d, s1[0], s2[1]);
	set_tdiff(&temp, s1[1], s2[0]);
	if (get_actual_diff(&temp) < get_actual_diff(d))
		set_tdiff(d, s1[1], s2[0]);
	set_tdiff(&temp, s1[1], s2[1]);
	if (get_actual_diff(&temp) < get_actual_diff(d))
		set_tdiff(d, s1[1], s2[1]);
	return (0);
}
