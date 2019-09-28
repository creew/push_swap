/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:11 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/28 16:32:16 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	printlst(t_list *lst)
{
	t_fentry	*fentry;
	while (lst)
	{
		fentry = (t_fentry *)(lst->content);

		ft_putendl(fentry->name);
		printlst(fentry->child);
		lst = lst->next;
	}
}

int		main(int ac, char *av[])
{
	t_result	ret;
	t_lsdata	lsdata;
	t_list		*lst;
	t_fentry	*fentry;

	ft_bzero(&lsdata, sizeof(lsdata));
	if ((ret = parse_args(&lsdata, ac, av)) == RET_OK)
	{
		printlst(lsdata.files);
		printlst(lsdata.dirs);
	}
	return (ret);
}
