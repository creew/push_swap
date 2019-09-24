/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:58:29 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/24 16:08:53 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void print_stack(t_stack *st1, t_stack *st2)
{
	size_t c1;
	size_t c2;

	c1 = st1->pos;
	c2 = st2->pos;
	ft_putendl("st1      st2");
	while (c1 > 0 || c2 > 0)
	{
		c1 ? ft_putnbr(st1->stack[--c1]) : ft_putstr("     ");
		ft_putstr("   ");
		c2 ? ft_putnbr(st2->stack[--c2]) : ft_putstr("     ");
		ft_putendl("");
	}
}

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

int run_commands(t_stack *st1, t_stack *st2, int n)
{
	int val;

	if (n == S_SA || n == S_SS)
		stack_swap(st1);
	if (n == S_SB || n == S_SS)
		stack_swap(st2);
	if (n == S_PA)
		if (stack_pop(st2, &val) == RET_OK)
			stack_push(st1, val);
	if (n == S_PB)
		if (stack_pop(st1, &val) == RET_OK)
			stack_push(st2, val);
	if (n == S_RA || n == S_RR)
		stack_rotate(st1);
	if (n == S_RB || n == S_RR)
		stack_rotate(st2);
	if (n == S_RRA || n == S_RRR)
		stack_rrotate(st1);
	if (n == S_RRB || n == S_RRR)
		stack_rrotate(st2);
	return (RET_OK);
}

int main(int ac, char *av[])
{
	t_stack st1;
	t_stack st2;
	int		res;
	int		ret;

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
				ft_putendl(is_stack_sorted(&st1) == RET_OK && st2.pos == 0 ?
				"OK" : "KO");
				break;
			}
			run_commands(&st1, &st2, res);
			print_stack(&st1, &st2);
		}
	}
	stack_free(&st1);
	stack_free(&st2);
	return (0);
}
