/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readarg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:01:30 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/25 09:50:13 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	check_exist_val(t_stack *st, int val)
{
	size_t	size;

	size = st->pos;
	while (size--)
	{
		if (st->stack[size] == val)
			return (ERROR_DUPL_VAL);
	}
	return (RET_OK);
}

int			parse_option(char *arg, t_stg *stg)
{
	t_uint	flags;

	flags = 0;
	if (*arg == '-' && *(arg + 1) != '\0')
	{
		while (*++arg)
		{
			if (*arg == 'v')
				flags |= 1u;
			else if (*arg == 'c')
				flags |= 2u;
			else
				return (0);
		}
		if (flags & 1u)
			stg->is_show_stat = 1;
		if (flags & 2u)
			stg->is_colorized = 1;
		return (1);
	}
	return (0);
}

int			arg_read(int n, char *av[], t_stg *stg)
{
	int		res;
	int		ret;

	ret = ERROR_NO_ARGUMENTS;
	while (n > 1)
	{
		if (parse_option(av[n - 1], stg) == 0)
		{
			if ((ret = safe_atoi(av[n - 1], &res)) != RET_OK)
				break ;
			if ((ret = check_exist_val(&stg->st1, res)) != RET_OK)
				break ;
			stack_push(&stg->st1, res);
		}
		n--;
	}
	return (ret);
}

char		*get_action_str(int i)
{
	if (i == S_SA)
		return ("sa");
	if (i == S_SB)
		return ("sb");
	if (i == S_SS)
		return ("ss");
	if (i == S_PA)
		return ("pa");
	if (i == S_PB)
		return ("pb");
	if (i == S_RA)
		return ("ra");
	if (i == S_RB)
		return ("rb");
	if (i == S_RR)
		return ("rr");
	if (i == S_RRA)
		return ("rra");
	if (i == S_RRB)
		return ("rrb");
	if (i == S_RRR)
		return ("rrr");
	return ("");
}
