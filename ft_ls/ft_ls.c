/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:11 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/30 12:16:27 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/ioctl.h>

void	printlst(t_lsdata *lsd, t_list *lst)
{
	t_fentry	*fentry;
	while (lst)
	{
		fentry = (t_fentry *)(lst->content);

		print_entry(lsd, fentry, lsd->flags);
		printlst(lsd, fentry->child);
		lst = lst->next;
	}
}

int		main(int ac, char *av[])
{
	t_result	ret;
	t_lsdata	lsd;
	t_list		*lst;
	t_fentry	*fentry;

	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	//ft_putnbr(w.ws_col);
	//ft_putendl("");

	ft_bzero(&lsd, sizeof(lsd));
	if ((ret = parse_args(&lsd, ac, av)) == RET_OK)
	{
		printlst(&lsd, lsd.files);
		printlst(&lsd, lsd.dirs);
	}
	write_flush(&lsd);
	return (ret);
}
