/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_short.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:48:01 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/08 11:48:03 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_result	print_short_entry(t_lsdata *lsd, t_fentry *entry,
							t_smaxvals *vals, int islast)
{
	size_t len;

	len = 0;
	if (lsd->flags & F_SHOWBLCKSZ)
	{
		print_uint(lsd, entry->fs.st_blocks, vals->blocks, 0);
		write_cout(lsd, ' ');
		len = vals->blocks + 1;
	}
	print_name(lsd, entry, 0);
	if (!islast)
	{
		len += get_str_length(entry->name);
		while (len++ < vals->maxw)
			write_cout(lsd, ' ');
	}
	return (RET_OK);
}

void		print_curl(t_lsdata *lsd, t_list *cur_lst, int is_files,
						t_smaxvals	*vls)
{
	t_list		*newl;
	t_fentry	*entry;

	if (cur_lst)
	{
		entry = (t_fentry *)cur_lst->content;
		if (!is_files && S_ISDIR(entry->fs.st_mode) &&
			(lsd->flags & F_RECURSIVE) && !is_notadir(entry->name) &&
			is_showed_entry(entry, lsd->flags))
		{
			newl = create_copy_tlist(cur_lst);
			if (newl)
				ft_lstaddrevsorted(&lsd->dirs, newl, &lsd->flags, cmp_callback);
		}
		print_short_entry(lsd, entry, lsd->flags, vls, row + (col + 1) * vls.row >= size);
	}
}

static void	calc_col_row(t_lsdata *lsd, t_smaxvals	*vls, size_t size)
{
	vls->col = lsd->termwidth / vls->maxw;
	if (vls->col == 0)
		vls->col = 1;
	vls->row = (size + vls->col - 1) / vls->col;
	vls->col = (size + vls->row - 1) / vls->row;
}

void		print_short(t_lsdata *lsd, t_list *lst, int is_files)
{
	t_smaxvals	vls;
	size_t		size;
	size_t		count;
	int			row;
	int			col;

	get_smaxvals(lst, &vls, lsd->flags);
	size = get_lst_real_size(lst, lsd->flags);
	calc_col_row(lsd, &vls, lsd->flags);
	count = 0;
	row = 0;
	col = 0;
	while (count < size)
	{
		if (row + col * vls.row < size)
			cur_lst = get_list_by_index(lst, lsd->flags, row + col * vls.row);
		col++;
		if (row + col * vls.row >= size)
		{
			write_cout(lsd, '\n');
			col = 0;
			row++;
		}
		count++;
	}
	ft_lstdel(&lst, dellst_callback);
}
