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

int			calc_optimal(t_stg *stg)
{
	size_t	size;
	int		count;
	t_diff	gres;
	int 	len;
	int 	*arr;
	int 	med;
	int		use_med;

	count = 0;
	if (!is_stack_sorted_index(&stg->st1))
	{
		size = stg->st1.pos;
		arr = find_max_sorted(&stg->st1, &len);
		if (arr && len >= 3)
		{
			use_med = find_med_val(&stg->st1, arr, &med);
			while (size-- && !is_stack_sorted_index(&stg->st1))
			{
				if (arr[size])
					run_commands(stg, S_RA, &count);
				else
				{
					run_commands(stg, S_PB, &count);
					if (use_med) {
						if (stg->st2.stack[stg->st2.pos - 1] < med)
						{
							if (size > 0 && !is_stack_sorted_index(&stg->st1) && arr[size - 1])
							{
								size--;
								run_commands(stg, S_RR, &count);
							}
							else
								run_commands(stg, S_RB, &count);
						}
					}
				}
			}
		}
		else
		{
			while (size-- > 3 && !is_stack_sorted_index(&stg->st1))
				run_commands(stg, S_PB, &count);
			sort3items(stg, &count);
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
