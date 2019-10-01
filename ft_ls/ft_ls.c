/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:11 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/01 15:02:51 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/ioctl.h>

void	delone(void *data, size_t content_size)
{
	(void)(content_size);
	t_fentry *entry = (t_fentry *)data;
	ft_lstdel(&entry->child, delone);
	ft_memdel(&data);
}

void	delall(t_lsdata *lsd)
{
	ft_lstdel(&lsd->dirs, delone);
	ft_lstdel(&lsd->files, delone);
}

t_uint 	get_maxvals(t_list *lst, t_maxvals *vals)
{
	t_fentry		*fentry;
	size_t			len;
	t_uint			bsize;

	bsize = 0;
	while (lst)
	{
		fentry = (t_fentry *)(lst->content);
		if ((len = ft_strlen(fentry->name)) > vals->name)
			vals->name = len;
		if ((len = get_uint_width(fentry->fs.st_blocks)) > vals->blocks)
			vals->blocks = len;
		bsize += fentry->fs.st_blocks;
		if ((len = get_uint_width(fentry->fs.st_nlink)) > vals->links)
			vals->links = len;
		if ((len = get_uid_length(fentry->fs.st_uid)) > vals->owner)
			vals->owner = len;
		if ((len =get_gid_length(fentry->fs.st_gid)) > vals->group)
			vals->group = len;
		if ((len = get_uint_width(fentry->fs.st_size)) > vals->size)
			vals->size = len;
		lst = lst->next;
	}
	return (bsize);
}

void	printlst(t_lsdata *lsd, t_list *lst)
{
	t_fentry	*fentry;
	t_maxvals	vals;

	ft_bzero(&vals, sizeof(vals));
	get_maxvals(lst, &vals);
	while (lst)
	{
		fentry = (t_fentry *)(lst->content);

		print_entry(lsd, fentry, lsd->flags, &vals);
		printlst(lsd, fentry->child);
		lst = lst->next;
	}
}

int		main(int ac, char *av[])
{
	t_result	ret;
	t_lsdata	lsd;
	time_t		cur_time;
	struct		winsize w;

	ft_bzero(&lsd, sizeof(lsd));
	if (ioctl(0, TIOCGWINSZ, &w) != -1)
		lsd.termwidth = w.ws_col;
	cur_time = time(NULL);
	if (cur_time != -1)
		parse_time(cur_time, &lsd.ftime);
	if ((ret = parse_args(&lsd, ac, av)) == RET_OK)
	{
		printlst(&lsd, lsd.files);
		printlst(&lsd, lsd.dirs);
	}
	write_flush(&lsd);
	delall(&lsd);
	return (ret);
}
