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

/**
 * Инициализирует массив с длинами последовательностей единицами
 * @param arr массив
 * @param size размер массива
 * @param val значение для инициализации
 */
static void	init_seq(int *arr, size_t size, int val)
{
	while (size--)
		*arr++ = val;
}

/**
 * Обнуляет индексы порядка для немаксимальных последовательностей
 * @param arr массив с индексами порядка
 * @param size размер массива
 * @param max максимальная длина последовательности в массиве
 * @return максимальная длина последовательности в массиве
 */
static int	remove_unused(int *arr, size_t size, int max)
{
	size_t	size_orig;
	size_t	pos;
	size_t	index;
	int		max_orig;

	pos = size;
	size_orig = size;
	max_orig = max;
	while (pos-- > 0)
	{
		if (arr[pos] == max)
		{
			pos--;
			max--;
			size--;
			while (size > 0)
			{
				index = (pos + size_orig) % size_orig;
				if (max != 0 && arr[index] == max) {
					max--;
				}
				else {
					arr[index] = 0;
				}
				pos--;
				size--;
			}
			break;
		}
	}
	return (max_orig);
}

/**
 * Находит максимальную последовательность в стеке с учетом начальной позиции
 * @param stack стэк
 * @param start начальная позиция
 * @param tmp временный массив для хранения длин последовательностей
 * @param size размер стэка
 * @return длина найденной последовательности
 */
static int	find_max_seq(t_stack *stack, size_t start, int *tmp)
{
	size_t	i;
	size_t	j;
	size_t	index_i;
	size_t	index_j;
	int		max;
	int		found;

	init_seq(tmp, stack->size, 1);
	j = 0;
	max = 0;
	while (++j < stack->size)
	{
		found = 0;
		i = -1;
		while (++i < j)
		{
			index_i = (start + i) % stack->size;
			index_j = (start + j) % stack->size;
			if (stack->stack[index_j] <= stack->stack[index_i] &&
				tmp[index_j] <= tmp[index_i])
			{
				found = 1;
				tmp[index_j] = tmp[index_i] + 1;
				if (tmp[index_j] > max)
					max = tmp[index_j];
			}
		}
		if (found == 0)
			break;
	}
	return (remove_unused(tmp, stack->size, max));
}

/**
 * Функция находит максимальную длину последовательности в стеке
 * @param stack стэк
 * @param maxlen длина найденного подмассива
 * @return массив с индексами порядка
 */
int			*find_max_sorted(t_stack *stack, int *maxlen)
{
	size_t	index;
	int		*resarr;
	int		curlen;

	*maxlen = 0;
	resarr = ft_calloc(stack->size * 2, sizeof(int));
	if (resarr)
	{
		index = -1;
		while (++index < stack->size)
		{
			curlen = find_max_seq(stack, index, resarr + stack->size);
			if (curlen > *maxlen)
			{
				*maxlen = curlen;
				ft_intmove(resarr, resarr + stack->size, stack->size);
			}
		}
	}
	return (resarr);
}
