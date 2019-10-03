/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:11 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/03 14:23:59 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/ioctl.h>

void	delone(void *data, size_t content_size)
{
	t_fentry	*entry;

	(void)(content_size);
	entry = (t_fentry *)data;
	ft_lstdel(&entry->child, delone);
	ft_memdel(&data);
}

void	delall(t_lsdata *lsd)
{
	ft_lstdel(&lsd->dirs, delone);
	ft_lstdel(&lsd->files, delone);
}

int		main(int ac, char *av[])
{
	t_result		ret;
	t_lsdata		lsd;
	struct winsize	w;

	ft_bzero(&lsd, sizeof(lsd));
	if (ioctl(0, TIOCGWINSZ, &w) != -1)
		lsd.termwidth = w.ws_col;
	lsd.ctime = time(NULL);
	if (lsd.ctime != -1)
		parse_time(lsd.ctime, &lsd.ftime);
	if ((ret = parse_args(&lsd, ac, av)) == RET_OK)
	{
		printlst(&lsd, lsd.files);
		printlst(&lsd, lsd.dirs);
	}
	write_flush(&lsd);
	delall(&lsd);
	return (ret);
}
