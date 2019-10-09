/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lst_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:44:58 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/09 11:45:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			is_entry_printable(t_fentry *entry, int is_file, t_uint flags)
{
	return ((is_file || is_showed_entry(entry, flags)) && !entry->is_nosuch);
}

size_t		get_lst_real_size(t_list *lst, t_uint flags, int is_file)
{
	size_t		size;
	t_fentry	*entry;

	size = 0;
	while (lst)
	{
		entry = (t_fentry *)lst->content;
		if (is_entry_printable(entry, is_file, flags))
			size++;
		lst = lst->next;
	}
	return (size);
}

t_list		*get_list_by_index(t_list *lst, t_uint flags,
									int index, int is_file)
{
	t_fentry	*entry;

	while (lst)
	{
		entry = (t_fentry *)lst->content;
		if (is_entry_printable(entry, is_file, flags))
		{
			if (index == 0)
				return (lst);
			index--;
		}
		lst = lst->next;
	}
	return (NULL);
}
