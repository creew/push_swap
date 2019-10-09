/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 20:08:45 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/07 11:34:23 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		setformat(t_lsdata *lsd, t_uint flag)
{
	if (flag == F_LONG_FORMAT || flag == F_SIMPLE_OUT ||
		flag == F_ONECOLUMN || flag == F_GROUP_NAME)
	{
		lsd->flags &= ~F_LONG_FORMAT;
		lsd->flags &= ~F_SIMPLE_OUT;
		lsd->flags &= ~F_ONECOLUMN;
		lsd->flags &= ~F_GROUP_NAME;
	}
	lsd->flags |= flag;
	lsd->flags |= (flag == F_ID_NUMBERS) ? F_LONG_FORMAT : 0;
	lsd->flags |= (flag == F_GROUP_NAME) ? F_LONG_FORMAT : 0;
}

static t_uint	getformat2(char c)
{
	if (c == 'n')
		return (F_ID_NUMBERS);
	if (c == 'S')
		return (F_SORTSIZE);
	if (c == '1')
		return (F_ONECOLUMN);
	if (c == 'i')
		return (F_INODES);
	if (c == 'C')
		return (F_SIMPLE_OUT);
	return (F_ERROR);
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
	return (getformat2(c));
}

static t_result	parse_arg(t_lsdata *lsd, char *arg, int *fls)
{
	t_result	ret;

	ret = RET_OK;
	if (*arg == '-' && arg[1] != '\0' && *fls)
	{
		if (arg[1] == '-' && arg[2] == '\0')
		{
			*fls = 0;
			return (ret);
		}
		while (*++arg)
		{
			if (!ft_strchr(LEGAL_OPTIONS, *arg))
			{
				write_illegal_param(*arg);
				write_usage();
				return (ERR_ILLEGAL_ARGS);
			}
			setformat(lsd, get_format(*arg));
		}
	}
	else
	{
		lsd->argcount++;
		ret = add_param(lsd, arg);
		if (ret == ERR_STAT)
			write_no_such_file(arg);
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
	while (count < ac)
	{
		ret = parse_arg(lsd, av[count++], &fls);
		if (ret != RET_OK)
			lsd->err = 1;
		if (ret == ERR_ILLEGAL_ARGS || ret == ERR_ENOMEM)
			return (ret);
	}
	lsd->flags |= ((lsd->flags & F_NOT_SORTED) ? F_INCLUDE_DIR : 0);
	if (lsd->flags & F_ONECOLUMN)
		lsd->termwidth = 0;
	if (!ft_lstsize(lsd->files) && !ft_lstsize(lsd->dirs) && !lsd->err)
	{
		ret = add_param(lsd, STR_CURRENT_DIR);
		if (ret != RET_OK)
			lsd->err = 1;
		if (ret == ERR_ENOMEM)
			return (ret);
		if (ret == ERR_STAT)
			write_no_such_file(STR_CURRENT_DIR);
	}
	return (RET_OK);
}
