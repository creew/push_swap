/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:11 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/07 15:56:18 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/ioctl.h>

void		dellst(void *val)
{
	t_list *lst;

	lst = (t_list *)val;
	ft_lstdel(&lst, dellst_callback);
}

void		delall(t_lsdata *lsd)
{
	ft_lstdel(&lsd->dirs, dellst_callback);
	ft_lstdel(&lsd->files, dellst_callback);
	ft_stack_delall(&lsd->stack, dellst);
}

t_result	lst_iter(t_lsdata *lsd)
{
	t_list		*next;
	t_fentry	*entry;
	t_list		*dirs;
	t_result	ret;

	dirs = lsd->dirs;
	while (dirs)
	{
		next = dirs->next;
		entry = (t_fentry *)dirs->content;
		dirs->next = 0;
		ret = read_dir(lsd, &dirs->next, entry->path);
		if (ret != RET_OK)
		{
			dirs->next = (t_list *)(-1l);
			lsd->err = 1;
		}
		ft_stack_push(&lsd->stack, (void *)dirs);
		dirs = next;
	}
	lsd->dirs = 0;
	return (RET_OK);
}

void		print_all(t_lsdata *lsd)
{
	t_list	*lst;
	size_t	sz_files;

	sz_files = ft_lstsize(lsd->files);
	printlst(lsd, lsd->files, 1);
	lsd->files = 0;
	lst_iter(lsd);
	if (ft_stack_size(&lsd->stack) && sz_files)
		write_cout(lsd, '\n');
	while (ft_stack_size(&lsd->stack))
	{
		ft_stack_pop(&lsd->stack, (void **)&lst);
		print_dir_lst(lsd, lst);
		lst_iter(lsd);
		if (ft_stack_size(&lsd->stack))
			write_cout(lsd, '\n');
	}
	write_flush(lsd);
}

int			main(int ac, char *av[])
{
	t_result		ret;
	t_lsdata		lsd;
	struct winsize	w;

	ft_bzero(&lsd, sizeof(lsd));
	ft_stack_init(&lsd.stack, 32);
	if ((ret = ioctl(0, TIOCGWINSZ, &w)) != -1)
		lsd.termwidth = w.ws_col;
	lsd.ctime = time(NULL);
	ret = parse_args(&lsd, ac, av);
	if (ret != RET_OK)
		lsd.err = 1;
	if (ret != ERR_ENOMEM && ret != ERR_ILLEGAL_ARGS)
		print_all(&lsd);
	delall(&lsd);
	return (lsd.err);
}
