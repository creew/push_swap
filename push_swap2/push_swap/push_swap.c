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


int		paste_optimal(t_stack *st1, t_stack *st2)
{
	(void)st1;
	(void)st2;


	return (0);
}

int		find_place_to_paste(t_stack *st1, int val)
{
	size_t	size;
	size_t	pos;

	pos = st1->pos - 1;
	size = st1->pos;
	while (size--)
	{


	}



}

int		find_optimal(t_stack *st1, t_stack *st2)
{
	(void)st1;
	int		size;
	int		val;
	int		s2;
	int		s1;

	size = (int)st2->pos;
	while (size--)
	{
		val = st2->stack[size];
		s2 = ft_min((int)st2->pos - 1 - size, size + 1);
		s1 = find_place_to_paste(st1, val);


	}
	return (0);
}

int		is_cycle_sorted(t_stack *st, int start)
{
	int	end;
	int prev_val;

	prev_val = st->stack[start];
	end = start == 0 ? 0 : start;
	start = start == 0 ? (int)st->pos - 1 : start - 1;
	while (start != end)
	{
		if (prev_val > st->stack[start])
			return (0);
		prev_val = st->stack[start];
		start = start == 0 ? (int)st->pos - 1 : start - 1;
	}
	return (1);
}

int 	find_min_index(t_stack *st)
{
	size_t	count;
	int		min;
	int		blocked;

	blocked = 0;
	min = st->pos ? (int)st->pos - 1 : -1;
	count = st->pos;
	while (count--)
	{
		if (st->stack[count] < st->stack[min])
		{
			min = (int)count;
			blocked = 1;
		}
		else if (st->stack[count] == st->stack[min])
		{
			if (!blocked)
			{
				min = (int)count;
				blocked = 1;
			}
		}
		else
			blocked = 0;
	}
	return (min);
}

void	sort3items(t_stack *st, int *count)
{
	int	min_index;

	if (st->pos == 2)
	{
		if (!is_stack_sorted(st, 2, 1))
			run_commands(st, NULL, S_SA, count);
	}
	if (st->pos == 3)
	{
		if ((min_index = find_min_index(st)) != -1)
		{
			if (!is_cycle_sorted(st, min_index))
				run_commands(st, NULL, S_SA, count);
		}
	}
}

int 	normalize_stack(t_stack *st, int *count)
{
	int	min;
	int	n;

	min = find_min_index(st);
	if (min != (int)st->pos - 1)
	{
		if ((int)st->pos - 1 - min < min - 0 + 1)
		{
			n = (int)st->pos - 1 - min;
			while (n--)
				run_commands(st, NULL, S_RA, count);
		}
		else
		{
			n = min - 0 + 1;
			while (n--)
				run_commands(st, NULL, S_RRA, count);
		}
	}
	return (0);
}

int		calc_optimal(t_stack *st1, t_stack *st2)
{
	size_t	size;
	int		count;

	count = 0;
	size = st1->pos;
	while (size-- > 3)
		run_commands(st1, st2, S_PB, &count);
	sort3items(st1, &count);
	while (st2->pos)
	{
		find_optimal(st1, st2);
		paste_optimal(st1, st2);
	}
	normalize_stack(st1, &count);
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
