/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_short.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:55:03 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/08 12:55:07 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_result	print_short_entry(t_lsdata *lsd, t_fentry *entry,
						t_smaxvals *vals, int islast)
{
	size_t len;

	len = 0;
	if (lsd->flags & F_INODES)
	{
		print_ulong(lsd, entry->fs.st_ino, vals->inode, 0);
		write_cout(lsd, ' ');
		len += (vals->inode + 1);
	}
	if (lsd->flags & F_SHOWBLCKSZ)
	{
		print_ulong(lsd, entry->fs.st_blocks, vals->blocks, 0);
		write_cout(lsd, ' ');
		len += (vals->blocks + 1);
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

static void		calc_wind_size(t_window *wind, t_uint termwidth,
										t_uint maxw, size_t size)
{
	wind->mcol = termwidth / maxw;
	if (wind->mcol == 0)
		wind->mcol = 1;
	wind->mrow = (size + wind->mcol - 1) / wind->mcol;
	wind->mcol = (size + wind->mrow - 1) / wind->mrow;
	wind->crow = 0;
	wind->ccol = 0;
}

static void		print_one_short(t_lsdata *lsd, t_window *wind,
					t_list *lst, int is_files)
{
	t_list		*cur_lst;
	t_list		*newl;
	t_fentry	*entry;

	if (wind->crow + wind->ccol * wind->mrow >= wind->size)
		return ;
	cur_lst = get_list_by_index(lst, lsd->flags,
		wind->crow + wind->ccol * wind->mrow, is_files);
	if (!cur_lst)
		return ;
	entry = (t_fentry *)cur_lst->content;
	if (!is_files && S_ISDIR(entry->fs.st_mode) && (lsd->flags & F_RECURSIVE) &&
		!is_notadir(entry->name) && is_showed_entry(entry, lsd->flags))
	{
		newl = create_copy_tlist(cur_lst);
		if (newl)
			ft_lstaddrevsorted(&lsd->dirs, newl, &lsd->flags, cmp_callback);
	}
	print_short_entry(lsd, entry, &wind->vls,
		wind->crow + (wind->ccol + 1) * wind->mrow >= wind->size);
}

void			print_short(t_lsdata *lsd, t_list *lst, int is_files)
{
	size_t		count;
	t_window	wind;

	get_smaxvals(lst, &wind.vls, lsd->flags);
	wind.size = get_lst_real_size(lst, lsd->flags, is_files);
	calc_wind_size(&wind, lsd->termwidth, wind.vls.maxw, wind.size);
	count = 0;
	while (count < wind.size)
	{
		print_one_short(lsd, &wind, lst, is_files);
		wind.ccol++;
		if (wind.crow + wind.ccol * wind.mrow >= wind.size)
		{
			write_cout(lsd, '\n');
			wind.ccol = 0;
			wind.crow++;
		}
		count++;
	}
}
