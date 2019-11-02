/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:55:01 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/21 14:55:01 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	arg_cmp(int *arg, size_t count, char *ch)
{
	int		count_op;

	count_op = S_SA;
	while (count_op < S_RRR)
	{
		if (ft_strlen(get_action_str(count_op)) == count)
		{
			if (ft_strncmp(get_action_str(count_op), ch, count) == 0)
			{
				*arg = count_op;
				return (RET_OK);
			}
		}
		count_op++;
	}
	return (ERROR_INCORRECT_ARGS);
}

static int	readl(int *arg)
{
	int		res;
	char	ch[4];
	size_t	count;

	count = 0;
	while ((res = ft_getc(0)) >= 0 && count < 4)
	{
		if (res == '\n')
			break ;
		ch[count++] = (char)res;
	}
	if (res == FT_EOF && count == 0)
		return (RET_ENDL);
	if (res != '\n' || count < 2)
		return (ERROR_INCORRECT_ARGS);
	return (arg_cmp(arg, count, ch));
}

static int	process_arg(t_stack *st1, t_stack *st2)
{
	int		ret;
	int		res;

	//print_stack(st1, st2);
	while ((ret = readl(&res)) >= RET_OK)
	{
		if (ret == RET_ENDL)
		{
			ft_putendl(is_stack_sorted(st1, st1->pos) == RET_OK
				&& st2->pos == 0 ? "OK" : "KO");
			break ;
		}
		run_commands(st1, st2, res, NULL);
		//print_stack(st1, st2);
	}
	return (ret);
}

int			main(int ac, char *av[])
{
	t_stack		st1;
	t_stack		st2;
	int			ret;

	stack_init(&st1);
	stack_init(&st2);
	ret = arg_read(ac, av, &st1);
	if (ret == RET_OK)
	{
		if (process_arg(&st1, &st2) < RET_OK)
			ft_putendl("Error");
	}
	else
		ft_putendl("Error");
	stack_free(&st1);
	stack_free(&st2);
	return (0);
}
