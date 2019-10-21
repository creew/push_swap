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

int			add_one(t_dllist **root, t_action_array *arr, t_uint val)
{
	int			res;
	t_dllist	*dll;

	res = add_new_dllist(root, &dll);
	if (res == RET_OK)
	{
		dll->data.pos = arr ? arr->pos + 1 : 1;
		dll->data.array = ft_memalloc(dll->data.pos / 2 + 1);
		if (!dll->data.array)
			return (ERROR_ENOMEM);
		if (arr)
			ft_memcpy(dll->data.array, arr->array, (arr->pos + 2) / 2);
		if ((dll->data.pos & 1u))
			dll->data.array[(dll->data.pos - 1) / 2] = val << 4u;
		else
			dll->data.array[(dll->data.pos - 1) / 2] |= val;
	}
	return (res);
}

t_dllist	*check_step(t_dllist **root, t_stack *st)
{
	t_dllist *dl;
	t_dllist *next;
	t_stack st1;
	t_stack st2;

	stack_init(&st1);
	stack_init(&st2);
	while (42)
	{
		dl = *root;
		while (dl)
		{
			next = dl->next;
			if (is_arr_sorts(&dl->data, st, &st1, &st2))
				return (dl);
			dl = next;
		}
	}
}

int		main(int ac, char *av[])
{
	t_stack	st1;
	t_stack	st2;
	int		ops;
	t_dllist *root;

	ops = 0;
	stack_init(&st1);
	stack_init(&st2);
	if (arg_read(ac, av, &st1) == RET_OK)
	{
		if (!is_stack_sorted(&st1, st1.pos, 0))
		{
			int i = S_SA;
			while (i <= S_RRR)
			{
				add_one(&root, 0, i);
				i++;
			}
			check_step(&root, &st1);
		}
		ft_putnbr(ops);
		ft_putendl("");
		//print_stack(&st1, &st2);
	}
	return (0);
}
