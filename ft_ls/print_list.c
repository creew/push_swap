/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 14:24:04 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/06 19:31:50 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	is_showed_entry(t_fentry *entry, t_uint flags)
{
	return ((entry->name[0] != '.' || (flags & F_INCLUDE_DIR)));
}

void		get_maxvals(t_list *lst, t_maxvals *vals, t_uint flags)
{
	t_fentry		*entry;
	size_t			len;

	while (lst)
	{
		entry = (t_fentry *)(lst->content);
		if (is_showed_entry(entry, flags))
		{
			if ((len = ft_strlen(entry->name)) > vals->name)
				vals->name = len;
			if ((len = get_uint_width(entry->fs.st_blocks)) > vals->blocks)
				vals->blocks = len;
			vals->total_blocks += entry->fs.st_blocks;
			if ((len = get_uint_width(entry->fs.st_nlink)) > vals->links)
				vals->links = len;
			if ((len = get_uid_length(entry->fs.st_uid, flags)) > vals->owner)
				vals->owner = len;
			if ((len = get_gid_length(entry->fs.st_gid, flags)) > vals->group)
				vals->group = len;
			if ((len = get_uint_width(entry->fs.st_size)) > vals->size)
				vals->size = len;
		}
		lst = lst->next;
	}
}

size_t		get_max_short_len(t_lsdata *lsd, t_list *lst)
{
	t_fentry	*entry;
	size_t		max_name_len;
	size_t		max_blk_len;
	t_uint		blk_len;
	t_uint		name_len;

	max_name_len = 0;
	max_blk_len = 0;
	while (lst)
	{
		entry = (t_fentry *)(lst->content);
		if (is_showed_entry(entry, lsd->flags))
		{
			if (lsd->flags & F_SHOWBLCKSZ)
				if ((blk_len = get_uint_width(entry->fs.st_blksize) > max_blk_len))
					max_blk_len = blk_len;
			if ((name_len = ft_strlen(entry->name)) > max_name_len)
				max_name_len = name_len;
		}
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
		if (entry->name[0] != '.' || (flags & F_INCLUDE_DIR))
			size++;
		lst = lst->next;
	}
	return (size);
}

t_fentry	*get_entry_by_index(t_list *lst, t_uint flags, int index)
{
	t_fentry	*entry;

	while (lst)
	{
		entry = (t_fentry *)lst->content;
		if (is_showed_entry(entry, flags))
		{
			if (index == 0)
				return ((t_fentry *)lst->content);
			index--;
		}
		lst = lst->next;
	}
	return (NULL);
}

void		printlst(t_lsdata *lsd, t_list *lst)
{
	t_fentry	*entry;
	t_maxvals	vals;
	size_t		max_len;
	size_t		count;
	int			del;
	t_list		*next;

	count = 0;
	if (lsd->flags & F_LONG_FORMAT || lsd->flags & F_GROUP_NAME)
	{
		if (get_lst_real_size(lst, lsd->flags))
		{
			ft_bzero(&vals, sizeof(vals));
			get_maxvals(lst, &vals, lsd->flags);
			write_out(lsd, "total ");
			write_number(lsd, vals.total_blocks);
			write_cout(lsd, '\n');
			while (lst)
			{
				del = 0;
				entry = (t_fentry *)(lst->content);
				next = lst->next;
				if (S_ISDIR(entry->fs.st_mode) && (lsd->flags & F_RECURSIVE)
					&& !is_notadir(entry->name) && is_showed_entry(entry, lsd->flags))
				{
					ft_lstaddrevsorted(&lsd->dirs, lst, &lsd->flags, cmp_callback);
					del = 1;
				}
				print_entry(lsd, entry, lsd->flags, &vals);
				if (!del)
					ft_lstdelone(&lst, dellst_callback);
				lst = next;
			}
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

void		print_dir_lst(t_lsdata *lsd, t_list *lst)
{
	t_fentry	*entry;

	if (lst)
	{
		entry = (t_fentry *)lst->content;
		write_out(lsd, entry->path);
		write_cout(lsd, ':');
		write_cout(lsd, '\n');
		printlst(lsd, lst->next);
		ft_lstdelone(&lst, dellst_callback);
	}
}
