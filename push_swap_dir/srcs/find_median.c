/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_median.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 12:26:34 by eklompus          #+#    #+#             */
/*   Updated: 2020/01/26 12:26:34 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		cmp_func(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

/**
 * Находит среднее значение в стеке с учетом количества элементов
 * и отсортированного подмассива
 * @param stack стэк
 * @param max_sorted отсортированный подмассив
 * @param res среднее значение
 * @return результат выполнения 0 в случае неудачи
 */
int				find_med_val(t_stack *stack, const int *max_sorted, int *res)
{
	int		*new_arr;
	size_t	index;
	int 	iindex;

	new_arr = (int *)ft_calloc(stack->size, sizeof(int));
	if (new_arr)
	{
		index = -1;
		iindex = -1;
		while (++index < stack->size)
		{
			if (!max_sorted[index])
				new_arr[++iindex] = stack->stack[index];
		}
		if (iindex != 0)
		{
			ft_qsort(new_arr, iindex, sizeof(int), cmp_func);
			*res = new_arr[iindex / 2];
		}
		ft_memdel((void **)&new_arr);
		return (iindex != 0);
	}
	return (0);
}
