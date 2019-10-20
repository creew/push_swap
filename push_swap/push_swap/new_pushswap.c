/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pushswap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:56:32 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/20 15:56:33 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_bfs(t_bfs *bfs)
{
	t_bfs *cur;
	t_bfs *next;

	if (!bfs)
		return;
	if (bfs->children)
	{
		cur = bfs->children;
		while (cur)
		{
			next = cur->next;
			free_bfs(cur);
			cur = next;
		}
	}
	ft_memdel(&bfs);
}

t_bfs *list_bfs(void)
{
	int i;
	t_bfs *first;
	t_bfs *cur;

	first = ft_memalloc(sizeof(*first));
	if (first)
	{
		cur = first;
		while (i < (11 - 1))
		{
			cur->next = ft_memalloc(sizeof(*cur));
			if (!cur->next)
			{

				return (0);
			}

			i++;
		}

	}

	i = 0;
	while (i < 11)


}
int big_bfs_deal(t_bfs *rbfs, t_bfs *pbfs, t_stack *st1, t_stack *st2)
{
	int i;
	t_bfs *

	i = 0;
	if (is_stack_sorted(st1, st1.pos, 0))
		return (1);
	while (i < 11)
	{


	}
}

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
		big_bfs_deal()


	}
	return (0);
}
