/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:02:01 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/29 16:02:01 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


size_t		set_path(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (path[len - 1] != '/')
		path[len++] = '/';
	return (len);
}

size_t		add_pathdir(char *path, const char *dir)
{
	size_t	len;

	len = set_path(path);
	ft_strcpy(path + len, dir);
	return (len + ft_strlen(dir));
}
