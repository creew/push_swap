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
#include <stdio.h>

int		paste_optimal(t_stack *st1, t_stack *st2, t_diff *gres, int *count)
{
	if (gres->s1_diff >= 0 && gres->s2_diff >= 0)
	{
		while (gres->s1_diff && gres->s2_diff)
		{
			run_commands(st1, st2, S_RR, count);
			gres->s1_diff--;
			gres->s2_diff--;
		}
		while (gres->s1_diff--)
			run_commands(st1, st2, S_RA, count);
		while (gres->s2_diff--)
			run_commands(st1, st2, S_RB, count);
	}
	else if (gres->s1_diff <= 0 && gres->s2_diff <= 0)
	{
		while (gres->s1_diff && gres->s2_diff)
		{
			run_commands(st1, st2, S_RRR, count);
			gres->s1_diff++;
			gres->s2_diff++;
		}
		while (gres->s1_diff++ < 0)
			run_commands(st1, st2, S_RRA, count);
		while (gres->s2_diff++ < 0)
			run_commands(st1, st2, S_RRB, count);
	}
	else
	{
		while (gres->s1_diff < 0)
		{
			run_commands(st1, st2, S_RRA, count);
			gres->s1_diff++;
		}
		while (gres->s2_diff < 0)
		{
			run_commands(st1, st2, S_RRB, count);
			gres->s2_diff++;
		}
		while (gres->s1_diff > 0)
		{
			run_commands(st1, st2, S_RA, count);
			gres->s1_diff--;
		}
		while (gres->s2_diff > 0)
		{
			run_commands(st1, st2, S_RB, count);
			gres->s2_diff--;
		}
	}
	run_commands(st1, st2, S_PA, count);
	return (0);
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

int		get_prev_index(t_stack *st, int index)
{
	if (index + 1 >= (int)st->pos) return (0);
	return (index + 1);
}

int		find_place_to_paste(t_stack *st, int val, int vals[2])
{
	int		pos;
	int		min_index;

	min_index = find_min_index(st);
	vals[0] = (int)st->pos - 1 - min_index;
	vals[1] = -(min_index + 1);
	if (min_index != -1)
	{
		pos = st->pos;
		while (pos--)
		{
			if (val >= st->stack[get_prev_index(st, pos)] && val <= st->stack[pos])
			{
				vals[0] = (int)st->pos - 1 - pos;
				break;
			}
		}
		pos = 0;
		while (pos < (int)st->pos)
		{
			if (val >= st->stack[get_prev_index(st, pos)] && val <= st->stack[pos])
			{
				vals[1] = -(pos + 1);
				break;
			}
			pos++;
		}
	}
	return (0);
}

int		get_diff(t_diff *d)
{
	if (d->s1_diff >= 0 && d->s2_diff >= 0)
		return (ft_max(d->s1_diff, d->s2_diff));
	if (d->s1_diff <= 0 && d->s2_diff <= 0)
		return (ft_max(ft_abs(d->s1_diff), ft_abs(d->s2_diff)));
	return (ft_abs(d->s1_diff) + ft_abs(d->s2_diff));
}

void	set_tdiff(t_diff *d, int s1_diff, int s2_diff)
{
	d->s1_diff = s1_diff;
	d->s2_diff = s2_diff;
}

int		find_min_diff(int s1[], int s2[], t_diff *d)
{
	t_diff	temp;

	set_tdiff(d, s1[0], s2[0]);
	set_tdiff(&temp, s1[0], s2[1]);
	if (get_diff(&temp) < get_diff(d))
		set_tdiff(d, s1[0], s2[1]);
	set_tdiff(&temp, s1[1], s2[0]);
	if (get_diff(&temp) < get_diff(d))
		set_tdiff(d, s1[1], s2[0]);
	set_tdiff(&temp, s1[1], s2[1]);
	if (get_diff(&temp) < get_diff(d))
		set_tdiff(d, s1[1], s2[1]);
	return (0);
}

int		find_optimal(t_stack *st1, t_stack *st2, t_diff *gres)
{
	int		size;
	t_diff	res;
	int		s1[2];
	int		s2[2];

	size = (int)st2->pos;
	if (size--)
	{
		s2[0] = (int)st2->pos - 1 - size;
		s2[1] = -(size + 1);
		find_place_to_paste(st1, st2->stack[size], s1);
		find_min_diff(s1, s2, gres);
		while (size--)
		{
			s2[0] = (int)st2->pos - 1 - size;
			s2[1] = -(size + 1);
			find_place_to_paste(st1, st2->stack[size], s1);
			find_min_diff(s1, s2, &res);
			if (get_diff(&res) < get_diff(gres))
				set_tdiff(gres, res.s1_diff, res.s2_diff);
		}
	}
	return (0);
}

int		is_cycle_sorted(t_stack *st, int start)
{
	int		end;
	int		prev_val;

	prev_val = st->stack[start];
	end = start;
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

void	sort3items(t_stack *st, int *count)
{
	int	min_index;

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
		if ((int)st->pos - 1 - min < min + 1)
		{
			n = (int)st->pos - 1 - min;
			while (n--)
				run_commands(st, NULL, S_RA, count);
		}
		else
		{
			n = min + 1;
			while (n--)
				run_commands(st, NULL, S_RRA, count);
		}
	}
	return (0);
}

int		is_stack_sorted_index(t_stack *st)
{
	int		min_index;

	if ((min_index = find_min_index(st)) != -1)
	{
		if (is_cycle_sorted(st, min_index))
			return (1);
	}
	return (0);
}


int		calc_optimal(t_stack *st1, t_stack *st2)
{
	size_t	size;
	int		count;
	t_diff	gres;

	count = 0;
	if (!is_stack_sorted_index(st1))
	{
		size = st1->pos;
		while (size-- > 3 && !is_stack_sorted_index(st1))
			run_commands(st1, st2, S_PB, &count);
		sort3items(st1, &count);
		while (st2->pos)
		{
			find_optimal(st1, st2, &gres);
			paste_optimal(st1, st2, &gres, &count);
		}
	}
	normalize_stack(st1, &count);
	return (count);
}

int		main(int ac, char *av[])
{
	t_stack	st1;
	t_stack	st2;

	stack_init(&st1);
	stack_init(&st2);
	setbuf(stdout, NULL);
	if (arg_read(ac, av, &st1) == RET_OK)
	{
		calc_optimal(&st1, &st2);
		//print_stack(&st1, &st2);
	}
	return (0);
}
