/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readarg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:01:30 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/25 09:50:13 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		arg_read(int n, char *av[], t_stack *st1)
{
	int		res;
	int		ret;

	ret = ERROR_NO_ARGUMENTS;
	while (n > 1)
	{
		if ((ret = safe_atoi(av[n - 1], &res)) != RET_OK)
			break ;
		stack_push(st1, res);
		n--;
	}
	return (ret);
}

void	print_stack(t_stack *st1, t_stack *st2)
{
	size_t c1;
	size_t c2;

	c1 = st1->pos;
	c2 = st2->pos;
	ft_putendl("st1      st2");
	while (c1 || c2 )
	{
		c1 ? ft_putnbr(st1->stack[--c1]) : ft_putstr("     ");
		ft_putstr("   ");
		c2 ? ft_putnbr(st2->stack[--c2]) : ft_putstr("     ");
		ft_putendl("");
	}
}

int		run_command(t_stack *st, int cmd, int *count)
{
	int val;

	if (cmd == SC_SWAP)
		stack_swap(st);
	else if (cmd == SC_ROT)
		stack_rotate(st);
	else if (cmd == SC_RROT)
		stack_rrotate(st);
	else
		return (ERROR_INVALID_VAL);
	if (count)
		*count = *count + 1;
	return (RET_OK);
}


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