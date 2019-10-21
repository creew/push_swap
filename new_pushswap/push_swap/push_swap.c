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

int check_for_dup(t_dllist *dl)
{
	size_t	size;
	t_uchar	*data;

	data = dl->data.array;
	size = dl->data.pos;



}

t_dllist	*check_step(t_dllist **root, t_stack *st)
{
	t_dllist *dl;
	t_dllist *next;
	t_stack st1;
	t_stack st2;
	int	iters;

	iters = 0;

	stack_init(&st1);
	stack_init(&st2);
	while (42)
	{
		ft_putnbr(++iters);
		ft_putendl("");
		dl = *root;
		while (dl)
		{
			next = dl->next;
			if (is_arr_sorts(&dl->data, st, &st1, &st2))
				return (dl);
			dl = next;
		}
		dl = *root;
		while (dl)
		{
			next = dl->next;
			int i = S_SA;
			while (i <= S_RRR)
			{
				add_one(root, &dl->data, i);
				i++;
			}
			rm_dllist(root, dl);
			dl = next;
		}
		dl = *root;
		while (dl)
		{
			next = dl->next;
			if (check_for_dup(dl))
				rm_dllist(root, dl);
			dl = next;
		}
	}
}

char  *g_operations[] = {
	"sa",
	"sb",
	"ss",
	"pa",
	"pb",
	"ra",
	"rb",
	"rr",
	"rra",
	"rrb",
	"rrr"
};

int		main(int ac, char *av[])
{
	t_stack	st1;
	int		ops;
	t_dllist *root;
	t_dllist *ll;

	ops = 0;
	stack_init(&st1);
	if (arg_read(ac, av, &st1) == RET_OK)
	{
		if (is_stack_sorted(&st1, st1.pos, 0) != RET_OK)
		{
			int i = S_SA;
			while (i <= S_RRR)
			{
				add_one(&root, 0, i);
				i++;
			}
			ll = check_step(&root, &st1);
			if (ll)
			{
				for (int i = 0; i < ll->data.pos; i++)
				{
					t_uchar data = ll->data.array[i / 2];
					data = !(i & 1) ? data >> 4 : data & 0xF;
					ft_putendl(g_operations[data - S_SA]);
				}
			}
		}
		ft_putnbr(ops);
		ft_putendl("");
		//print_stack(&st1, &st2);
	}
	return (0);
}
