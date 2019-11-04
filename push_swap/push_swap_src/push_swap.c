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
	t_stg	stg;
	int		ret;

	stg.is_show_stat = 0;
	stg.is_colorized = 0;
	stack_init(&stg.st1);
	stack_init(&stg.st2);
	ret = arg_read(ac, av, &stg);
	if (ret == RET_OK)
		calc_optimal(&stg);
	else if (ret != ERROR_NO_ARGUMENTS)
		ft_putendl("Error");
	stack_free(&stg.st1);
	stack_free(&stg.st2);
	return (0);
}
