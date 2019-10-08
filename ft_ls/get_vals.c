/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:49:12 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/08 11:49:16 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_showed_entry(t_fentry *entry, t_uint flags)
{
	return ((entry->name[0] != '.' || (flags & F_INCLUDE_DIR)));
}

void	get_maxvals(t_list *lst, t_maxvals *vals, t_uint flags)
{
	t_fentry		*entry;
	size_t			len;

	ft_bzero(vals, sizeof(*vals));
	while (lst)
	{
		entry = (t_fentry *)(lst->content);
		if (is_showed_entry(entry, flags))
		{
			if ((len = get_str_length(entry->name)) > vals->name)
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

void	get_smaxvals(t_list *lst, t_smaxvals *vals, t_uint flags)
{
	t_fentry	*entry;
	t_uint		blk_len;
	t_uint		name_len;

	ft_bzero(vals, sizeof(*vals));
	while (lst)
	{
		entry = (t_fentry *)(lst->content);
		if (is_showed_entry(entry, flags))
		{
			if (flags & F_SHOWBLCKSZ)
			{
				blk_len = get_uint_width(entry->fs.st_blocks);
				if (blk_len > vals->blocks)
					vals->blocks = blk_len;
			}
			if ((name_len = get_str_length(entry->name)) > vals->name)
				vals->name = name_len;
		}
		lst = lst->next;
	}
	vals->maxw = ((vals->name + (vals->blocks ? (vals->blocks + 9) : 8))
		/ 8) * 8;
}

size_t	get_lst_real_size(t_list *lst, t_uint flags)
{
	size_t		size;
	t_fentry	*entry;

	size = 0;
	while (lst)
	{
		entry = (t_fentry *)lst->content;
		if (is_showed_entry(entry, flags))
			size++;
		lst = lst->next;
	}
	return (size);
}

t_list	*get_list_by_index(t_list *lst, t_uint flags, int index)
{
	t_fentry	*entry;

	while (lst)
	{
		entry = (t_fentry *)lst->content;
		if (is_showed_entry(entry, flags))
		{
			if (index == 0)
				return (lst);
			index--;
		}
		lst = lst->next;
	}
	return (NULL);
}
