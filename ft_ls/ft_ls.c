/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:11 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/26 18:12:42 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char *av[])
{
	t_result	ret;
	t_lsdata	lsdata;
	t_list		*lst;

	ft_bzero(&lsdata, sizeof(lsdata));
	if ((ret = parse_args(&lsdata, ac, av)) == RET_OK)
	{
		lst = lsdata.dirs;
		while (lst)
		{
			ft_putendl(lst->content);
			lst = lst->next;
		}
	}
	return (ret);
}
