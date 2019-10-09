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

int			add_recursivable_dir(t_lsdata *lsd, t_list *lst, int is_files)
{
	t_list		*newl;
	t_fentry	*entry;

	entry = (t_fentry *)(lst->content);
	if (!is_files && S_ISDIR(entry->fs.st_mode) &&
		(lsd->flags & F_RECURSIVE) && !is_notadir(entry->name))
	{
		newl = create_copy_tlist(lst);
		if (newl)
		{
			ft_lstaddrevsorted(&lsd->dirs, newl, &lsd->flags, cmp_callback);
			return (1);
		}
		return (-1);
	}
	return (0);
}

int			print_long(t_lsdata *lsd, t_list *lst, int is_files)
{
	t_fentry	*entry;
	t_maxvals	vals;
	int			printed;

	printed = 0;
	get_maxvals(lst, &vals, lsd->flags);
	if (!is_files)
		write_out_total(lsd, vals.total_blocks);
	while (lst)
	{
		entry = (t_fentry *)(lst->content);
		if (is_entry_printable(entry, is_files, lsd->flags))
		{
			add_recursivable_dir(lsd, lst, is_files);
			print_long_entry(lsd, entry, lsd->flags, &vals);
			printed++;
		}
		lst = lst->next;
	}
	return (printed);
}

void		print_nosuch(t_lsdata *lsd, t_list *lst)
{
	t_fentry *entry;

	if (lst)
	{
		print_nosuch(lsd, lst->next);
		entry = (t_fentry *)lst->content;
		if (entry->is_nosuch)
		{
			lsd->err = 1;
			write_no_such_file(entry->path);
		}
	}
}

int			printlst(t_lsdata *lsd, t_list **lst, int is_files)
{
	int	printed;

	printed = 0;
	print_nosuch(lsd, *lst);
	if (get_lst_real_size(*lst, lsd->flags, is_files))
	{
		if (lsd->flags & F_LONG_FORMAT)
			printed = print_long(lsd, *lst, is_files);
		else
			printed = print_short(lsd, *lst, is_files);
	}
	ft_lstdel(lst, dellst_callback);
	return (printed);
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
			printlst(lsd, &lst->next, 0);
		ft_lstdelone(&lst, dellst_callback);
		lsd->dircount++;
	}
}
