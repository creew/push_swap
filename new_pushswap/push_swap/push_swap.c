/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:54:47 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/21 14:54:51 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		main(int ac, char *av[])
{
	t_stack	st1;
	t_stack	st2;
	int		ops;

	ops = 0;
	stack_init(&st1);
	stack_init(&st2);
	if (arg_read(ac, av, &st1) == RET_OK)
	{
		//find_optimal_solution(&st1, &st2, st1.pos, &ops);
		//find_solution(&st1, &st2, st1.pos, &ops);
		ft_putnbr(ops);
		ft_putendl("");
		//print_stack(&st1, &st2);
	}
	return (0);
}
