/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:01:35 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/02 17:01:36 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Перемещает из стэка а в стэк б все элементы кроме отсортированного подмассива
 * @param stg глобальная структура
 * @param size размер стэка а
 * @param count подсчет количетсва выполненных команд
 * @param arr отсортированный подмассив
 */
void transfer_not_sorted(t_stg* stg, size_t size, int* count, const int* arr)
{
	int use_med;
	int med;

	use_med = find_med_val(&stg->st1, arr, &med);
	while (size--)
	{
		if (arr[size]) {
			if (size != 0)
				run_commands(stg, S_RA, count);
		}
		else
		{
			run_commands(stg, S_PB, count);
			if (use_med)
			{
				if (stg->st2.stack[stg->st2.size - 1] < med)
				{
					if (size > 0 && arr[size - 1])
					{
						size--;
						run_commands(stg, S_RR, count);
					}
					else
						run_commands(stg, S_RB, count);
				}
			}
		}
	}
}

int			calc_optimal(t_stg *stg)
{
	size_t	size;
	int		count;
	t_diff	gres;
	int 	len;
	int 	*arr;

	count = 0;
	if (!is_stack_sorted_index(&stg->st1))
	{
		size = stg->st1.pos;
		arr = find_max_sorted(&stg->st1, &len);
		if (arr && len > 3)
		{
			transfer_not_sorted(stg, size, &count, arr);
		}
		else
		{
			while (size-- > 3 && !is_stack_sorted_index(&stg->st1))
				run_commands(stg, S_PB, &count);
			sort3items(&stg->st1, &count, stg, S_SA);
		}
		ft_memdel((void **)&arr);
		while (stg->st2.pos)
		{
			find_optimal(&stg->st1, &stg->st2, &gres);
			paste_optimal(stg, &gres, &count);
		}
	}
	normalize_stack(stg, &count);
	return (count);
}
