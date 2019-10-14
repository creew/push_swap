/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 07:17:39 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/14 07:17:43 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		point_list_add(t_list **lst, t_point *point)
{
	t_list *new_list;

	new_list = ft_lstnew(point, sizeof(*point));
	if (new_list)
	{
		ft_lstadd(lst, new_list);
	}
	else
		return (ERR_ENOMEM);
	return (RET_OK);
}