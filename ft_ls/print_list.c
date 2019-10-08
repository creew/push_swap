/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 14:24:04 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/07 18:20:13 by eklompus         ###   ########.fr       */
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

void		get_smaxvals(t_list *lst, t_smaxvals *vals, t_uint flags)
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
	vals->maxw = ((vals->name + (vals->blocks ? (vals->blocks + 9) : 8)) / 8) * 8;
}

size_t		get_lst_real_size(t_list *lst, t_uint flags)
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

void		print_long(t_lsdata *lsd, t_list *lst, int is_files)
{
	t_fentry	*entry;
	t_maxvals	vals;
	int			del;
	t_list		*next;

	get_maxvals(lst, &vals, lsd->flags);
	if (!is_files)
		write_out_total(lsd, vals.total_blocks);
	while (lst)
	{
		del = 0;
		entry = (t_fentry *)(lst->content);
		next = lst->next;
		if (!is_files && S_ISDIR(entry->fs.st_mode) &&
			(lsd->flags & F_RECURSIVE) && !is_notadir(entry->name) &&
			is_showed_entry(entry, lsd->flags))
		{
			ft_lstaddrevsorted(&lsd->dirs, lst, &lsd->flags, cmp_callback);
			del = 1;
		}
		print_long_entry(lsd, entry, lsd->flags, &vals);
		if (!del)
			ft_lstdelone(&lst, dellst_callback);
		lst = next;
	}
}

t_result		print_short_entry(t_lsdata *lsd, t_fentry *entry,
	unsigned int flags, t_smaxvals *vals, int islast)
{
	size_t len;

	len = 0;
	if (flags & F_SHOWBLCKSZ)
	{
		print_uint(lsd, entry->fs.st_blocks, vals->blocks, 0);
		write_cout(lsd, ' ');
		len = vals->blocks + 1;
	}
	print_name(lsd, entry, 0);
	len += get_str_length(entry->name);
	if (!islast)
	{
		while (len++ < vals->maxw)
			write_cout(lsd, ' ');
	}
	return (RET_OK);
}

void		print_short(t_lsdata *lsd, t_list *lst, int is_files)
{
	t_smaxvals	vls;
	size_t 		size;
	size_t 		count;
	t_fentry	*entry;
	int			del;
	int			row;
	int 		col;
	t_list 		*cur_lst;
	t_list		*newl;

	get_smaxvals(lst, &vls, lsd->flags);
	size = get_lst_real_size(lst, lsd->flags);

	vls.col = lsd->termwidth / vls.maxw;
	if (vls.col == 0)
		vls.col = 1;
	vls.row = (size + vls.col - 1) / vls.col;
	vls.col = (size + vls.row - 1) / vls.row;
	count = 0;
	row = 0;
	col = 0;
	while (count < size)
	{
		if (row + col * vls.row < size)
		{
			cur_lst = get_list_by_index(lst, lsd->flags, row + col * vls.row);
			if (cur_lst)
			{
				entry = (t_fentry *)cur_lst->content;
				if (!is_files && S_ISDIR(entry->fs.st_mode) && (lsd->flags & F_RECURSIVE) &&
					!is_notadir(entry->name) && is_showed_entry(entry, lsd->flags))
				{
					newl = create_copy_tlist(cur_lst);
					if (newl)
						ft_lstaddrevsorted(&lsd->dirs, newl, &lsd->flags, cmp_callback);
				}
				print_short_entry(lsd, entry, lsd->flags, &vls, row + (col + 1) * vls.row >= size);
			}
		}
		col++;
		if (row + col * vls.row >= size || col >= vls.col)
		{
			write_cout(lsd, '\n');
			col = 0;
			row++;
		}
		count++;
	}
	ft_lstdel(&lst, dellst_callback);
}

void		printlst(t_lsdata *lsd, t_list *lst, int is_files)
{
	if (get_lst_real_size(lst, lsd->flags))
	{
		if (lsd->flags & F_LONG_FORMAT)
		{
			print_long(lsd, lst, is_files);
		}
		else
		{
			print_short(lsd, lst, is_files);
		}
	}
}

void		print_dir_lst(t_lsdata *lsd, t_list *lst)
{
	if (lst)
	{
		if (lsd->dircount > 0 || (lsd->argcount > 1))
			write_out_path(lsd, ((t_fentry *)lst->content)->path);
		if (lst->next == (t_list *)-1l)
			write_perm_denied(((t_fentry *)(lst->content))->name);
		else
			printlst(lsd, lst->next, 0);
		ft_lstdelone(&lst, dellst_callback);
		lsd->dircount++;
	}
}
