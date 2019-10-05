/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_delall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 12:54:42 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/05 13:03:11 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stack_delall(t_ftstack **stack, void (*f)(void *))
{
	t_ftstack *st;

	st = *stack;
	while (st->pos)
	{
		if (f)
			f(st->data[st->pos - 1]);
		st->pos--;
	}
	ft_memdel((void **)stack);
	return (0);
}
