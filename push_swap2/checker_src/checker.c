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

static int	arg_cmp(int *arg, size_t count, char *ch, int ret)
{
	int		count_op;

	count_op = S_SA;
	while (count_op <= S_RRR)
	{
		if (ft_strlen(get_action_str(count_op)) == count)
		{
			if (ft_strncmp(get_action_str(count_op), ch, count) == 0)
			{
				*arg = count_op;
				return (ret);
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

	*arg = S_ERROR;
	count = 0;
	while ((res = ft_getc(0)) >= 0 && count < 4)
	{
		if (res == '\n')
			break ;
		ch[count++] = (char)res;
	}
	if (res == FT_EOF && count == 0)
		return (RET_ENDL);
	if ((res != '\n' && res != FT_EOF) || count < 2)
		return (ERROR_INCORRECT_ARGS);
	return (arg_cmp(arg, count, ch, res == FT_EOF ? RET_ENDL : RET_OK));
}

static int	process_arg(t_stg *stg)
{
	int		ret;
	int		res;

	while ((ret = readl(&res)) >= RET_OK)
	{
		if (res != S_ERROR)
			run_commands(stg, res, NULL);
		if (ret == RET_ENDL)
		{
			ft_putendl(is_stack_sorted(&stg->st1, stg->st1.pos) == RET_OK
				&& stg->st2.pos == 0 ? "OK" : "KO");
			break ;
		}
	}
	return (ret);
}

int			main(int ac, char *av[])
{
	t_stg		stg;
	int			ret;

	stack_init(&stg.st1);
	stack_init(&stg.st2);
	stg.is_show_stat = 0;
	ret = arg_read(ac, av, &stg);
	if (ret == RET_OK)
	{
		if (process_arg(&stg) < RET_OK)
			ft_putendl("Error");
	}
	else if (ret != ERROR_NO_ARGUMENTS)
		ft_putendl("Error");
	stack_free(&stg.st1);
	stack_free(&stg.st2);
	return (0);
}
