/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:02:01 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/01 11:21:07 by eklompus         ###   ########.fr       */
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

t_uint      get_uint_width(t_uint num)
{
	int		size;

	size = 1;
	if (num == 0)
		return (size);
	if (num / 10 != 0)
		return (get_uint_width(num / 10) + size);
	return (size);
}

t_uint		get_uid_length(uid_t uid)
{
	struct passwd	*pwd;

	if ((pwd = getpwuid(uid)))
		return (ft_strlen(pwd->pw_name));
	return (get_uint_width(uid));
}

t_uint		get_gid_length(gid_t gid)
{
	struct group	*grp;

	if ((grp = getgrgid(gid)))
		return (ft_strlen(grp->gr_name));
	return (get_uint_width(gid));
}

