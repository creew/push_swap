/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:42:09 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/21 18:42:10 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		add_new_dllist(t_dllist **root, t_dllist **res)
{
	t_dllist	*dll;

	dll = ft_memalloc(sizeof(*dll));
	if (!dll)
		return (ERROR_ENOMEM);
	dll->prev = NULL;
	dll->next = *root;
	if (*root)
		(*root)->prev = dll;
	*root = dll;
	*res = dll;
	return (RET_OK);
}

void	rm_dllist(t_dllist **root, t_dllist *dll)
{
	ft_memdel((void **)&(dll->data));
	if (dll->prev)
		dll->prev->next = dll->next;
	if (dll->next)
		dll->next->prev = dll->prev;
	if (dll == *root)
		*root = dll->next;
	ft_memdel((void **)&dll);
}