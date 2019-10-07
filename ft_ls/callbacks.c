/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:47:47 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/07 11:05:35 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static long	cmp_time(t_fentry *f1, t_fentry *f2, t_uint flags)
{
	long res;

	if (flags & F_SORTATIME)
	{
		res = f2->fs.ST_ATIME.tv_sec - f1->fs.ST_ATIME.tv_sec;
		if (!res)
			res = f2->fs.ST_ATIME.tv_nsec - f1->fs.ST_ATIME.tv_nsec;
	}
	else
	{
		res = f2->fs.ST_MTIME.tv_sec - f1->fs.ST_MTIME.tv_sec;
		if (!res)
			res = f2->fs.ST_MTIME.tv_nsec - f1->fs.ST_MTIME.tv_nsec;
	}
	return (res);
}

int			cmp_callback(t_list *l1, t_list *l2, void *param)
{
	t_fentry	*f1;
	t_fentry	*f2;
	t_uint		flags;
	long		res;

	flags = *(t_uint *)(param);
	f1 = (t_fentry *)(l1->content);
	f2 = (t_fentry *)(l2->content);
	res = 0;
	if (flags & F_NOT_SORTED)
		return (0);
	if (flags & F_SORTSIZE)
		res = f2->fs.st_size - f1->fs.st_size;
	else if (flags & F_SORTTIME)
		res = cmp_time(f1, f2, flags);
	if (res == 0)
		res = ft_strcmp(f1->path, f2->path);
	return ((int)(flags & F_REVERSE ? -res : res));
}

void		dellst_callback(void *data, size_t content_size)
{
	(void)content_size;
	ft_memdel(&data);
}
