/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 14:23:56 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/29 14:23:57 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	cp_stack(t_stack *dst, t_stack *src)
{
	int		size;

	size = 0;
	dst->pos = 0;
	while (size < src->pos)
	{
		stack_push(dst, src->stack[size]);
		size++;
	}
}

int 	get_index_number(int n, t_stack *st1, t_stack *st2)
{


}

int		get_sum_permutation(t_stack *st1, t_stack *st2)
{
	int i;

	i = st1->pos;
	while (i--)
	{
		get_index_number(st1->stack[i], st1, st2);
	}
	i = st2->pos;
	while (i--)
	{
		get_index_number(st2->stack[i], st1, st2);
	}
}

int		find_optimal_val(t_stack *st1, t_stack *st2, t_stack *t1, t_stack *t2, int *op)
{
	int i;
	int min;
	int val;

	i = S_SA;
	cp_stack(t1, st1);
	cp_stack(t2, st2);
	run_commands(t1, t2, i, NULL);
	min = get_sum_permutation(t1, t2);
	*op = i;
	while (++i <= S_RRR)
	{
		cp_stack(t1, st1);
		cp_stack(t2, st2);
		run_commands(t1, t2, i, NULL);
		val = get_sum_permutation(t1, t2);
		if (val < min)
		{
			min = val;
			*op = i;
		}
	}
	return (min);
}

int 	calc_optimal(t_stack *st1, t_stack *st2)
{
	int val;
	int	op;
	int	count;
	t_stack t1;
	t_stack t2;

	stack_init(&t1);
	stack_init(&t2);
	count = 0;
	while ((val = find_optimal_val(st1, st2, &t1, &t2, &op)) != 0)
	{
		run_commands(st1, st2, op, &count);
	}
	stack_free(&t1);
	stack_free(&t2);
	return (count);
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
		//find_optimal_solution(&st1, &st2, st1.pos, &ops);
		ops = calc_optimal(&st1, &st2);
		ft_putnbr(ops);
		ft_putendl("");
		print_stack(&st1, &st2);
	}
	return (0);
}
