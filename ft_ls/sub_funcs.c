/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:02:01 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/07 14:02:40 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	set_path(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (path[len - 1] != '/')
	{
		path[len++] = '/';
		path[len] = '\0';
	}
	return (len);
}

int		is_notadir(const char *name)
{
	if (name[0] == '.')
	{
		if (name[1] == '\0')
			return (1);
		if (name [1] == '.')
		{
			if (name[2] == '\0')
				return (1);
		}
	}
	return (0);
}
