/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:55:51 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/08 12:55:52 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_showed_entry(t_fentry *entry, t_uint flags)
{
	return ((entry->name[0] != '.' || (flags & F_INCLUDE_DIR)));
}

static void get_size_maxvals(t_fentry *entry, t_maxvals *vals)
{
	size_t			len;

	if (S_ISCHR(entry->fs.st_mode) || S_ISBLK(entry->fs.st_mode))
	{
		if ((len = get_ulong_width(major(entry->fs.st_rdev))) > vals->major)
			vals->major = len;
		if ((len = get_ulong_width(minor(entry->fs.st_rdev))) > vals->minor)
			vals->minor = len;
		if ((vals->major + vals->minor + 3) > vals->size)
			vals->size = vals->major + vals->minor + 3;
	}
	else
	{
		if ((len = get_ulong_width(entry->fs.st_size)) > vals->size)
			vals->size = len;
	}
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
			get_size_maxvals(entry, vals);
			if ((len = get_str_length(entry->name)) > vals->name)
				vals->name = len;
			if ((len = get_ulong_width(entry->fs.st_ino)) > vals->inode)
				vals->inode = len;
			if ((len = get_ulong_width(entry->fs.st_blocks)) > vals->blocks)
				vals->blocks = len;
			vals->total_blocks += entry->fs.st_blocks;
			if ((len = get_ulong_width(entry->fs.st_nlink)) > vals->links)
				vals->links = len;
			if ((len = get_uid_length(entry->fs.st_uid, flags)) > vals->owner)
				vals->owner = len;
			if ((len = get_gid_length(entry->fs.st_gid, flags)) > vals->group)
				vals->group = len;

		}
		lst = lst->next;
	}
}

void	get_smaxvals(t_list *lst, t_smaxvals *vals, t_uint flags)
{
	t_fentry	*entry;
	t_uint		len;

	ft_bzero(vals, sizeof(*vals));
	while (lst)
	{
		entry = (t_fentry *)(lst->content);
		if (is_showed_entry(entry, flags))
		{
			if (flags & F_INODES)
			{
				len = get_ulong_width(entry->fs.st_ino);
				if (len > vals->inode)
					vals->inode = len;
			}
			if (flags & F_SHOWBLCKSZ)
			{
				len = get_ulong_width(entry->fs.st_blocks);
				if (len > vals->blocks)
					vals->blocks = len;
			}
			if ((len = get_str_length(entry->name)) > vals->name)
				vals->name = len;
		}
		lst = lst->next;
	}
	vals->maxw = ((vals->name + (vals->blocks ? (vals->blocks + 1) : 0) +
		(vals->inode ? (vals->inode + 1) : 0) + 8) / 8) * 8;
}

size_t	get_lst_real_size(t_list *lst, t_uint flags, int is_file)
{
	size_t		size;
	t_fentry	*entry;

	size = 0;
	while (lst)
	{
		entry = (t_fentry *)lst->content;
		if (is_file || is_showed_entry(entry, flags))
			size++;
		lst = lst->next;
	}
	return (size);
}

t_list	*get_list_by_index(t_list *lst, t_uint flags, int index, int is_file)
{
	t_fentry	*entry;

	while (lst)
	{
		entry = (t_fentry *)lst->content;
		if (is_file || is_showed_entry(entry, flags))
		{
			if (index == 0)
				return (lst);
			index--;
		}
		lst = lst->next;
	}
	return (NULL);
}
