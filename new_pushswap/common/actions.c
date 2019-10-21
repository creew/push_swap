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

int		actions_clone_val(t_action_array *act, t_uint val)
{
	t_uchar		*arr;

	arr = ft_memalloc(sizeof(char) * ((act->pos + 1) / 2 + 1));
	if (!arr)
		return (ERROR_ENOMEM);
	ft_memcpy(arr, act->array, (act->pos + 1) / 2);
	act->array = arr;
	if (!(act->pos & 1u))
		act->array[act->pos / 2] = val << 4u;
	else
		act->array[act->pos / 2] |= val;
	act->pos++;
	return (RET_OK);
}

int 	add_possible_values()
{



}
