/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:58:29 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/25 14:51:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

const char *g_operations[] = {"sa", "sb", "ss",	 "pa",	"pb", "ra",
								"rb", "rr", "rra", "rrb", "rrr"};

int readl(int *arg)
{
	int	   res;
	char   ch[4];
	size_t count;
	size_t count_op;

	count = 0;
	while ((res = ft_getc(0)) >= 0 && count < 4)
	{
		if (res == '\n')
			break;
		ch[count++] = res;
	}
	if (res == FT_EOF && count == 0)
		return (RET_ENDL);
	if (res != '\n' || count < 2)
		return (ERROR_INCORRECT_ARGS);
	count_op = 0;
	while (count_op < ARRSIZE(g_operations))
	{
		if (ft_strlen(g_operations[count_op]) == count && ft_strncmp(g_operations[count_op], ch, count) == 0)
		{
			*arg = count_op + 1;
			return (RET_OK);
		}
		count_op++;
	}
	return (ERROR_INCORRECT_ARGS);
}

int main(int ac, char *av[])
{
	t_stack		st1;
	t_stack		st2;
	int			res;
	int			ret;

	stack_init(&st1);
	stack_init(&st2);
	ret = arg_read(ac, av, &st1);
	if (ret == RET_OK)
	{
		print_stack(&st1, &st2);
		while ((ret = readl(&res)) >= RET_OK)
		{
			if (ret == RET_ENDL)
			{
				ft_putendl(is_stack_sorted(&st1, st1.pos) == RET_OK && st2.pos == 0 ? "OK" : "KO");
				break;
			}
			run_commands(&st1, &st2, res, NULL);
			print_stack(&st1, &st2);
		}
	}
	stack_free(&st1);
	stack_free(&st2);
	return (0);
}
