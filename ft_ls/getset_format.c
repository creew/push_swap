/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:22:19 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/09 11:22:21 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			setformat(t_lsdata *lsd, t_uint flag)
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

t_uint			get_format(char c)
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
