/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:11 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/05 16:10:40 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/ioctl.h>

void	dellst(void *val)
{
	t_list *lst;

	lst = (t_list *)val;
	ft_lstdel(&lst, dellst_callback);
}

void	delall(t_lsdata *lsd)
{
	ft_lstdel(&lsd->dirs, dellst_callback);
	ft_lstdel(&lsd->files, dellst_callback);
	ft_stack_delall(&lsd->stack, dellst);
}



t_result	lst_iter(t_lsdata * lsd)
{
	t_list		*lst;
	t_list 		*prev;
	t_fentry	*entry;
	t_list		*dirs;
	t_result	ret;

	dirs = lsd->dirs;
	lst = 0;
	while (dirs)
	{
		entry = (t_fentry *)dirs->content;
		if ((ret = read_dir(lsd, &lst, entry->path)) == RET_OK)
		{
			ft_stack_push(&lsd->stack, (void *)lst);
		}
		prev = dirs;
		dirs = dirs->next;
		ft_lstdelone(&prev, dellst_callback);
	}
	lsd->dirs = 0;
	return (RET_OK);
}

int		main(int ac, char *av[])
{
	t_result		ret;
	t_lsdata		lsd;
	struct winsize	w;
	t_list			*lst;

	ft_bzero(&lsd, sizeof(lsd));
	ft_stack_init(&lsd.stack, 32);
	if (ioctl(0, TIOCGWINSZ, &w) != -1)
		lsd.termwidth = w.ws_col;
	lsd.ctime = time(NULL);
	if ((ret = parse_args(&lsd, ac, av)) == RET_OK)
	{
		printlst(&lsd, lsd.files);
		lst_iter(&lsd);
		while (ft_stack_size(&lsd.stack))
		{
			ft_stack_pop(&lsd.stack, (void **)&lst);
			printlst(&lsd, lst);
			lst_iter(&lsd);
			//ft_lstdel(&lst, dellst_callback);
		}
	}
	write_flush(&lsd);
	delall(&lsd);
	return (ret);
}
