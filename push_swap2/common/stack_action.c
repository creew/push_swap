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
#include "ft_printf.h"

static void	print_command(int cmd, int is_colorized)
{
	char	*str;

	str = get_action_str(cmd);
	if (is_colorized)
	{
		if (cmd == S_SA || cmd == S_RA || cmd == S_RRA)
			ft_printf("{red}%s{eoc}\n", str);
		if (cmd == S_SB || cmd == S_RB || cmd == S_RRB)
			ft_printf("{blue}%s{eoc}\n", str);
		if (cmd == S_SS || cmd == S_RR || cmd == S_RRR)
			ft_printf("{green}%s{eoc}\n", str);
		if (cmd == S_PA || cmd == S_PB)
			ft_printf("{cyan}%s{eoc}\n", str);
	}
	else
		ft_putendl(str);
}

int			run_commands(t_stg *stg, int cmd, int *count)
{
	int val;

	if (count)
		print_command(cmd, stg->is_colorized);
	if (cmd == S_SA || cmd == S_SS)
		stack_swap(&stg->st1);
	if (cmd == S_SB || cmd == S_SS)
		stack_swap(&stg->st2);
	if (cmd == S_PA && (stack_pop(&stg->st2, &val) == RET_OK))
		stack_push(&stg->st1, val);
	if (cmd == S_PB && (stack_pop(&stg->st1, &val) == RET_OK))
		stack_push(&stg->st2, val);
	if (cmd == S_RA || cmd == S_RR)
		stack_rotate(&stg->st1);
	if (cmd == S_RB || cmd == S_RR)
		stack_rotate(&stg->st2);
	if (cmd == S_RRA || cmd == S_RRR)
		stack_rrotate(&stg->st1);
	if (cmd == S_RRB || cmd == S_RRR)
		stack_rrotate(&stg->st2);
	if (count)
		*count = *count + 1;
	if (stg->is_show_stat)
		print_stacks(stg);
	return (RET_OK);
}
