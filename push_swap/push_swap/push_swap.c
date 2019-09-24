/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 10:56:19 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/24 17:14:26 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


int		find_middle(t_stack *st1, size_t start, size_t size)
{
	size_t	pos;
	long	sum;
	int		mid;
	int		min;
	size_t	mid_pos;

	mid_pos = 0;
	pos = start;
	sum = 0;
	while (pos < size)
		sum += st1->stack[pos++];
	mid = sum / (size - start);
	sum = 0;
	while (pos < size)
	{
		if (ABS(st1->stack[pos] - mid) < min)
		{
			min		= st1->stack[pos] - mid;
			mid_pos = pos;
		}
		pos++;
	}
	return (mid_pos );
}

int		find_optimal_solution(t_stack *st1, t_stack *st2)
{
	int	pivot;
	if (st1->pos)
	{
		pivot = find_middle(st1, 0, st1->pos);

	}

}

int		main(int ac, char *av[])
{
	t_stack st1;
	t_stack st2;

	stack_init(&st1);
	stack_init(&st2);
	if (arg_read(ac, av, &st1) == RET_OK)
	{



	}
	return (0);
}