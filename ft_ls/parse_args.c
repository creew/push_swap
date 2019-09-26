/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 11:35:08 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/26 14:45:25 by eklompus         ###   ########.fr       */
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

static t_result	parse_arg(t_list **root, char *arg, t_uint *flags, int *fls)
{
	t_list	*lst;

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
			*flags = *flags | get_format(*arg);
		}
	}
	else
	{
		*fls = 0;
		lst = ft_lstnew(arg, ft_strlen(arg) + 1);
		if (!lst)
			return (ERR_ENOMEM);
		ft_lstadd(root, lst);
	}
	return (RET_OK);
}

t_result		parse_args(t_list **root, int ac, char *av[], t_uint *flags)
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
		ft_lstadd(root, lst);
	}
	else
	{
		while (--ac > 0)
			if ((ret = parse_arg(root, av[ac], flags, &fls)) != RET_OK)
				return (ret);
	}
	return (RET_OK);
}