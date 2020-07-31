/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_max_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 12:26:46 by eklompus          #+#    #+#             */
/*   Updated: 2020/01/26 12:26:49 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_seq(int *arr, size_t size)
{
	while (size--)
		*arr++ = 1;
}

static int	remove_unused(t_stack *stack, int *arr, size_t size, int max)
{
	int		max_size;

	(void)stack;
	max_size = max;
	while (size--)
	{
		if (arr[size] != max)
			arr[size] = 0;
		else
			max--;
	}
	return (max_size);
}

static int	find_max_seq(t_stack *stack, size_t start, int *tmp, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	index_i;
	size_t	index_j;
	int		max;

	init_seq(tmp, stack->pos);
	j = 0;
	max = 0;
	while (++j < stack->pos)
	{
		i = -1;
		while (++i < j)
		{
			index_i = (start + i) % size;
			index_j = (start + j) % size;
			if (stack->stack[index_j] <= stack->stack[index_i] &&
				tmp[index_j] <= tmp[index_i])
			{
				tmp[index_j] = tmp[index_i] + 1;
				if (tmp[index_j] > max)
					max = tmp[index_j];
			}
		}
	}
	return (remove_unused(stack, tmp, size, max));
}

int			*find_max_sorted(t_stack *stack, int *maxlen)
{
	size_t	index;
	size_t	size;
	int		*resarr;
	int		curlen;

	size = stack->pos;
	*maxlen = 0;
	resarr = ft_calloc(size * 2, sizeof(int));
	if (resarr)
	{
		index = -1;
		while (++index < size)
		{
			if ((curlen = find_max_seq(stack, index, resarr + size, size)) >
				*maxlen)
			{
				*maxlen = curlen;
				ft_intmove(resarr, resarr + size, size);
			}
		}
	}
	return (resarr);
}
