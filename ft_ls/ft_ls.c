/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:11 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/06 17:48:19 by eklompus         ###   ########.fr       */
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

void	printstack(t_ftstack *stack, char *st)
{
	size_t size;
	t_list *lst;
	t_fentry *entry;

	size = stack->pos;
	while(size)
	{
		lst = (t_list *)stack->data[size - 1];
		entry = (t_fentry *)lst->content;
		printf("**stack: %s, %lu: %s**\n", st, stack->pos - size, entry->path);
		size--;
	}
}

void	print_list(t_list *lst, char *sr)
{
	t_fentry	*entry;
	int			n;

	n = 0;
	while(lst)
	{
		entry = (t_fentry *)lst->content;
		printf("**lst: %s, %d: %s**\n", sr, n, entry->path);
		n++;
		lst=lst->next;
	}
}

t_result	lst_iter(t_lsdata * lsd)
{

	t_list 		*next;
	t_fentry	*entry;
	t_list		*dirs;
	t_result	ret;

	dirs = lsd->dirs;
	while (dirs)
	{
		next = dirs->next;
		entry = (t_fentry *)dirs->content;
		dirs->next = 0;
		if ((ret = read_dir(lsd, &dirs->next, entry->path)) == RET_OK)
			ft_stack_push(&lsd->stack, (void *)dirs);
			//ft_queue_add(&lsd->queue, (void *)dirs);
		dirs = next;
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
			print_dir_lst(&lsd, lst);
			lst_iter(&lsd);
			if (ft_stack_size(&lsd.stack))
			{
				write_out(&lsd, "\n");
			}
		}
	}
	write_flush(&lsd);
	delall(&lsd);
	return (ret);
}
