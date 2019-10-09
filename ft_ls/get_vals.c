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

static void	get_size_maxvals(t_fentry *entry, t_maxvals *vals)
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

static void	get_one_maxval(t_fentry *entry, t_maxvals *vals, t_uint flags)
{
	size_t			len;

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
}

void		get_maxvals(t_list *lst, t_maxvals *vals, t_uint flags)
{
	t_fentry		*entry;

	ft_bzero(vals, sizeof(*vals));
	while (lst)
	{
		entry = (t_fentry *)(lst->content);
		get_one_maxval(entry, vals, flags);
		lst = lst->next;
	}
}

static void	get_one_smaxval(t_fentry *entry, t_maxvals *vals, t_uint flags)
{
	t_uint		len;

	if (is_showed_entry(entry, flags))
	{
		if (flags & F_INODES)
		{
			if ((len = get_ulong_width(entry->fs.st_ino)) > vals->inode)
				vals->inode = len;
		}
		if (flags & F_SHOWBLCKSZ)
		{
			if ((len = get_ulong_width(entry->fs.st_blocks)) > vals->blocks)
				vals->blocks = len;
		}
		if ((len = get_str_length(entry->name)) > vals->name)
			vals->name = len;
	}
}

void		get_smaxvals(t_list *lst, t_smaxvals *vals, t_uint flags)
{
	t_fentry	*entry;

	ft_bzero(vals, sizeof(*vals));
	while (lst)
	{
		entry = (t_fentry *)(lst->content);
		get_one_smaxval(entry, vals, flags);
		lst = lst->next;
	}
	vals->maxw = ((vals->name + (vals->blocks ? (vals->blocks + 1) : 0) +
		(vals->inode ? (vals->inode + 1) : 0) + 8) / 8) * 8;
}
