/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:57:55 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/21 15:57:56 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		run_commands(t_stack *st1, t_stack *st2, int cmd, int *count)
{
	int val;

	if (cmd == S_SA || cmd == S_SS)
		stack_swap(st1);
	if (cmd == S_SB || cmd == S_SS)
		stack_swap(st2);
	if (cmd == S_PA)
		if (stack_pop(st2, &val) == RET_OK)
			stack_push(st1, val);
	if (cmd == S_PB)
		if (stack_pop(st1, &val) == RET_OK)
			stack_push(st2, val);
	if (cmd == S_RA || cmd == S_RR)
		stack_rotate(st1);
	if (cmd == S_RB || cmd == S_RR)
		stack_rotate(st2);
	if (cmd == S_RRA || cmd == S_RRR)
		stack_rrotate(st1);
	if (cmd == S_RRB || cmd == S_RRR)
		stack_rrotate(st2);
	if (count)
		*count = *count + 1;
	return (RET_OK);
}