#include "push_swap.h"

static void	find_left_values(t_stack *st, int val, int *vals)
{
	int pos;

	pos = st->pos;
	while (pos--)
	{
		if (val >= st->stack[get_prev_i(st, pos)] && val <= st->stack[pos])
		{
			*vals = (int)st->pos - 1 - pos;
			break ;
		}
	}
}

static void	find_right_values(t_stack *st, int val, int *vals)
{
	int pos;

	pos = 0;
	while (pos < (int)st->pos)
	{
		if (val >= st->stack[get_prev_i(st, pos)] && val <= st->stack[pos])
		{
			*vals = -(pos + 1);
			break ;
		}
		pos++;
	}
}

static int	find_place_to_paste(t_stack *st, int val, t_vals *vals)
{
	int		min_index;

	min_index = find_min_index(st);
	vals->up = (int)st->pos - 1 - min_index;
	vals->down = -(min_index + 1);
	if (min_index != -1)
	{
		find_left_values(st, val, &vals->up);
		find_right_values(st, val, &vals->down);
	}
	return (0);
}

int			find_optimal(t_stack *st1, t_stack *st2, t_diff *gres)
{
	int		size;
	t_diff	res;
	t_vals	left;
	t_vals	right;

	size = (int)st2->pos;
	if (size--)
	{
		right.up = (int)st2->pos - 1 - size;
		right.down = -(size + 1);
		find_place_to_paste(st1, st2->stack[size], &left);
		find_min_diff(&left, &right, gres);
		while (size--)
		{
			right.up = (int)st2->pos - 1 - size;
			right.down = -(size + 1);
			find_place_to_paste(st1, st2->stack[size], &left);
			find_min_diff(&left, &right, &res);
			if (get_actual_diff(&res) < get_actual_diff(gres))
				set_tdiff(gres, res.s1_diff, res.s2_diff);
		}
		return (1);
	}
	return (0);
}
