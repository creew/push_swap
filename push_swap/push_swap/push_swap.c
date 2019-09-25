/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 10:56:19 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/25 17:33:23 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


int		find_middle(t_stack *st1, size_t end)
{
	size_t	count;
	size_t	cc;
	int		mid;
	int		diff;
	size_t	pos;
	int		min;

	pos = 1;
	if (end > 1)
	{
		min = MAX_INTMAX;
		count = 0;
		while (count < end)
		{
			mid = st1->stack[st1->pos - count - 1];
			cc = 0;
			diff = 0;
			while (cc < end)
			{
				if (st1->stack[st1->pos - ++cc] < mid)
					diff--;
				else
					diff++;
			}
			if (ABS(diff) < min)
			{
				min = ABS(diff);
				pos = cc;
			}
			count++;
		}
	}
	return (st1->stack[st1->pos - pos]);
}

int 	find3sol(t_stack *st1, t_stack *st2, int *ops, int b)
{
	int		v1;
	int 	v2;
	int 	v3;

	v1 = st1->stack[st1->pos - 1];
	v2 = st1->stack[st1->pos - 2];
	v3 = st1->stack[st1->pos - 3];
	if (is_stack_sorted(st1, 3, b) == RET_OK)
		return (RET_OK);
	if ((b ? v1 <= v2 : v1 >= v2) && (b ? v1 <= v3 : v1 >= v3))
	{
		run_commands(st1, st2, S_RA, ops);
		if (is_stack_sorted(st1, 2, b) != RET_OK)
			run_commands(st1, st2, S_SA, ops);
	}
	else if ((b ? v2 <= v1 : v2 >= v1) && (b ? v2 <= v3 : v2 >= v3))
	{
		run_commands(st1, st2, S_RRA, ops);
		if (is_stack_sorted(st1, 2, b) != RET_OK)
			run_commands(st1, st2, S_SA, ops);
	}
	else if ((b ? v3 <= v1 : v3 >= v1) && (b ? v3 <= v2 : v3 >= v2))
	{
		if (is_stack_sorted(st1, 2, b) != RET_OK)
			run_commands(st1, st2, S_SA, ops);
	}
	return (RET_OK);
}


int		find_optimal_solution(t_stack *st1, t_stack *st2, size_t end,
								 int *ops, int backward)
{
	int		pivot;
	size_t	count;
	size_t	half_len;

	if (end > 1 && is_stack_sorted(st1, end, 0) != RET_OK)
	{
		if (end == 2)
			return (run_commands(st1, st2, S_SA, ops));
		if (end == 3 && st1->pos == 3)
			return (find3sol(st1, st2, ops, 0));

		pivot = find_middle(st1, end);
		half_len = 0;
		count = 0;
		while (count < end)
		{
			int val = st1->stack[st1->pos - 1];
			if (val < pivot)
			{
				run_commands(st1, st2, S_PB, ops);
				half_len++;
			}
			else
				run_commands(st1, st2, S_RA, ops);
			count++;
		}

		count = 0;
		while (count++ < (end - half_len))
			run_commands(st1, st2, S_RRA, ops);

		count = 0;
		while (count++ < half_len)
			run_commands(st1, st2, S_PA, ops);

		find_optimal_solution(st1, st2, half_len, ops, 0);

		count = 0;
		while (count++ < half_len)
			run_commands(st1, st2, S_RA, ops);

		find_optimal_solution(st1, st2, end - half_len, ops, 0);

		count = 0;
		while (count++ < half_len)
			run_commands(st1, st2, S_RRA, ops);

	}
	return (0);
}


int		main(int ac, char *av[])
{
	t_stack	st1;
	t_stack	st2;
	int		ops;

	ops = 0;
	stack_init(&st1);
	stack_init(&st2);
	if (arg_read(ac, av, &st1) == RET_OK)
	{
		find_optimal_solution(&st1, &st2, st1.pos, &ops, 0);
		ft_putnbr(ops);
		ft_putendl("");
		print_stack(&st1, &st2);
	}
	return (0);
}