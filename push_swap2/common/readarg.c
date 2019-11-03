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

static int	parse_option(char *arg, t_stg *stg)
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

static int	read_check_val(t_stg *stg, char *s)
{
	int		ret;
	int		res;

	if ((ret = safe_atoi(s, &res)) != RET_OK)
		return (ret);
	if ((ret = check_exist_val(&stg->st1, res)) != RET_OK)
		return (ret);
	stack_push(&stg->st1, res);
	return (ret);
}

int			parse_arr(t_stg *stg, char *str)
{
	char	*s;
	size_t	len;
	int		ret;

	ret = ERROR_NO_ARGUMENTS;
	while ((s = ft_strrchr(str, ' ')))
	{
		len = ft_strlen(str);
		*s = '\0';
		if (s != str + len - 1)
		{
			if ((ret = read_check_val(stg, s + 1)) != RET_OK)
				return (ret);
		}
	}
	if (*str)
	{
		if ((ret = read_check_val(stg, str)) != RET_OK)
			return (ret);
	}
	return (ret);
}

int			arg_read(int n, char *av[], t_stg *stg)
{
	int		ret;

	ret = ERROR_NO_ARGUMENTS;
	while (n > 1)
	{
		if (parse_option(av[n - 1], stg) == 0)
			ret = parse_arr(stg, av[n - 1]);
		n--;
	}
	return (ret);
}
