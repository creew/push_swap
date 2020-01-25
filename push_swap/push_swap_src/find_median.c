//
// Created by eklompus on 25.01.2020.
//

#include "push_swap.h"

static int		cmp_func(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int				find_med_val(t_stack *stack, const int *max_sorted, int *res)
{
	int		*new_arr;
	size_t	index;
	int 	iindex;

	new_arr = (int *)ft_calloc(stack->pos, sizeof(int));
	if (new_arr)
	{
		index = -1;
		iindex = -1;
		while (++index < stack->pos)
		{
			if (!max_sorted[index])
				new_arr[++iindex] = stack->stack[index];
		}
		if (iindex != 0)
		{
			ft_bubble_sort(new_arr, iindex, sizeof(int), cmp_func);
			*res = new_arr[iindex / 2];
		}
		ft_memdel((void **)&new_arr);
		return (iindex != 0);
	}
	return (0);
}

