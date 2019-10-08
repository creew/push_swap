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
		next = lst->next;
		entry = (t_fentry *)(lst->content);
		if (is_showed_entry(entry, lsd->flags) || is_files)
		{
			if (!is_files && S_ISDIR(entry->fs.st_mode) &&
				(lsd->flags & F_RECURSIVE) && !is_notadir(entry->name))
			{
				ft_lstaddrevsorted(&lsd->dirs, lst, &lsd->flags, cmp_callback);
				del = 1;
			}
			print_long_entry(lsd, entry, lsd->flags, &vals);
		}
		if (!del)
			ft_lstdelone(&lst, dellst_callback);
		lst = next;
	}
}

void		printlst(t_lsdata *lsd, t_list *lst, int is_files)
{
	if (get_lst_real_size(lst, lsd->flags, is_files))
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
