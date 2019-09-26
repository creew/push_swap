/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 11:37:33 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/26 11:46:36 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
t_flist		*add_to_flist(t_flist **flist, char	*name)
{
	char	*tmp;
	t_flist	*newfl;

	newfl = NULL;
	tmp = ft_strdup(name);
	if (tmp)
	{
		newfl = ft_memalloc(sizeof(t_flist));
		if (newfl)
		{
			if (*flist)
			{
				newfl->next = *flist;
				(*flist)->prev = newfl;
			}
			*flist = newfl;
		}
		else
			ft_strdel(&tmp);
	}
	return (newfl);
}
 */
