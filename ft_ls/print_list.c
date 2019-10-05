/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 14:24:04 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/05 11:09:12 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_uint		get_maxvals(t_list *lst, t_maxvals *vals, t_uint flags)
{
	t_fentry		*fentry;
	size_t			len;
	t_uint			bsize;

	bsize = 0;
	while (lst)
	{
		fentry = (t_fentry *)(lst->content);
		if ((fentry->name[0] == '.' &&
			(flags & F_INCLUDE_DIR)) || fentry->name[0] != '.')
		{
			if ((len = ft_strlen(fentry->name)) > vals->name)
				vals->name = len;
			if ((len = get_uint_width(fentry->fs.st_blocks)) > vals->blocks)
				vals->blocks = len;
			bsize += fentry->fs.st_blocks;
			if ((len = get_uint_width(fentry->fs.st_nlink)) > vals->links)
				vals->links = len;
			if ((len = get_uid_length(fentry->fs.st_uid, flags)) > vals->owner)
				vals->owner = len;
			if ((len = get_gid_length(fentry->fs.st_gid, flags)) > vals->group)
				vals->group = len;
			if ((len = get_uint_width(fentry->fs.st_size)) > vals->size)
				vals->size = len;
		}
		lst = lst->next;
	}
	return (bsize);
}

size_t		get_max_short_len(t_lsdata *lsd, t_list *lst)
{
	t_fentry	*fentry;
	size_t		max_name_len;
	size_t		max_blk_len;
	t_uint		blk_len;
	t_uint		name_len;

	max_name_len = 0;
	max_blk_len = 0;
	while (lst)
	{
		fentry = (t_fentry *)(lst->content);
		if (lsd->flags & F_SHOWBLCKSZ)
			if ((blk_len = get_uint_width(fentry->fs.st_blksize) > max_blk_len))
				max_blk_len = blk_len;
		if ((name_len = ft_strlen(fentry->name)) > max_name_len)
			max_name_len = name_len;
		lst = lst->next;
	}
	return ((lsd->flags & F_SHOWBLCKSZ) ? max_blk_len + max_name_len + 1 :
		max_name_len);
}

size_t		get_lst_real_size(t_list *lst, t_uint flags)
{
	size_t		size;
	t_fentry	*entry;

	size = 0;
	while (lst)
	{
		entry = (t_fentry *)lst->content;
		if (entry->name[0] == '.')
		{
			if (flags & F_INCLUDE_DIR)
				size++;
		}
		else
			size++;
		lst = lst->next;
	}
	return (size);
}

t_fentry	*get_entry_by_index(t_list *lst, t_uint flags, int index)
{
	t_fentry	*entry;
	int			found;

	found = 0;
	while (lst)
	{
		entry = (t_fentry *)lst->content;
		if (entry->name[0] == '.')
		{
			if (flags & F_INCLUDE_DIR)
				found = 1;
		}
		else
			found = 1;
		if (found)
		{
			if (index == 0)
				return ((t_fentry *)lst->content);
			index--;
			found = 0;
		}
		lst = lst->next;
	}
	return (NULL);
}

void		printlst(t_lsdata *lsd, t_list *lst)
{
	t_fentry	*fentry;
	t_maxvals	vals;
	size_t		max_len;
	size_t		count;

	count = 0;
	if (lsd->flags & F_LONG_FORMAT || lsd->flags & F_GROUP_NAME)
	{
		ft_bzero(&vals, sizeof(vals));
		get_maxvals(lst, &vals, lsd->flags);
		while (lst)
		{
			fentry = (t_fentry *)(lst->content);
			print_entry(lsd, fentry, lsd->flags, &vals);
			printlst(lsd, fentry->child);
			lst = lst->next;
		}
	}
	else
	{
		max_len = get_max_short_len(lsd, lst);
		while (count < max_len)
		{
			count++;
		}
	}
}
