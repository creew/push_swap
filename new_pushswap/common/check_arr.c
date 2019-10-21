/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:18:50 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/21 15:18:51 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int is_arr_sorts(char *arr, int arr_size)
{
	int i;
	t_uint action;

	i = -1;
	while (++i < arr_size)
	{
		if (!(i & 1))
			action = ((t_uint)*arr) >> 4u;
		else
			action = ((t_uint)*arr++) & 0xFu;
		do_action(action);
	}



}
