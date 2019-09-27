/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 11:35:08 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/27 11:28:15 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_result	write_usage(void)
{
	ft_putstr_fd("usage: ls [-", 2);
	ft_putstr_fd(LEGAL_OPTIONS, 2);
	ft_putstr_fd("] [file ...]", 2);
	ft_putchar_fd('\n', 2);
	return (RET_OK);
}

static t_result	write_illegal_param(char s)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(s, 2);
	ft_putchar_fd('\n', 2);
	return (RET_OK);
}

static t_uint	get_format(char c)
{
	if (c == 'R')
		return (F_RECURSIVE);
	if (c == 'a')
		return (F_INCLUDE_DIR);
	if (c == 'l')
		return (F_LONG_FORMAT);
	if (c == 'r')
		return (F_REVERSE);
	if (c == 't')
		return (F_SORTTIME);
	if (c == 'u')
		return (F_SORTATIME);
	if (c == 'f')
		return (F_NOT_SORTED);
	if (c == 'g')
		return (F_GROUP_NAME);
	if (c == 'd')
		return (F_DIR_LIKE_FILE);
	if (c == 'G')
		return (F_COLORISED);
	return (F_ERROR);
}

static t_result	parse_arg(t_lsdata *lsd, char *arg, int *fls)
{
	t_list		*lst;
	t_result	ret;

	ret = RET_OK;
	if (*arg == '-' && *fls)
	{
		while (*++arg)
		{
			if (!ft_strchr(LEGAL_OPTIONS, *arg))
			{
				write_illegal_param(*arg);
				write_usage();
				return (ERR_ILLEGAL_ARGS);
			}
			lsd->flags |= get_format(*arg);
		}
	}
	else
	{
		ret = add_param(lsd, arg);
	}
	return (ret);
}

t_result		parse_args(t_lsdata *lsd, int ac, char *av[])
{
	t_list	*lst;
	int 	ret;
	int		fls;

	fls = 1;
	if (ac < 2)
	{
		lst = ft_lstnew(STR_CURRENT_DIR, ft_strlen(STR_CURRENT_DIR) + 1);
		if (!lst)
			return (ERR_ENOMEM);
		add_param(&lsd, ".");
	}
	else
	{
		while (--ac > 0)
			if ((ret = parse_arg(lsd, av[ac], &fls)) != RET_OK)
				return (ret);
	}
	return (RET_OK);
}