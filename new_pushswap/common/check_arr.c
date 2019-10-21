/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:18:50 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/21 15:18:51 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int is_arr_sorts(t_action_array *act, t_stack *st_orig, t_stack *st1, t_stack *st2)
{
	t_uint	i;
	t_uint	action;

	st1->pos = 0;
	st2->pos = 0;
	i = 0;
	while (i < act->pos)
	{
		if (!(i & 1u))
			action = (act->array[i >> 1u]) >> 4u;
		else
			action = (act->array[i >> 1u]) & 0xFu;
		run_commands(st1, st2, action, NULL);
		i++;
	}
	return (is_stack_sorted(st1, st1->pos, 0) == RET_OK);
}
