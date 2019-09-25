/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 10:56:19 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/25 14:18:22 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


int		find_middle(t_stack *st1, size_t end)
{
	/*
	size_t	pos;
	long	sum;
	int		mid;
	int		min;
	size_t	mid_pos;

	min = MAX_INTMAX;
	pos = 0;
	sum = 0;
	while (pos++ < end)
		sum += st1->stack[st1->pos - pos];
	mid = sum / end;
	mid_pos = 0;
	pos = 0;
	while (pos++ < end)
	{
		if (ABS(st1->stack[st1->pos - pos] - mid) < min)
		{
			min = ABS(st1->stack[st1->pos - pos] - mid);
			mid_pos = st1->pos - pos;
		}
	}
	return (st1->stack[mid_pos]);
	 */
	return (st1->stack[st1->pos - end - 1]);
}

int 	find3sol(t_stack *st1, t_stack *st2, int *ops, int b)
{
	int		v1;
	int 	v2;
	int 	v3;

	v1 = st1->stack[st1->pos - 1];
	v2 = st1->stack[st1->pos - 2];
	v3 = st1->stack[st1->pos - 3];
	if (b ? v1 <= v2 : v1 >= v2 && b ? v1 <= v3 : v1 >= v3 && v2 != v3)
	{
		run_commands(st1, st2, S_RA, ops);
		if (!is_stack_sorted(st1, 2, b))
			run_commands(st1, st2, S_SA, ops);
	}
	else if (b ? v2 <= v1 : v2 >= v1 && b ? v2 <= v3 : v2 >= v3 && v1 != v3)
	{
		run_commands(st1, st2, S_RRA, ops);
		if (!is_stack_sorted(st1, 2, b))
			run_commands(st1, st2, S_SA, ops);
	}
	else if (b ? v3 <= v1 : v3 >= v1 && b ? v3 <= v2 : v3 >= v2 && v1 != v2)
	{
		if (!is_stack_sorted(st1, 2, b))
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

	if (end > 1 && is_stack_sorted(st1, end, backward) != RET_OK)
	{
		if (end == 2)
			return (run_commands(st1, st2, S_SA, ops));
		if (end == 3 && st1->pos == 3)
			return (find3sol(st1, st2, ops, backward));

		pivot = find_middle(st1, end);
		half_len = 0;
		count = 0;
		while (count < end)
		{
			if (st1->stack[st1->pos - 1] < pivot)
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

		find_optimal_solution(st1, st2, end - half_len, ops, 1);

		count = 0;
		while (count++ < half_len)
			run_commands(st1, st2, S_RRA, ops);

	}
	return (0);
}


int		main(int ac, char *av[])
{
	t_stack st1;
	t_stack st2;
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