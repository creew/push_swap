/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 14:23:56 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/29 14:23:57 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		main(int ac, char *av[])
{
	t_stack	st1;
	t_stack	st2;
	int		ret;

	stack_init(&st1);
	stack_init(&st2);
	ret = arg_read(ac, av, &st1);
	if (ret == RET_OK)
		calc_optimal(&st1, &st2);
	else if (ret != ERROR_NO_ARGUMENTS)
		ft_putendl("Error");
	stack_free(&st1);
	stack_free(&st2);
	return (0);
}
