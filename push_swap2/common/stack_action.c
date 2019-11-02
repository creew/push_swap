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

const char *g_operations[] = {"sa", "sb", "ss",	 "pa",	"pb", "ra",
							  "rb", "rr", "rra", "rrb", "rrr"};

int		run_commands(t_stack *st1, t_stack *st2, int cmd, int *count)
{
	int val;

	ft_putendl(g_operations[cmd - S_SA]);
	//print_stack(st1, st2);

	if ((cmd == S_SA || cmd == S_SS) && st1)
		stack_swap(st1);
	if ((cmd == S_SB || cmd == S_SS) && st2)
		stack_swap(st2);
	if (cmd == S_PA && st1 && st2)
		if (stack_pop(st2, &val) == RET_OK)
			stack_push(st1, val);
	if (cmd == S_PB && st1 && st2)
		if (stack_pop(st1, &val) == RET_OK)
			stack_push(st2, val);
	if ((cmd == S_RA || cmd == S_RR) && st1)
		stack_rotate(st1);
	if ((cmd == S_RB || cmd == S_RR) && st2)
		stack_rotate(st2);
	if ((cmd == S_RRA || cmd == S_RRR) && st1)
		stack_rrotate(st1);
	if ((cmd == S_RRB || cmd == S_RRR) && st2)
		stack_rrotate(st2);
	if (count)
		*count = *count + 1;
	return (RET_OK);
}