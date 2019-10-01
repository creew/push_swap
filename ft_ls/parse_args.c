/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 20:08:45 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/30 20:08:45 by eklompus         ###   ########.fr       */
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
	if (c == 's')
		return (F_SHOWBLCKSZ);
	return (F_ERROR);
}

static t_result	parse_arg(t_lsdata *lsd, char *arg, int *fls)
{
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
		*fls = 0;
	}
	return (ret);
}

t_result		parse_args(t_lsdata *lsd, int ac, char *av[])
{
	int		ret;
	int		fls;
	int		count;

	fls = 1;
	count = 1;
	ret = RET_OK;
	while (count < ac)
		if ((ret = parse_arg(lsd, av[count++], &fls)) != RET_OK)
			return (ret);
	if (!ft_lstsize(lsd->files) && !ft_lstsize(lsd->dirs))
		ret = add_param(lsd, STR_CURRENT_DIR);
	return (ret);
}
