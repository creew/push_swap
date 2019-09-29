/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 10:56:19 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/29 14:24:04 by eklompus         ###   ########.fr       */
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
			mid = st1->stack[st1->pos - ++count];
			cc = 0;
			diff = 0;
			while (cc < end)
			    st1->stack[st1->pos - ++cc] < mid ? diff-- : diff++;
			if (ABS(diff) < min)
			{
				min = ABS(diff);
				pos = count;
			}
		}
	}
	return (st1->stack[st1->pos - pos]);
}

int		sort3firstmax(t_stack *st1, t_stack *st2, int *ops, int b)
{
	int		v1;
	int 	v2;
	int 	v3;

	v1 = st1->stack[st1->pos - 1];
	v2 = st1->stack[st1->pos - 2];
	v3 = st1->stack[st1->pos - 3];
	if ((b ? v1 <= v2 : v1 >= v2) && (b ? v1 <= v3 : v1 >= v3))
	{
		if (st1->pos == 3)
		{
			run_commands(st1, st2, S_RA, ops);
		}
		else
		{
			run_commands(st1, st2, S_SA, ops);
			run_commands(st1, st2, S_RA, ops);
			run_commands(st1, st2, S_SA, ops);
			run_commands(st1, st2, S_RRA, ops);
		}
		if (is_stack_sorted(st1, 2, b) != RET_OK)
			run_commands(st1, st2, S_SA, ops);
	}
	return (RET_OK);
}

int		sort3midmax(t_stack *st1, t_stack *st2, int *ops, int b)
{
	int		v1;
	int 	v2;
	int 	v3;

	v1 = st1->stack[st1->pos - 1];
	v2 = st1->stack[st1->pos - 2];
	v3 = st1->stack[st1->pos - 3];
	if ((b ? v2 <= v1 : v2 >= v1) && (b ? v2 <= v3 : v2 >= v3))
	{
		if (st1->pos == 3)
		{
			run_commands(st1, st2, S_RRA, ops);
		}
		else
		{
			run_commands(st1, st2, S_RA, ops);
			run_commands(st1, st2, S_SA, ops);
			run_commands(st1, st2, S_RRA, ops);
		}
		if (is_stack_sorted(st1, 2, b) != RET_OK)
			run_commands(st1, st2, S_SA, ops);
	}
	return (RET_OK);
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
		sort3firstmax(st1, st2, ops, b);
	}
	else if ((b ? v2 <= v1 : v2 >= v1) && (b ? v2 <= v3 : v2 >= v3))
	{
		sort3midmax(st1, st2, ops, b);
	}
	else if ((b ? v3 <= v1 : v3 >= v1) && (b ? v3 <= v2 : v3 >= v2))
	{
		if (is_stack_sorted(st1, 2, b) != RET_OK)
			run_commands(st1, st2, S_SA, ops);
	}
	return (RET_OK);
}

int		get_max_in_stack(t_stack *st, size_t size)
{
	int		max;
	size_t	count;

	count = size;
	max = -MAX_INTMIN;

	while (count)
	{
		if (st->stack[count - 1] > max)
			max = st->stack[count - 1];
		count--;
	}
	return (max);

}

int		get_more_in_stack(t_stack *st, int val, size_t size)
{
	size_t	count;

	count = size;
	while (count)
	{
		if (val > st->stack[--count])
			return (1);
	}
	return (0);

}

int		find_place(t_stack *st, size_t size, int val, int bord)
{
	size_t		count;
	int			ret;

	ret = MAX_INTMAX;
	count = bord;
	while (count > 0)
	{
		count--;
		if (val > st->stack[st->pos - (size - count)] && (ret = count))
			break;
	}
	count = size;
	while (size > bord && ret == MAX_INTMAX)
	{
		count--;
		if (val > st->stack[st->pos - (size - count)] && (ret = count))
			break;
	}
	if (ret == MAX_INTMAX)
		return (MAX_INTMAX);
	if ((size - ret) < ret)
		return (-ret);
	return (ret);
}

int		find_solution(t_stack *st1, t_stack *st2, size_t end, int *ops)
{
	int val;
	int len;
	int f;
	int ret;
	int bord;
	int shift;

	bord = 0;
	ret = 0;
	f = end == st1->pos;
	while (end != 1 || is_stack_sorted(st1, end, 0) != RET_OK)
	{
		val = st1->stack[st1->pos - 1];
		if (!ret && val == get_max_in_stack(st1, end) )
		{
			run_commands(st1, st2, S_RA, ops);
			ret = 1;
		}
		else
		{
			len = 0;
			if ((shift = find_place(st2, st2->pos, val, bord)) != MAX_INTMAX || st2->pos < 2)
			{
				if (shift > 0)
				{
					while (shift--)
					{
						run_commands(st1, st2, S_RB, ops);
						bord++;
					}
				}
				else if (shift < 0)
				{
					while (shift++)
					{
						run_commands(st1, st2, S_RRB, ops);
						bord--;
					}
				}
				run_commands(st1, st2, S_PB, ops);
				if (st2->pos == 2 && is_stack_sorted(st2, 2, 1))
					run_commands(st1, st2, S_SB, ops);
			}
			else
			{
				run_commands(st1, st2, S_PB, ops);
				run_commands(st1, st2, S_RB, ops);
			}
		}
		end--;
	}
	if (bord < 0)
	{
		while(bord)
		{
			run_commands(st1, st2, S_RB, ops);
			bord++;
		}
	}
	else if (bord > 0)
	{
		while(bord)
		{
			run_commands(st1, st2, S_RRB, ops);
			bord++;
		}
	}
	if  (!f && ret)
		run_commands(st1, st2, S_RRA, ops);
	while (st2->pos)
		run_commands(st1, st2, S_PA, ops);
	return (0);
}

int		find_optimal_solution(t_stack *st1, t_stack *st2, size_t end,
								 int *ops)
{
	int		pivot;
	size_t	count;
	size_t	half_len;

	if (end > 1 && is_stack_sorted(st1, end, 0) != RET_OK)
	{
		if (end == 2)
			return (run_commands(st1, st2, S_SA, ops));

		if (end == 3)
			return (find3sol(st1, st2, ops, 0));

		if (end < 20)
			return (find_solution(st1, st2, end, ops));

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

		if (half_len == 3)
			find3sol(st2, st1, ops, 1);

		count = 0;
		while (count++ < half_len)
			run_commands(st1, st2, S_PA, ops);

		find_optimal_solution(st1, st2, half_len, ops);

		count = 0;
		while (count++ < half_len)
			run_commands(st1, st2, S_RA, ops);

		find_optimal_solution(st1, st2, end - half_len, ops);

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
		//find_optimal_solution(&st1, &st2, st1.pos, &ops);
		find_solution(&st1, &st2, st1.pos, &ops);
		ft_putnbr(ops);
		ft_putendl("");
		print_stack(&st1, &st2);
	}
	return (0);
}