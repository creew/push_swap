/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:02:01 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/05 15:33:33 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t		set_path(char *path)
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

t_uint		get_uint_width(t_uint num)
{
	int		size;

	size = 1;
	if (num == 0)
		return (size);
	if (num / 10 != 0)
		return (get_uint_width(num / 10) + size);
	return (size);
}

t_uint		get_uid_length(uid_t uid, t_uint flags)
{
	struct passwd *pwd;

	if (!(flags & F_ID_NUMBERS))
	{
		pwd = getpwuid(uid);
		if (pwd)
			return (ft_strlen(pwd->pw_name));
	}
	return (get_uint_width(uid));
}

t_uint		get_str_length(char *str)
{
	t_uint	c;
	int		plus;
	t_uint 	len;

	len = 0;
	while ((c = (t_uint)*str))
	{
		len++;
		plus = 1;
		if (!(c & 0x80u))
			plus = 1;
		else if (((c >> 6u) & 7u) == 6)
			plus = 2;
		else if (((c >> 5u) & 0xFu) == 0xE)
			plus = 3;
		else if (((c >> 3u) & 0x1Fu) == 0x1E)
			plus = 4;
		while (plus && *str)
		{
			plus--;
			str++;
		}
	}
	return (len);
}

t_uint		get_gid_length(gid_t gid, t_uint flags)
{
	struct group	*grp;

	if (!(flags & F_ID_NUMBERS))
	{
		grp = getgrgid(gid);
		if (grp)
			return (ft_strlen(grp->gr_name));
	}
	return (get_uint_width(gid));
}

int			is_notadir(char *name)
{
	if (!ft_strcmp(name, ".")  || !ft_strcmp(name, ".."))
		return (1);
	return (0);
}
