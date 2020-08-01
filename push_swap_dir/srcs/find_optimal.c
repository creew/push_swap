/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_optimal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:15:26 by eklompus          #+#    #+#             */
/*   Updated: 2020/01/29 15:15:27 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Находит количество операций для вставки значения вращая стэк вверх
 * @param st стэк
 * @param val значение
 * @param vals количество операций
 */
static void find_up_values(t_stack *st, int val, int *vals)
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

/**
 * Находит количество операций для вставки значения вращая стэк вниз
 * @param st стэк
 * @param val значение
 * @param vals количество операций
 */
static void find_down_values(t_stack *st, int val, int *vals)
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

/**
 * Находит количество операция для вставки значения
 * @param st стэк
 * @param val значение
 * @param vals структура хранящее количество операций для вставки вращая
 * 			стэк вверх и вниз
 * @return RET_OK - успешное завершение
 */
static int	find_place_to_paste(t_stack *st, int val, t_vals *vals)
{
	int		min_index;

	min_index = find_min_index(st);
	vals->up = (int)st->pos - 1 - min_index;
	vals->down = -(min_index + 1);
	if (min_index != -1)
	{
		find_up_values(st, val, &vals->up);
		find_down_values(st, val, &vals->down);
	}
	return (RET_OK);
}

/**
 * Находит элемент из стека б для вставки в стек а с наименьшим количеством
 * 		операций
 * @param st1 стэк а
 * @param st2 стэк б
 * @param gres
 * @return
 */
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
		return (RET_OK);
	}
	return (ERROR_GETEMPTY_STACK);
}
