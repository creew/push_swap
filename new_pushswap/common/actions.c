/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:47:12 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/21 17:47:13 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		add_val(t_action_array *act, t_uint val)
{
	t_uchar		*arr;

	if ((act->pos + 1) / 2 >= act->cap)
	{
		arr = ft_memalloc((act->pos + 1) / 2 + ACTIONS_SIZE);
		if (!arr)
			return (ERROR_ALLOCATING_STACK);
		ft_memcpy(arr, act->array, (act->pos + 1) / 2);
		ft_memdel((void **)&act->array);
		act->array = arr;
		act->cap = (act->pos + 1) / 2 + ACTIONS_SIZE;
	}
	if (!(act->pos & 1u))
		act->array[act->pos / 2] = val << 4u;
	else
		act->array[act->pos / 2] |= val;
	act->pos++;
	return (RET_OK);
}
