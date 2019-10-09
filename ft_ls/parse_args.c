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

static t_result	check_n_addparam(t_lsdata *lsd, char c)
{
	if (!ft_strchr(LEGAL_OPTIONS, c))
	{
		write_illegal_param(c);
		write_usage();
		return (ERR_ILLEGAL_ARGS);
	}
	setformat(lsd, get_format(c));
	return (RET_OK);
}

static t_result	check_fts(char *arg)
{
	if (ft_strlen(arg) == 0)
	{
		write_no_such_file("fts_open");
		return (ERR_FTS_OPEN);
	}
	return (RET_OK);
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
			if ((ret = check_n_addparam(lsd, *arg)) != RET_OK)
				return (ret);
		}
	}
	else
	{
		if ((ret = check_fts(arg)) != RET_OK)
			return (ret);
		lsd->argcount++;
		ret = add_param(lsd, arg);
		*fls = 0;
	}
	return (ret);
}

static t_result	add_std_dir(t_lsdata *lsd)
{
	t_result	ret;

	ret = add_param(lsd, STR_CURRENT_DIR);
	if (ret != RET_OK)
		lsd->err = 1;
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
		if (ret != RET_OK)
			return (ret);
	}
	lsd->flags |= ((lsd->flags & F_NOT_SORTED) ? F_INCLUDE_DIR : 0);
	if (lsd->flags & F_ONECOLUMN)
		lsd->termwidth = 0;
	if (!ft_lstsize(lsd->files) && !ft_lstsize(lsd->dirs) && !lsd->err)
	{
		if ((ret = add_std_dir(lsd)) != RET_OK)
			return (ret);
	}
	return (RET_OK);
}
